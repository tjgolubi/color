# `tjg::color::no_color_t`

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
struct no_color_t {
  constexpr auto operator<=>(const no_color_t&) const noexcept = default;
};
```

## Description

Represents an unspecified color channel. See the [`no_color`](../no_color.md) constant and the [`color_t`](../color_t.md) variant.

## Member functions

| Name                                              | Description                                                                          |
| ---                                               | ---                                                                                  |
| [`no_color_t`](constructor.md)                    | Constructs the value; see the constructor overloads.                                 |
| [`operator=`](operator-assignment.md)             | Assignment replaces the unspecified-color value from the source and returns `*this`. |
| [`operator<=>`](operator-three-way-comparison.md) | Compares two unspecified colors.                                                     |
| [`operator==`](operator-equal.md)                 | Compares the unspecified-color values for equality.                                  |
