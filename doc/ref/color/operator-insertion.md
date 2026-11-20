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

## Supported operands

| Right operand | Output |
| --- | --- |
| Color value, `color_t`, `no_color_t`, or `emphasis` | Readable notation via [`write_value`](write_value.md), with width, fill, and alignment as for string insertion. |
| [`text_style`](text_style/text_style.md) | Opening SGR only. An empty style emits a terminal reset. Pending stream width is preserved. |
| [`styled`](styled.md) result | Inserts the borrowed value with its style. Width, fill, precision, and alignment apply to the wrapped insertion. |
| [`basic_styled_text`](styled_text/basic_styled_text.md) | Renders the styled text with its nested styles. Stream width applies to the visible width of the result. |

Supports `char` and `wchar_t` streams where the wrapped value is insertable. Returns `os`. See the [stream insertion examples](../../print.md#styled-stream-insertion).
