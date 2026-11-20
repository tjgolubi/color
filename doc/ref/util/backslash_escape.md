# `tjg::backslash_escape`

Header: [`<tjg/backslash.hpp>`](index.md#tjgbackslashhpp).

## Synopsis

```cpp
template<CharType Char>
constexpr auto backslash_escape(std::basic_string_view<Char> input)
  -> std::basic_string<Char>;
constexpr auto backslash_escape(std::string_view input) -> std::string;
constexpr auto backslash_escape(std::wstring_view input) -> std::wstring;
```

Returns an owning copy with escaped control characters and punctuation. For example, an ESC character becomes the two characters `\e`. The string has the input character type. See [`backslash_escape_to`](backslash_escape_to.md) for the accepted syntax and the iterator overloads.
