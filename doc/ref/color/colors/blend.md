# `tjg::color::blend`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
template<Color First, Color Second, Color... Colors>
constexpr auto blend(First first, Second second, Colors... rest) noexcept -> rgb;

// Second and Colors must be concrete colors, color_t, or no_color_t.
template<typename Second, typename... Colors>
constexpr auto blend(color_t first, Second second, Colors... rest) noexcept
  -> color_t;
```

Averages two or more colors. Concrete colors convert to fixed RGB equivalents. Each channel is summed before division and fractional results round down.

If any input is a `color_t` or `no_color_t`, the result is a [`color_t`](color_t.md). Unspecified inputs are excluded from the average. Zero specified inputs give `no_color`; one preserves its kind and value; two or more yield `rgb`. See also [style blending](../text_style/blend.md).
