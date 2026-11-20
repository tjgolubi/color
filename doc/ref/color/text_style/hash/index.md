# `std::hash<tjg::color::text_style>`

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
template<> struct std::hash<tjg::color::text_style>;
```

## Description

Provides a standard hash for [`tjg::color::text_style`](../text_style/index.md),
so styles can be keys in unordered containers.

## Member functions

| Name                             | Description                                                                             |
| ---                              | ---                                                                                     |
| [`operator()`](operator-call.md) | Returns a hash for the stored style, including colors, emphasis, and the absolute flag. |
