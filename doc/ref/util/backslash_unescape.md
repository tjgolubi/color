# `tjg::backslash_unescape`

Header: [`<tjg/backslash.hpp>`](index.md#tjgbackslashhpp).

## Synopsis

```cpp
template<CharType Char>
constexpr auto backslash_unescape(std::basic_string_view<Char> input)
  -> std::basic_string<Char>;
constexpr auto backslash_unescape(std::string_view input) -> std::string;
constexpr auto backslash_unescape(std::wstring_view input) -> std::wstring;
```

Returns an owning copy with backslash escapes decoded. Surrounding quotes are preserved. Malformed input can throw. The string has the input character type. See [`backslash_unescape_to`](backslash_unescape_to.md) for the accepted syntax and the iterator overloads.
