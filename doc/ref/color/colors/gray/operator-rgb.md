# `tjg::color::gray::operator rgb`

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr operator rgb() const noexcept;
```

## Description

Converts implicitly to [`rgb`](../rgb/index.md). Each channel is `8 + 10 * index()`.
