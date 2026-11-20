# [`tjg::color::no_color_t::operator==`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L31)

Type: [`tjg::color::no_color_t`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared by the defaulted operator<=>.
constexpr auto operator==(const no_color_t&) const noexcept -> bool;
```

## Description

Compares the unspecified-color values for equality. Also supports `!=` through the rewritten comparison.
