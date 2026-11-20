# `operator|` for `tjg::color::rgb`

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator|(rgb lhs, rgb rhs) noexcept -> rgb;
```

## Description

Returns the bitwise OR of corresponding channels. The input values are unchanged. See also [`operator|=`](operator-or-assignment.md).
