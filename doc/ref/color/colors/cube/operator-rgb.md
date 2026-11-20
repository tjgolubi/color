# [`tjg::color::cube::operator rgb`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L497)

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr operator rgb() const noexcept;
```

## Description

Converts implicitly to [`rgb`](../rgb/index.md). Indices `0..5` map to the fixed channel levels `{0, 95, 135, 175, 215, 255}`.
