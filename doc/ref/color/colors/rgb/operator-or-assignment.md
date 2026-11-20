# `tjg::color::rgb::operator|=`

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator|=(rgb rhs) noexcept -> rgb&;
```

Takes the bitwise OR of corresponding channels in place and returns `*this`. See also [`operator|`](operator-or.md).
