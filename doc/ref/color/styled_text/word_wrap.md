# [`tjg::color::word_wrap`](https://github.com/tjgolubi/color/blob/e99d821498d9a00315bc71f28cce7d4c7fd9a4b8/include/tjg/color/styled_text.hpp#L167)

Header: [`<tjg/color/styled_text.hpp>`](index.md), also available through
[`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
auto word_wrap(const styled_text& text, std::size_t width)
  -> std::vector<styled_text>;
auto word_wrap(const wstyled_text& text, std::size_t width)
  -> std::vector<wstyled_text>;
```

## Description

Returns lines of styled text whose estimated display widths do not exceed
`width`. Does not align or pad lines and leaves `text` unchanged. Preserves
nested groups, inherited styles, and absolute-style boundaries, including when
the returned lines are subsequently nested or overlaid with another style.

### Narrow overload

Decodes UTF-8 independently within each text span. Each malformed byte is
preserved and counts as one column; sequences split across spans are not joined.

### Wide overload

Decodes UTF-16 when `wchar_t` is two bytes, and UTF-32 when it is four bytes,
independently within each text span. Valid surrogate pairs are kept together.
Unpaired surrogates and invalid UTF-32 values are preserved, each counting as
one column. Surrogate pairs split across spans are not joined.

### Display width and breaks

Both overloads use the UTF-8 formatter's Unicode 18.0.0 width table: wide code
points count as two columns and other decoded characters as one. Combining
marks, variation selectors, and ZWJ sequences receive no special grapheme or
zero-width handling. This differs from wide formatting's code-unit measurement.

Breaks are allowed at whitespace and after Unicode punctuation, except opening
punctuation and characters with the Unicode `Quotation_Mark` property. This
keeps apostrophes within contractions. Eligible punctuation remains on the
preceding line with no added hyphen. These are break preferences, not a full
Unicode line-breaking implementation.

A word or punctuation-delimited portion that fits the full width moves intact
to the next line if it cannot fit the remaining space. An oversized portion
splits at the last complete decoded character that leaves room for an ASCII
`-`. The hyphen inherits the preceding character's style and all enclosing
groups. Opening punctuation and quotation marks do not prevent this forced
split. Style boundaries alone are not word boundaries.

### Whitespace and controls

Complete ESC-prefixed ANSI sequences are stripped independently from each text
span using the existing ANSI scanner. Sequences spanning spans are not
recognized. Incomplete and malformed sequences retain the scanner's existing
handling, after which the following filtering applies.

Each Unicode `White_Space` character becomes one ordinary space, except `\n`,
which forces a line break. Tabs have no tab stops; consecutive whitespace is
not collapsed. Carriage return becomes a space even before newline. Remaining
C0/C1 controls, including NUL, BEL, ESC, and DEL, are discarded after decoding.
Malformed encoded units are retained rather than interpreted as C1 controls.

Removing a control within a text span can bring malformed UTF-8 bytes or
unpaired UTF-16 surrogates together so that they form a valid character.
For example, removing BEL from the bytes `C2 07 80` leaves `C2 80`, the
UTF-8 encoding of U+0080. Wrapping that result again removes U+0080 as a
control.

Leading and interior newlines preserve empty physical lines. Trailing spaces
are trimmed across span boundaries, and trailing blank lines are removed.
Leading indentation and interior spaces remain except at automatic wrap
boundaries, where separating whitespace is consumed. Empty or whitespace-only
sanitized input returns an empty vector.

For any valid width large enough for the text:

```text
"a\n\nb\n\n" -> {"a", "", "b"}
"\n\na\n"    -> {"", "", "a"}
"  a  b  "   -> {"  a  b"}
"\t\n \n"    -> {}
```

## Exceptions

Throws `std::invalid_argument` when `width < 4`, even for empty or
whitespace-only input. Width is checked before inspecting text. Validate
signed widths before converting them to `std::size_t`.
Allocation can throw. With exceptions disabled, invalid widths use the
library's `TJG_THROW` failure policy.

## See also

[Wrapping guide](../../../styled.md#wrapping-text-into-lines),
[WrapTable walkthrough](../../../wrap-table.md),
[`basic_styled_text`](basic_styled_text/index.md),
[`strip_ansi`](../sgr/strip_ansi.md).
