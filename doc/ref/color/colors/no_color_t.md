# `tjg::color::no_color_t`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
struct no_color_t {
  constexpr auto operator<=>(const no_color_t&) const noexcept = default;
};
```

Represents an unspecified color channel. See the [`no_color`](no_color.md) constant and the [`color_t`](color_t.md) variant.
