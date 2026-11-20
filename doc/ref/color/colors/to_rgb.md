# `tjg::color::to_rgb`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
template<Color T>
constexpr auto to_rgb(const T& color) noexcept -> rgb;
constexpr auto to_rgb(no_color_t color) noexcept -> no_color_t;
constexpr auto to_rgb(const color_t& color) noexcept -> color_t;
```

Returns a fixed RGB equivalent of a [concrete color](Color.md). Terminal, cube, and gray values use their fixed palettes. For a [`color_t`](color_t.md), the result holds `rgb` if specified or `no_color_t` otherwise. The `no_color_t` overload preserves the unspecified value.
