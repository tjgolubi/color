# [`tjg::color::rgb::operator|=`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L124)

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator|=(rgb rhs) noexcept -> rgb&;
```

## Description

Takes the bitwise OR of corresponding channels in place and returns `*this`. See also [`operator|`](operator-or.md).
