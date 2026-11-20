# `std::hash` specializations for colors

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
template<> struct std::hash<tjg::color::term_color>;
template<> struct std::hash<tjg::color::rgb>;
template<> struct std::hash<tjg::color::cube>;
template<> struct std::hash<tjg::color::gray>;
template<> struct std::hash<tjg::color::color_t>;
```

## Description

Provides `std::hash` specializations for [`tjg::color::term_color`](../term_color.md), [`tjg::color::rgb`](../rgb/index.md), [`tjg::color::cube`](../cube/index.md), [`tjg::color::gray`](../gray/index.md), [`tjg::color::color_t`](../color_t.md).
Use them for keys in standard unordered containers.

## Member functions

| Name                             | Description                     |
| ---                              | ---                             |
| [`operator()`](operator-call.md) | Returns a hash of the argument. |
