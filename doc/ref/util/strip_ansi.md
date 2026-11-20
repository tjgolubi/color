# `tjg::strip_ansi`

Header: [`<tjg/strip_ansi.hpp>`](index.md#tjgstrip_ansihpp).

## Synopsis

```cpp
template<CharType Char>
constexpr auto strip_ansi(std::basic_string_view<Char> input)
  -> std::basic_string<Char>;
constexpr auto strip_ansi(std::string_view input) -> std::string;
constexpr auto strip_ansi(std::wstring_view input) -> std::wstring;
```

## Description

Returns an owning copy with complete ESC-prefixed ANSI sequences removed. Handles CSI, OSC, DCS, SOS, PM, APC, and ordinary ESC sequences. OSC accepts BEL or ST termination, and other control strings require ST. Malformed or incomplete sequences, standalone C0 controls, and single-byte C1 controls are retained.

This is escape removal. It does not simulate cursor motion or terminal editing. See the [styled-text overload](../color/sgr/strip_ansi.md) for stripping escapes while preserving styles.

### Character-type template: `std::basic_string_view<Char>`

Returns `std::basic_string<Char>` with the same character type as the input.

### Narrow and wide convenience overloads

Accept `std::string_view` or `std::wstring_view`, returning `std::string` or `std::wstring`, respectively.
