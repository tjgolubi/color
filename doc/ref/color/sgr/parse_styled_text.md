# `tjg::color::parse_styled_text`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
auto parse_styled_text(std::basic_string_view<Char> input)
  -> basic_styled_text<Char>;
auto parse_styled_text(std::string_view input) -> styled_text;
auto parse_styled_text(std::wstring_view input) -> wstyled_text;
```

## Description

Parses standard `ESC[...m` [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) into [owned styled text](../styled_text/basic_styled_text/index.md). Consecutive SGR sequences update one style. The first reset begins an absolute group for subsequent text. Later resets clear the style within that group, and text before the first reset remains relative.

Non-SGR escapes and malformed SGR remain in the text. Unknown valid SGR parameters are ignored. The result represents appearance, so rendering can produce a different byte sequence. See the [parsing walkthrough](../../../styled.md#parsing-sgr-text).

### Character-type template: `std::basic_string_view<Char>`

Returns `basic_styled_text<Char>` for the matching input character type.

### Narrow and wide convenience overloads

Accept `std::string_view` or `std::wstring_view`, returning `styled_text` or `wstyled_text`, respectively.

## Parameters

| Parameter | Description                                                      |
| ---       | ---                                                              |
| `input`   | Text containing SGR sequences, with the matching character type. |

## Return value

Owned styled text with the input character type.
