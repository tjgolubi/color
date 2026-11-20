# `std::formatter` specializations

Header: [`<tjg/color.hpp>`](index.md).

| Formatted type | Default representation | Debug representation (`?`) |
| --- | --- | --- |
| `rgb`, `term_color`, `gray`, `cube`, `color_t`, `no_color_t` | Readable color notation | Same notation |
| `emphasis` | Attribute names in braces | Compact attribute codes |
| `text_style` | Opening SGR sequence | Readable style notation |
| `basic_styled_text<Char>` | Rendered styled text | Structural representation with quoted text |
| [`styled`](styled.md) result | Styled wrapped value | Determined by the wrapped formatter |

The specializations support narrow and wide formatting for matching character types. For detailed format specifications and examples, see [Standard formatting](../../index.md#standard-formatting), [Readable style output](../../text-style.md#readable-style-output), and [Formatting and plain text](../../styled.md#formatting-and-plain-text).
