# Styled-text wrapping design handoff

[Document map](README.md) · [Workflow](Workflow.md)

Updated November 20, 2026.

## Status and authorization

`wrap()` is not currently part of the project. The first implementation was
removed at Terry's instruction, including its headers, Unicode table
generator, tests, documentation, and build integrations. Do not recover it
as an accepted implementation. Its removal passed the build, all 22 CTest
entries, and the strict documentation build.

The behavior below is agreed and sufficiently specified for implementation.
Updating this document does not authorize implementation. Follow the prime
directive in [Workflow.md](Workflow.md): a question calls for an answer,
not project edits. Temporary scratch experiments are allowed. Wait for an
imperative instruction before implementing or integrating `wrap()`.

The inspected library checkout is `feat/Wrap` at
`e5c1cd09f9bd8614ddfa2b05d41a90703ed6744d`, the runtime-library refactor
committed on `ref/RuntimeCpp` and reported pushed by Terry. The library has
no tracked edits; `ViewWeb.bash` remains an untracked convenience script.
Coordination documents are in the `coord/` worktree on `docs/Coord`, versioned
separately from the library. Recheck actual state before work; do not assume
either checkout is clean. Terry wants `wrap()` in its own commit. Do not
commit, stash, switch branches, or restore whole files without authorization.

## Purpose and agreed behavior

The motivating use is Taskwarrior tables: wrap a styled table cell into
physical lines, then let the table code align and pad those lines. The
replacement should work on styled text rather than a rendered `std::string`.

- Accept styled text and a display-width parameter; return a vector of
  styled-text lines.
- Measure display columns, not bytes or string length.
- Support both `styled_text` and `wstyled_text`, preserving styling while
  splitting text into lines. Keep the input intact.
- Do not align or pad the results. Alignment belongs to the caller.
- Use a minimum requested width of 16 columns. Validate width first and throw
  `std::invalid_argument` for any width below 16, even for empty or
  whitespace-only input. Do not clamp invalid widths. This minimum also
  accommodates the widest character in the chosen one/two-column width model.
- Allow breaks at whitespace and eligible punctuation, as specified below.
- A word that fits the full column should move intact to the next line when
  it does not fit the remaining space. "Too wide" means wider than the whole
  column, not merely wider than its remaining space.
- Split words wider than the whole column at the last complete decoded
  character that leaves one column for an ASCII `-`. The inserted hyphen
  inherits the preceding character's style and enclosing style ancestry.
  Continue the word on the next line.
- At a punctuation break, leave the punctuation on the preceding line and
  do not insert a hyphen. Inserted hyphens are for oversized words only.

An API shape discussed was `wrap(styled_text, width) ->
std::vector<styled_text>`, with a corresponding wide-character interface.
The value/reference parameter choice and width type are implementation
choices, subject to the behavior above. Prefer signed types where suitable,
and reject negative widths rather than converting them to huge unsigned
values. Use `style`, not `ts`, for public style parameter names.

## Whitespace and physical lines

Replace each whitespace character with one ordinary space, except `\n`, which
forces a line break. This includes tab, carriage return, vertical tab, and
form feed. There are no tab stops and no collapsing of consecutive whitespace
characters into one space. Carriage return is normalized to a space even
before a newline; trailing-space trimming removes it at that line ending.

Preserve leading and interior newlines, including the empty physical lines
they express. Trim trailing newlines. Preserve spaces, including leading
indentation, except at the end of a line or at an automatic wrap boundary.
Consume the separating whitespace at a wrap boundary so it does not trail
the preceding line or lead the next one. Trim trailing whitespace across
text-span boundaries: no returned styled-text line has trailing whitespace.

Return an empty vector if the sanitized input is empty or only whitespace.
Width validation still happens first. For input containing visible text,
leading and interior blank lines remain; trailing blank lines do not.

Examples below assume a valid width large enough for the visible text:

```text
"a\n\nb\n\n" -> {"a", "", "b"}
"\n\na\n"    -> {"", "", "a"}
"  a  b  "   -> {"  a  b"}
"\t\n \n"    -> {}
```

## ANSI sequences and remaining controls

The existing `strip_ansi(basic_styled_text<Char>)` in
`include/tjg/color/bits/strip_ansi_styled_text.hpp` strips complete
ESC-prefixed sequences independently in each leaf. Its documented behavior
retains sequences spanning leaves. Match this behavior: do not recognize
escape sequences split across spans and do not add a streaming ANSI scanner.
Keep the current scanner's handling of incomplete and malformed sequences;
apply the control filtering below to what remains. Do not change
`strip_ansi()` semantics as part of implementing wrapping.

After ANSI stripping, normalize whitespace and discard every remaining
non-whitespace control character, including NUL, backspace, BEL, ESC, DEL
(`\x7f`), and the other C0/C1 controls. Whitespace classification takes
precedence over control removal: whitespace controls become spaces, except
newline, which forces a line break.

Strip controls after decoding characters. In UTF-8, a continuation byte may
have the numeric value of a C1 control; deleting such bytes corrupts text.
Malformed encoded units are preserved under the separate decoding policy;
do not reinterpret malformed UTF-8 bytes as decoded C1 controls. ANSI removal
must leave structured styles intact rather than rendering them as escape
sequences and reparsing them.

## Unicode and wide-character support

The removed implementation only supported UTF-8 `styled_text`. Terry called
out the missing `wstyled_text` support. Do not repeat that omission or treat
templating on `Char` as sufficient Unicode support.

The inspected MSYS2 GCC toolchain has `sizeof(wchar_t) == 2`: its wide strings
require UTF-16 decoding, including surrogate pairs. Other supported systems
may have four-byte `wchar_t` and require UTF-32 scalar validation. This does
not require two different wrapping algorithms: character decoding and output
encoding can vary while the line-breaking algorithm works on decoded tokens.

Inspect these existing facilities before proposing new ones:

- `include/tjg/color/bits/unicode.hpp`: UTF-8 decoding, estimated code-point
  display widths, and prefixes that fit a width limit.
- `include/tjg/color/bits/styled_text-format.hpp`: styled-text measurement,
  truncation, and rendering.
- `include/tjg/color/bits/EastAsianWidth.hpp` and `src/UnicodeData.hpp`:
  checked-in width and private classification tables. `support/unicode/`
  documents their generation; use matching Unicode versions for new data.

Use the current UTF-8 formatter's width model for both character types: two
columns for decoded code points in the wide-character table and one otherwise.
Decode UTF-8 for `char`, UTF-16 for two-byte `wchar_t`, and UTF-32 for four-byte
`wchar_t`. The current wide formatter counts code units; wrapping nevertheless
uses the agreed decoded one/two-column model. Do not change formatter behavior
incidentally or substitute GBF's `mk_wcwidth` rules.

Decode each text span independently, matching the current formatter. Do not
combine UTF-8 sequences or UTF-16 surrogate pairs across spans. Preserve
malformed UTF-8 bytes, unpaired UTF-16 surrogates, and invalid UTF-32 values;
count each invalid code unit as one column. Preserve their original units.

Do not split a valid encoded character. This width model does not combine
grapheme clusters or give combining marks, variation selectors, and ZWJ
sequences special zero-width behavior. Terry accepted that limitation in
favor of matching the current UTF-8 formatter.

## Punctuation break points

Allow breaks after Unicode punctuation except opening punctuation and
quotation marks, including apostrophes. Opening brackets and quotes should
stay attached to following text; apostrophes should not split contractions.
Use Unicode punctuation and quotation-mark classifications consistently,
including ASCII characters. Other punctuation remains on the preceding line
at a break, with no inserted hyphen.

These exclusions govern preferred punctuation breaks. They do not exempt an
oversized word from the agreed character-boundary hyphenation rule.

The removed implementation added punctuation and whitespace range tables
and a Python generator. These were removed too. Check existing data before
adding new generated files. Do not describe this punctuation policy as a
complete Unicode line-breaking implementation.

## Preserving styles and implementation structure

`basic_styled_text<Char>` stores shared immutable leaf strings, child groups,
and a style on each node. Its representation is private. The renderer and
ANSI stripper have narrow friend access. `plain_text()` loses the style
structure and cannot by itself implement wrapping correctly.

Preserve nested groups, inherited styles, and absolute-style boundaries when
reconstructing each line. Flattening only to effective colors can change
behavior when the result is later nested or overlaid. Keep the input intact.
An inserted hyphen inherits the preceding character's style, with the correct
ancestry retained. Removing ANSI sequences, controls, or trailing spaces must
preserve the styles and nesting of the text that remains.

One promising approach from the removed implementation is to track decoded
tokens with source ranges, select line ranges in a shared wrapping algorithm,
then reconstruct the corresponding portions of the original styled groups.
Whitespace normalization and inserted hyphens require explicit generated
tokens. Decode and strip ANSI independently within each span, as agreed.
Word detection and line selection still operate on the concatenated text;
a style boundary alone is not a word boundary. Preserve source mappings when
sanitization changes text lengths.
Watch for repeated full-tree rescans, excess copying, and very deep nesting.

Color now builds a static archive, `libcolor.a` on MSYS2 and Unix, with the
existing `tjg::tjg` CMake consumer target. Implement wrapping's runtime logic
in `.cpp` files and include it in that archive. Ordinary narrow and wide
overloads can share private implementation code; duplicate complete wrapping
algorithms are unnecessary.

Preserve speed and constexpr support before reducing header content. Do not
reintroduce `detail::output`: its type-erased iterator added an indirect call
per output code unit and was removed at Terry's instruction. Iterator-dependent
rendering and quoting remain templated in headers. Do not add an erased
per-character callback or route wrapping through formatted ANSI output.

Use `noexcept` for operations that cannot throw. Respect
`TJG_NOEXCEPT_UNLESS_BAD_ALLOC` where allocation failure is the sole intended
escaping exception; width validation must still throw `std::invalid_argument`.
For `auto` return types, keep the trailing return type on the signature line
when it fits within 80 columns. Move qualifiers before `auto` to a preceding
line first if needed. If the return type still does not fit, place it alone
on the next line, indented two spaces relative to the signature.

## Taskwarrior context

Local files inspected, relative to Terry's
`C:/msys64/home/tjgolubi/prj/taskwarrior/` checkout:

- `src/libshared/src/shared.cpp`: `wrapText()` repeatedly calls
  `extractLine()`. Terry identified `extractLine()` as the behavior he wants
  to replace with formatting-aware styled-text wrapping.
- `src/libshared/src/Table.cpp`: wraps cells into physical lines, aligns each
  line, and assembles the row. Terry previously adapted this code to {fmt}
  with color extensions and plans a similar adaptation using {color}.

The organization is Gothenburg Bit Factory; the upstream repository is
`GothenburgBitFactory/libshared`. Terry's local code differs from upstream.
Read local source again when comparing behavior. These files are context,
not authorization to modify Taskwarrior or to copy its algorithm wholesale.

## Implementation readiness and verification

There are no remaining blocking design questions from this review. The
behavior above is settled. Parameter passing, internal representation,
helper names, and data-generation details remain implementation choices;
they must preserve the agreed behavior and performance priorities.

After an imperative implementation instruction, inspect existing diffs and
record the proposed changes before editing. Keep the wrap change independently
reviewable. A new header alone does not authorize integrations under a
scratch-file exception. Check for Vim swap files before changing open files.

Meaningful tests should cover ASCII wrapping; moving a fitting word intact;
oversized words and hyphen width/style; eligible and excluded punctuation;
leading/interior blank lines and trimmed trailing newlines; whitespace-only
input; indentation and trailing whitespace across spans; per-character
whitespace normalization; DEL and other controls; and per-span ANSI stripping.
Test widths below 16 even for empty input.

Cover UTF-8 multibyte characters, two-column characters at the margin, UTF-16
surrogate pairs, and UTF-32 where supported. Verify malformed units and
encoded sequences split across spans against the agreed per-span policy.
Check nested/absolute styles, words spanning styles, and input preservation.
Every returned line must fit the agreed width model and have no trailing
whitespace. No wrapping implementation or wrap-specific tests are present
yet; the earlier removal/build checks do not validate the future feature.

Run relevant focused tests, then the full build and CTest suite. Build the
documentation strictly after authorized documentation changes. Use MSYS2 Git,
never Windows Git, and the existing MSYS2 toolchain with `/usr/bin` on PATH.
See [BuildAndTest.md](BuildAndTest.md) for procedures. Report exactly which
character types and behaviors were tested. Leave the work uncommitted unless
Terry separately instructs a commit.
