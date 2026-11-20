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

Parses standard `ESC[...m` SGR into [owned styled text](../styled_text/basic_styled_text/index.md). Consecutive SGR sequences update one style. The first reset begins an absolute group for subsequent text. Later resets clear the style within that group, and text before the first reset remains relative.

Non-SGR escapes and malformed SGR remain in the text. Unknown valid SGR parameters are ignored. The result represents appearance, so rendering can produce a different byte sequence. See the [parsing walkthrough](../../../styled.md#parsing-sgr-text).
