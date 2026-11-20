# `tjg::color::cube::operator==`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared by the defaulted operator<=>.
constexpr auto operator==(const cube&) const noexcept -> bool;
```

Compares the three channel indices for equality. Also supports `!=` through the rewritten comparison.
