# [`tjg::backslash_unescape`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/backslash.hpp#L248)

Header: [`<tjg/backslash.hpp>`](index.md#tjgbackslashhpp).

## Synopsis

```cpp
template<CharType Char>
constexpr auto backslash_unescape(std::basic_string_view<Char> input)
  -> std::basic_string<Char>;
constexpr auto backslash_unescape(std::string_view input) -> std::string;
constexpr auto backslash_unescape(std::wstring_view input) -> std::wstring;
```

## Description

Returns a copy with backslash escapes decoded. Surrounding quotes are preserved. Malformed input can throw. The string has the input character type. See [`backslash_unescape_to`](backslash_unescape_to.md) for the accepted syntax and the iterator overloads.

### Character-type template: `std::basic_string_view<Char>`

Returns `std::basic_string<Char>` with the same character type as the input.

### Narrow and wide convenience overloads

Accept `std::string_view` or `std::wstring_view`, returning `std::string` or `std::wstring`, respectively.
