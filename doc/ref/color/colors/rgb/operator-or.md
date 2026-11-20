# [`operator|` for `tjg::color::rgb`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L133)

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator|(rgb lhs, rgb rhs) noexcept -> rgb;
```

## Description

Returns the bitwise OR of corresponding channels. The input values are unchanged. See also [`operator|=`](operator-or-assignment.md).
