# `tjg::color::gray::index`

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto index() const noexcept -> int;
```

## Description

Returns the zero-based gray palette index without modifying the color.

## Return value

The stored gray index, in `0..23`.

## See also

[Xterm-default palette](../xterm-palette.md), [RGB conversion](operator-rgb.md).
