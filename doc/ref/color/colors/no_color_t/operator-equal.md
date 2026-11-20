# `tjg::color::no_color_t::operator==`

Type: [`tjg::color::no_color_t`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared by the defaulted operator<=>.
constexpr auto operator==(const no_color_t&) const noexcept -> bool;
```

Compares the unspecified-color values for equality. Also supports `!=` through the rewritten comparison.
