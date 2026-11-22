# [`tjg::color::word_wrap`](https://github.com/tjgolubi/color/blob/e99d821498d9a00315bc71f28cce7d4c7fd9a4b8/include/tjg/color/styled_text.hpp#L167)

Header: [`<tjg/color/styled_text.hpp>`](index.md), also available through
[`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
auto word_wrap(const styled_text& text, std::size_t width, std::size_t indent = 0)
  -> std::vector<styled_text>;
auto word_wrap(const wstyled_text& text, std::size_t width, std::size_t indent = 0)
  -> std::vector<wstyled_text>;
```

## Description

Returns lines of styled text whose estimated display widths do not exceed
`width`. Leaves alignment to the caller and leaves `text` unchanged. Preserves
nested groups, inherited styles, and absolute-style boundaries, including when
the returned lines are subsequently nested or overlaid with another style.

The first line uses the full width. Each subsequent nonblank line starts
with `indent` spaces in the outermost style and has `width - indent` columns
available for its text. This also applies after explicit newlines. Blank
lines remain empty, and `indent` defaults to zero.

### Narrow overload

Decodes UTF-8 independently within each text span. Each malformed byte is
preserved and counts as one column; sequences split across spans are not joined.

### Wide overload

Decodes UTF-16 when `wchar_t` is two bytes, and UTF-32 when it is four bytes,
independently within each text span. Valid surrogate pairs are kept together.
Unpaired surrogates and invalid UTF-32 values are preserved, each counting as
one column. Surrogate pairs split across spans are not joined.

### Display width and breaks

Both overloads use the UTF-8 formatter's Unicode 18.0.0 width table. Wide code
points count as two columns and most other decoded characters as one. Soft
hyphens are zero-width break hints. Combining marks, variation selectors, and
ZWJ sequences retain the formatter's code-point width behavior. Wide formatting
uses code-unit measurement.

Breaks are allowed at ordinary spaces and after Unicode punctuation, except opening
punctuation and characters with the Unicode `Quotation_Mark` property. This
keeps apostrophes within contractions. Eligible punctuation remains on the
preceding line with no added hyphen. These are break preferences, not a full
Unicode line-breaking implementation.

A word or punctuation-delimited portion that fits the line's content width
moves to the next line if it cannot fit the remaining space. For an oversized
portion, choose the last fitting soft-hyphen or ideographic break. A soft
hyphen (`U+00AD`) becomes an ASCII `-` only when its break is used and there
is room for the hyphen. The hyphen inherits the preceding character's style
and all enclosing groups. Breaks between adjacent characters in Unicode's
Ideographic (`ID`) line-break class add no hyphen. For example, `北京大学`
wraps at width four as `北京` and `大学`.

A no-break space (`U+00A0`) counts as one column and keeps adjacent text
together if it fits on a full line. For an oversized group, when no preferred
break fits, wrapping can break at the last no-break space that fits. The
separator is consumed and no hyphen is added. For example, `10 kg` stays on
one line at width five and wraps as `10` and `kg` at width four. If there
is no fitting break, split at the last complete decoded character that leaves
room for an ASCII `-`. Style boundaries alone do not create break opportunities.

### Whitespace and controls

Complete ESC-prefixed ANSI sequences are stripped independently from each text
span using the existing ANSI scanner. Sequences spanning spans are not
recognized. Incomplete and malformed sequences retain the scanner's existing
handling, after which the following filtering applies.

Each Unicode `White_Space` character becomes one ordinary space, except `\n`
and `U+00A0`. Newlines force line breaks, and no-break spaces retain their
original encoding. Tabs have no tab stops; consecutive whitespace is
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

Throws `std::invalid_argument` when `width < 4` or `indent > width - 4`, even
for empty or whitespace-only input. Validate signed widths and indents before
converting them to `std::size_t`. Allocation can throw. With exceptions
disabled, invalid widths or indents use the library's `TJG_THROW` failure
policy.

## See also

[Wrapping guide](../../../styled.md#wrapping-text-into-lines),
[WrapTable walkthrough](../../../wrap-table.md),
[`basic_styled_text`](basic_styled_text/index.md),
[`strip_ansi`](../sgr/strip_ansi.md).
