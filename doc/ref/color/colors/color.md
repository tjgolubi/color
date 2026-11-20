# `tjg::color::color`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
constexpr rgb color(double red, double green, double blue) noexcept;
constexpr rgb color(double grayscale) noexcept;
```

Returns an [`rgb`](rgb.md) from normalized inputs in `0.0..1.0`. The one-argument overload applies the same component to all three channels. In the current implementation, an interior value maps to the integer part of `256 * value`; the endpoints map to 0 and 255. Inputs below or above the range map to the nearest endpoint, and NaN maps to 0.

```cpp
using namespace tjg::color;
constexpr auto accent = color(0.1, 0.6, 1.0); // rgb{25, 153, 255}
constexpr auto shade = color(0.25);           // rgb::dark_gray
```
