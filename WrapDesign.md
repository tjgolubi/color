# Styled-text wrapping design handoff

[Document map](README.md) · [Workflow](Workflow.md)

Updated November 20, 2026.

## Status and authorization

`wrap()` is not currently part of the project. The first implementation was
removed at Terry's instruction, including its headers, Unicode table
generator, tests, documentation, and build integrations. Do not recover it
as an accepted implementation. Its removal passed the build, all 22 CTest
entries, and the strict documentation build.

This document preserves the design discussion and lessons for the next
session. Writing it does not authorize implementation. Follow the prime
directive in [Workflow.md](Workflow.md): a question calls for an answer,
not project edits. Temporary scratch experiments are allowed. Wait for an
imperative instruction before implementing or integrating `wrap()`.

The inspected library checkout is `feat/CppRef` at
`0bdfa029668fb4650d619d88870784b86e3e49e3`, matching its local remote-tracking
ref. The reference changes and source-comment cleanup are committed; only
the convenience script `ViewWeb.bash` remains untracked. Coordination
documents are in the `coord/` worktree on `docs/Coord`, versioned separately
from the library. Recheck actual state before work; do not assume either checkout is
clean. Terry wants `wrap()` in its own commit. Preserve existing changes; do not
commit, stash, switch branches, or restore whole files without authorization.

## Purpose and agreed behavior

The motivating use is Taskwarrior tables: wrap a styled table cell into
physical lines, then let the table code align and pad those lines. The
replacement should work on styled text rather than a rendered `std::string`.

- Accept styled text and a display-width parameter; return a vector of
  styled-text lines.
- Measure display columns, not bytes or string length.
- Preserve styling while splitting text into lines.
- Do not align or pad the results. Alignment belongs to the caller.
- Use a minimum requested width of 16 columns initially. Terry chose this
  arbitrary practical minimum; the earlier eight-column discussion was not
  a chosen limit. The width must also accommodate the widest character.
- Allow breaks at whitespace and punctuation.
- A word that fits the full column should move intact to the next line when
  it does not fit the remaining space. "Too wide" means wider than the whole
  column, not merely wider than its remaining space.
- For words wider than the column, Terry suggested severing them at the
  margin with a hyphen. Reserve a column for the inserted hyphen; finalize
  the exact rules before documenting them as guarantees.

An API shape discussed was `wrap(styled_text, width) ->
std::vector<styled_text>`. The value/reference parameter choice, width type,
exception for invalid width, and wide-character API are still design choices.
Use `style`, not `ts`, for public style parameter names.

## Newlines, tabs, and control sequences

Terry proposed removing ANSI escape sequences using our stripping facilities
and removing other control characters, with special handling for `\n` and
`\t`. Newline should force a line break. Decide and test empty input, repeated
newlines, and a trailing newline explicitly rather than silently dropping
empty physical lines.

Real tab stops, if supported, must be relative to the start of the column,
not the output stream. Four columns seemed useful to Terry; eight is the
well-known default. No tab-stop size was finalized. A simpler first version
could replace whitespace controls other than newline with one space. The
removed implementation treated tab, carriage return, vertical tab, and form
feed this way; that was an implementation choice, not a settled requirement
for its successor. Resolve tab and CRLF behavior before implementation.

The existing `strip_ansi(basic_styled_text<Char>)` in
`include/tjg/color/bits/strip_ansi_styled_text.hpp` strips complete
ESC-prefixed sequences independently in each leaf. Its documented behavior
retains sequences spanning leaves. Reusing it alone does not provide stripping
across text-span boundaries. Decide whether `wrap()` needs a streaming ANSI
scanner across spans; do not change `strip_ansi()` semantics incidentally.
Also decide how to handle incomplete escapes and malformed encoded input.

Strip controls after decoding characters. In UTF-8, a continuation byte may
have the numeric value of a C1 control; deleting such bytes corrupts text.
ANSI removal must leave structured styles intact rather than rendering them
as escape sequences and reparsing them.

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
- `include/tjg/color/bits/EastAsianWidth.hpp` and `UnicodeData.hpp`:
  checked-in tables; `support/unicode/` documents their generation.

Existing UTF-8 formatting estimates width as one or two columns per code
point. The wide-character path does not already provide equivalent Unicode
decoding and width measurement. GBF's `mk_wcwidth` treatment of combining
characters can also differ from our formatter. Decide whether wrapping must
match our formatter exactly or whether shared width facilities need revision.
Do not promise grapheme-cluster or terminal-perfect emoji behavior without
implementing and testing it. Avoid splitting encoded characters; separately
decide treatment of combining marks, variation selectors, and ZWJ sequences.

The removed implementation added punctuation and whitespace range tables
and a Python generator. These were removed too. Check existing data before
adding new generated files. Define which punctuation permits a break and
whether the punctuation stays on the preceding line; do not describe a simple
punctuation heuristic as a complete Unicode line-breaking implementation.

## Preserving styles and implementation structure

`basic_styled_text<Char>` stores shared immutable leaf strings, child groups,
and a style on each node. Its representation is private. The renderer and
ANSI stripper have narrow friend access. `plain_text()` loses the style
structure and cannot by itself implement wrapping correctly.

Preserve nested groups, inherited styles, and absolute-style boundaries when
reconstructing each line. Flattening only to effective colors can change
behavior when the result is later nested or overlaid. Keep the input intact.
An inserted hyphen needs a deliberate style policy, likely the style of the
preceding text, with correct ancestry retained.

One promising approach from the removed implementation is to track decoded
tokens with source ranges, select line ranges in a shared wrapping algorithm,
then reconstruct the corresponding portions of the original styled groups.
Whitespace normalization and inserted hyphens require explicit generated
tokens. Maintain decoding and ANSI state across spans if that behavior is
chosen. Preserve source mappings when sanitization changes text lengths.
Watch for repeated full-tree rescans, excess copying, and very deep nesting.

Terry asked whether most of the implementation could live in a `.cpp` file.
Much of the algorithm can, but Color currently presents itself as a standalone
header library. Do not silently add a compiled-library dependency. Settle the
packaging first: a shared non-template algorithm with encoding adapters is
possible, as are out-of-line implementations for supported character types,
but linkage, installation, consumers, and build configuration must agree.

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

## Next-session decisions and verification

Before implementation, settle the character types and encodings, header-only
versus compiled packaging, width semantics, whitespace and tab policy,
hyphenation, and malformed-input behavior. Present unresolved choices plainly;
do not implement a narrow version and disclose its limitations afterward.

After an imperative implementation instruction, inspect existing diffs and
record the proposed changes before editing. Keep the wrap change independently
reviewable. A new header alone does not authorize integrations under a
scratch-file exception. Check for Vim swap files before changing open files.

Meaningful tests should cover ASCII wrapping; moving a fitting word intact;
oversized words and hyphen width; punctuation; forced and empty lines;
controls and ANSI sequences; UTF-8 multibyte characters; two-column characters
at the margin; UTF-16 surrogate pairs and UTF-32 where supported; nested and
absolute styles; style boundaries inside a word or encoded character; and
input preservation. Add cases for the chosen malformed-input and tab policies.
Each returned line must fit the chosen display-width model.

Run relevant focused tests, then the full build and CTest suite. Build the
documentation strictly after authorized documentation changes. Use MSYS2 Git,
never Windows Git, and the existing MSYS2 toolchain with `/usr/bin` on PATH.
See [BuildAndTest.md](BuildAndTest.md) for procedures. Report exactly which
character types and behaviors were tested. Leave the work uncommitted unless
Terry separately instructs a commit.
