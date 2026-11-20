# [`tjg::color::gray::operator==`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L383)

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared by the defaulted operator<=>.
constexpr auto operator==(const gray&) const noexcept -> bool;
```

## Description

Compares the gray index for equality. Also supports `!=` through the rewritten comparison.
