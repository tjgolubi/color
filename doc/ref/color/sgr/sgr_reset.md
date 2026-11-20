# [`tjg::color::sgr_reset`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/sgr_support.hpp#L47)

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char = char>
constexpr auto sgr_reset() noexcept -> std::basic_string_view<Char>;
```

## Description

Returns a four-character view of `ESC[0m` in static storage. Writing it resets the terminal’s colors and emphasis to defaults. Use `sgr_reset<wchar_t>()` for wide output.
