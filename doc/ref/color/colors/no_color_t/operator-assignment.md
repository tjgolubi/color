# `tjg::color::no_color_t::operator=`

Type: [`tjg::color::no_color_t`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared.
constexpr auto operator=(const no_color_t&) noexcept -> no_color_t&;
constexpr auto operator=(no_color_t&&) noexcept -> no_color_t&;
```

Assignment replaces the unspecified-color value from the source and returns `*this`.
