# [`tjg::backslash_unescape_to`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/backslash.hpp#L131)

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

## Description

Decodes escapes in one pass and returns the advanced iterator. Recognizes `\a`, `\b`, `\e`, `\f`, `\n`, `\r`, `\t`, `\v`, `\\`, `\"`, `\'`, and `\?`. `\x` takes exactly two hexadecimal digits. Octal escapes take one to three digits and must fit in `0..255`.

`\u` and `\U` take four and eight hex digits, respectively. A valid scalar is emitted as UTF-8 for `char`, UTF-16 for 16-bit `wchar_t`, or UTF-32 for 32-bit `wchar_t`.

The output must preserve unread input. See [`backslash_unescape`](backslash_unescape.md) for the string-returning overloads.

### Character-type template: `std::basic_string_view<Char>`

Writes through an output iterator accepting the input character type.

### Narrow and wide convenience overloads

Accept `std::string_view` with a character output iterator, or `std::wstring_view` with a wide-character output iterator. Each returns the advanced iterator.

## Exceptions

`std::invalid_argument` for unknown or malformed escapes and Unicode surrogate values.
`std::out_of_range` for octal overflow or values above `U+10FFFF`.
Previously written output is retained.
