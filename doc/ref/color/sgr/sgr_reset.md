# [`tjg::color::sgr_reset`](https://github.com/tjgolubi/color/blob/bf01e2dda7a63533f350ec19807749fca60a40cb/include/tjg/color/bits/sgr-support.hpp#L47)

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char = char>
constexpr auto sgr_reset() noexcept -> std::basic_string_view<Char>;
```

## Description

Returns a four-character view of `ESC[0m` in static storage. Writing it resets the terminal’s colors and emphasis to defaults. Use `sgr_reset<wchar_t>()` for wide output.
