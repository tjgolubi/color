# `std::formatter` specializations

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
// Representative specialization for matching character types.
template<tjg::CharType Char>
struct std::formatter<tjg::color::rgb, Char>;
// See the supported-type table below for the other specializations.
```

## Description

| Formatted type                                                                                                                                                                                                                   | Default representation                                                                                     | Debug representation (`?`)                 |
| ---                                                                                                                                                                                                                              | ---                                                                                                        | ---                                        |
| [`rgb`](../colors/rgb/index.md), [`term_color`](../colors/term_color.md), [`gray`](../colors/gray/index.md), [`cube`](../colors/cube/index.md), [`color_t`](../colors/color_t.md), [`no_color_t`](../colors/no_color_t/index.md) | Readable color notation                                                                                    | Same notation                              |
| [`emphasis`](../text_style/emphasis.md)                                                                                                                                                                                          | Attribute names in braces                                                                                  | Compact attribute codes                    |
| [`text_style`](../text_style/text_style/index.md)                                                                                                                                                                                | Opening [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) sequence | Readable style notation                    |
| [`basic_styled_text<Char>`](../styled_text/basic_styled_text/index.md)                                                                                                                                                           | Rendered styled text                                                                                       | Structural representation with quoted text |
| [`styled`](../styled.md) result                                                                                                                                                                                                  | Styled wrapped value                                                                                       | Determined by the wrapped formatter        |

The specializations support narrow and wide formatting for matching character types. For detailed format specifications and examples, see [Standard formatting](../../../index.md#standard-formatting), [Readable style output](../../../text-style.md#readable-style-output), and [Formatting and plain text](../../../styled.md#formatting-and-plain-text).

## Member functions

| Name                  | Description                                                                                        |
| ---                   | ---                                                                                                |
| [`parse`](parse.md)   | Parses the format specification and returns the iterator marking where parsing stopped.            |
| [`format`](format.md) | Writes the selected representation to the format context and returns the advanced output iterator. |
