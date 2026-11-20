# `tjg::color::rgb::operator==`

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared by the defaulted operator<=>.
constexpr auto operator==(const rgb&) const noexcept -> bool;
```

Compares the three color channels for equality. Also supports `!=` through the rewritten comparison.
