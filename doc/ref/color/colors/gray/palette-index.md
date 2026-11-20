# [`tjg::color::gray::index`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L410)

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
