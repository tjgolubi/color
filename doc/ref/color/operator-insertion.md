# `tjg::color::operator<<`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
// Representative overloads
template<CharType Char>
auto operator<<(std::basic_ostream<Char>& os, const text_style& style)
  -> std::basic_ostream<Char>&;
template<CharType Char>
auto operator<<(std::basic_ostream<Char>& os,
                const basic_styled_text<Char>& value)
  -> std::basic_ostream<Char>&;
```

## Description

Supports `char` and `wchar_t` streams where the wrapped value is insertable.

### Readable values

Color values, `color_t`, `no_color_t`, and emphasis use readable notation via
[`write_value`](write_value.md), with width, fill, and alignment as for strings.

### Opening style: `const text_style&`

Writes opening [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) only. An empty style emits a terminal reset. Pending stream
width is preserved.

### Styled value: `styled` result

Inserts the value with its style. Width, fill, precision, and alignment
apply to the wrapped insertion.

### Styled text: `const basic_styled_text<Char>&`

Renders nested styled text. Stream width applies to the visible width of the result.

### Operand summary

| Right operand                                                 | Output                                                                                                          |
| ---                                                           | ---                                                                                                             |
| Color value, `color_t`, `no_color_t`, or `emphasis`           | Readable notation via [`write_value`](write_value.md), with width, fill, and alignment as for string insertion. |
| [`text_style`](text_style/text_style/index.md)                | Opening SGR only. An empty style emits a terminal reset. Pending stream width is preserved.                     |
| [`styled`](styled.md) result                                  | Inserts the value with its style. Width, fill, precision, and alignment apply to the wrapped insertion.         |
| [`basic_styled_text`](styled_text/basic_styled_text/index.md) | Renders the styled text with its nested styles. Stream width applies to the visible width of the result.        |

Supports `char` and `wchar_t` streams where the wrapped value is insertable. Returns `os`. See the [stream insertion examples](../../print.md#styled-stream-insertion).

## Return value

The destination stream `os`.

## Notes

When inserting `text_style` values directly into a stream, also insert an SGR
reset after the styled text, for example with [`sgr_reset()`](sgr/sgr_reset.md).
Without that reset, subsequent styled output may behave unexpectedly.

```cpp
using namespace tjg::color;
using enum term_color;
std::cout << fg(red) << "Warning" << sgr_reset();
```

## See also

[Standard stream insertion](https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt2.html).
