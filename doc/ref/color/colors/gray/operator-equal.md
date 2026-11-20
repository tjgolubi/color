# `tjg::color::gray::operator==`

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared by the defaulted operator<=>.
constexpr auto operator==(const gray&) const noexcept -> bool;
```

Compares the gray index for equality. Also supports `!=` through the rewritten comparison.
