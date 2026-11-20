# `tjg::backslash_unescape_to`

Header: [`<tjg/backslash.hpp>`](index.md#tjgbackslashhpp).

## Synopsis

```cpp
template<CharType Char, std::output_iterator<Char> OutputIt>
constexpr auto backslash_unescape_to(OutputIt out, std::basic_string_view<Char> input)
  -> OutputIt;
template<std::output_iterator<char> OutputIt>
constexpr auto backslash_unescape_to(OutputIt out, std::string_view input) -> OutputIt;
template<std::output_iterator<wchar_t> OutputIt>
constexpr auto backslash_unescape_to(OutputIt out, std::wstring_view input) -> OutputIt;
```

Decodes escapes in one pass and returns the advanced iterator. Recognizes `\a`, `\b`, `\e`, `\f`, `\n`, `\r`, `\t`, `\v`, `\\`, `\"`, `\'`, and `\?`. `\x` takes exactly two hexadecimal digits. Octal escapes take one to three digits and must fit in `0..255`.

`\u` and `\U` take four and eight hex digits, respectively. A valid scalar is emitted as UTF-8 for `char`, UTF-16 for 16-bit `wchar_t`, or UTF-32 for 32-bit `wchar_t`.

Unknown or malformed escapes and Unicode surrogate values throw `std::invalid_argument`. Octal overflow and values above `U+10FFFF` throw `std::out_of_range`. Previously written output is retained. The output must preserve unread input. See [`backslash_unescape`](backslash_unescape.md) for the string-returning overloads.
