# `tjg::color::wrap_sgr`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
auto wrap_sgr(const text_style& ts, std::basic_string_view<Char> sv)
  -> std::basic_string<Char>;
auto wrap_sgr(const text_style& ts, std::string_view sv) -> std::string;
```

Returns the opening SGR for `ts`, the literal text `sv`, and a terminal reset. Empty text produces an empty string. An empty relative style returns a copy of the input text. Embedded nulls, braces, and escape sequences are copied without interpretation. The result can allocate.

For wide text, supply a `std::wstring_view` or specify `wrap_sgr<wchar_t>` explicitly.
