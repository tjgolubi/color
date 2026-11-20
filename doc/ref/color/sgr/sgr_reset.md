# `tjg::color::sgr_reset`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char = char>
constexpr auto sgr_reset() noexcept -> std::basic_string_view<Char>;
```

Returns a four-character view of `ESC[0m` in static storage. Writing it resets the terminal’s colors and emphasis to defaults. Use `sgr_reset<wchar_t>()` for wide output.
