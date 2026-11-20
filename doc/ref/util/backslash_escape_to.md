# `tjg::backslash_escape_to`

Header: [`<tjg/backslash.hpp>`](index.md#tjgbackslashhpp).

## Synopsis

```cpp
template<CharType Char, std::output_iterator<Char> OutputIt>
constexpr auto backslash_escape_to(OutputIt out, std::basic_string_view<Char> input)
  -> OutputIt;
template<std::output_iterator<char> OutputIt>
constexpr auto backslash_escape_to(OutputIt out, std::string_view input) -> OutputIt;
template<std::output_iterator<wchar_t> OutputIt>
constexpr auto backslash_escape_to(OutputIt out, std::wstring_view input) -> OutputIt;
```

Writes escaped text and returns the advanced iterator. The standard control characters use short escapes, including `\e` for ESC. Double quotes and backslashes are escaped. Other C0 controls and DEL use `\x` followed by two hex digits. Other code units pass through.

The output must preserve unread input. See [`backslash_escape`](backslash_escape.md) for the string-returning overloads.
