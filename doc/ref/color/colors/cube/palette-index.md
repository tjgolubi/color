# `tjg::color::cube::index`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto index() const noexcept -> int;
```

## Description

Returns the zero-based cube palette index without modifying the color.

## Return value

The combined index `36 * r() + 6 * g() + b()`, in `0..215`.

## See also

[Xterm-default palette](../xterm-palette.md), [RGB conversion](operator-rgb.md).
