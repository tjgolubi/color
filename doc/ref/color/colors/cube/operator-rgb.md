# `tjg::color::cube::operator rgb`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr operator rgb() const noexcept;
```

Converts implicitly to [`rgb`](../rgb/index.md). Indices `0..5` map to the fixed channel levels `{0, 95, 135, 175, 215, 255}`.
