# [`tjg::color::operator<<`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/color-ostream.hpp#L37)

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
Styled insertion emits SGR only on a detected terminal. See
[Terminal detection](print.md#terminal-detection) for the stream mapping.

### Readable values

Color values, `color_t`, `no_color_t`, and emphasis use readable notation via
[`write_value`](write_value.md), with width, fill, and alignment as for strings.

### Opening style: `const text_style&`

On a terminal, writes opening SGR or a reset for an empty style. Other
destinations receive no bytes for this operand. Pending stream width is
preserved.

### Styled value: `styled` result

Inserts the value with its style. Width, fill, precision, and alignment
apply to the wrapped insertion.

### Styled text: `const basic_styled_text<Char>&`

Renders nested styled text. Stream width applies to the visible width of the result.

### Wrapped text

Inserts the result of [`wrapped()`](wrapped.md) into a narrow or wide stream. A pending
width set with `std::setw()` supplies the wrap width and is consumed by the
insertion. The default is 80 display columns.

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

When inserting a `text_style` to start styling directly, insert an empty style
after the text to reset the terminal. Both insertions check the destination.

```cpp
using namespace tjg::color;
using enum term_color;
std::cout << fg(red) << "Warning" << text_style{};
```

## See also

[Standard stream insertion](https://en.cppreference.com/w/cpp/io/basic_ostream/operator_ltlt2.html).
