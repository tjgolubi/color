# Styled-text wrapping design handoff

[Document map](README.md) · [Workflow](Workflow.md)

Updated November 20, 2026.

## Feature status

`word_wrap()` was implemented in `5675404` on top of the runtime-library
refactor. The pushed `feat/Wrap` tip is
`e99d821498d9a00315bc71f28cce7d4c7fd9a4b8`. The earlier, removed
`wrap()` design is superseded. Integration into `dev` is pending.
See [BuildAndTest.md](BuildAndTest.md#wrap-feature-validation) for the
verified build and CI results.

## Purpose and agreed behavior

Taskwarrior tables motivated the design. Wrapping splits a styled table cell
into physical lines, and the table code aligns and pads those lines.

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

The public overloads are declared in `<tjg/color/styled_text.hpp>` and linked
through `tjg::tjg`. Both take the text by const reference and the width as
`std::size_t`, consistent with the library's other width arguments. Callers
validate signed widths before converting them. The overloads return
`std::vector<styled_text>` and `std::vector<wstyled_text>`, respectively.
See `doc/ref/color/styled_text/word_wrap.md` in the library checkout.

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
leading and interior blank lines remain. Each retained blank line carries
the input’s root style so callers can pad it with the same background as
the surrounding lines. Trailing blank lines are trimmed.

Examples below assume a valid width large enough for the visible text:

```text
"a\n\nb\n\n" -> {"a", "", "b"}
"\n\na\n"    -> {"", "", "a"}
"  a  b  "   -> {"  a  b"}
"\t\n \n"    -> {}
```

## ANSI sequences and remaining controls

Wrapping uses the existing ANSI scanner independently within each text span.
It strips complete ESC-prefixed sequences and retains the scanner's treatment
of incomplete and malformed sequences. Sequences split across spans are
handled separately in each span.

After ANSI stripping, normalize whitespace and discard every remaining
non-whitespace control character, including NUL, backspace, BEL, ESC, DEL
(`\x7f`), and the other C0/C1 controls. Whitespace classification takes
precedence over control removal: whitespace controls become spaces, except
newline, which forces a line break.

Control filtering follows decoding. A valid UTF-8 continuation byte can
have the same numeric value as a C1 control. Malformed units are preserved
individually. Removing a control can join previously malformed units within
a span. For example, removing BEL from `C2 07 80` leaves `C2 80`, which
decodes as U+0080 and is removed on a second wrap. The API reference documents
this behavior for UTF-8 bytes and unpaired UTF-16 surrogates. Terry chose to
document the edge case to avoid adding span boundaries for it.

## Unicode and wide-character support

The local MSYS2 toolchain uses two-byte `wchar_t`. The wide overload decodes
surrogate pairs there and validates UTF-32 scalars on systems with four-byte
`wchar_t`. Both overloads share the line-breaking algorithm.
`include/tjg/color/bits/unicode.hpp` supplies UTF-8 decoding and the
formatter's code-point width lookup.

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

`support/unicode/gen-wrap-tables.py` generates `src/WrapData.hpp` from the
checked-in Unicode 18.0.0 data. It uses `White_Space` and `Quotation_Mark`
from `PropList.txt` and the punctuation categories from `UnicodeData.txt`.
Unicode License V3 is included in the installed `THIRD-PARTY-NOTICES`.

## Preserving styles and implementation structure

`basic_styled_text<Char>` stores shared immutable leaf strings, child groups,
and a style on each node. Its representation is private. The renderer, ANSI stripper, and
word wrapper have narrow friend access. `plain_text()` loses the style
structure and cannot by itself implement wrapping correctly.

Preserve nested groups, inherited styles, and absolute-style boundaries when
reconstructing each line. Flattening only to effective colors can change
behavior when the result is later nested or overlaid. Keep the input intact.
An inserted hyphen inherits the preceding character's style, with the correct
ancestry retained. Removing ANSI sequences, controls, or trailing spaces must
preserve the styles and nesting of the text that remains.

The narrow and wide entry points share compiled code in `src/word_wrap.cpp`.
The wrapper walks the source groups with an explicit stack. Each token
records its location in the sanitized span, its width, and its break
classification. Prefix sums guide line selection across style boundaries.
To rebuild each line, the wrapper finds the overlapping children by binary
search, copies their styles, and appends any inserted hyphen to the final
span. An empty line needs only the root style for padding.

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

## Tests and demo

`test/word-wrap-test.cc` exercises both overloads, including width validation
before sanitization, physical line breaks, punctuation, oversized words,
malformed input, controls, and sequences split across spans. The style tests
check nested and absolute groups, hyphen inheritance, input preservation,
and formatting of blank lines with field padding. Wide encoding cases
select the appropriate expectations for the platform's `wchar_t` size.

`demo/WrapTable.cpp` wraps each styled cell, aligns its physical lines, and
fills shorter columns with blank cells up to the row height. Unicode borders
outline the columns. Muted slate, green, and plum
backgrounds span text and padding. The header uses white text and scales each
background channel by 2.5, rounded and capped at 255. Bold underlined titles,
the reversed yellow “Blocked” label, and the magenta word “lobby” demonstrate
how a span can keep its own emphasis or foreground inside a colored cell.
