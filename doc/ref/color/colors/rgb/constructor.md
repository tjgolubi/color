# `tjg::color::rgb::rgb`

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr rgb() noexcept;

constexpr rgb(int r, int g, int b) noexcept;

constexpr explicit rgb(value_type hex) noexcept;

constexpr rgb(term_color color) noexcept;
```

The default constructor produces black. With three integers, each channel must be in `0..255`. Assertion-enabled builds check this range. The current implementation clamps channels when assertions are disabled. The packed overload interprets the low 24 bits as `0xRRGGBB`. Conversion from [`term_color`](../term_color.md) uses the fixed Xterm-default palette.
