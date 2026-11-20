# `tjg::color::rgb`

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
struct rgb {
  using value_type = std::uint32_t;
  using chan_type = std::uint8_t;
  chan_type r, g, b;

  constexpr rgb() noexcept;
  constexpr rgb(int r, int g, int b) noexcept;
  constexpr explicit rgb(value_type hex) noexcept;
  constexpr rgb(term_color color) noexcept;
  constexpr explicit operator value_type() const noexcept;
  constexpr auto operator<=>(const rgb&) const noexcept -> std::strong_ordering;
  constexpr auto operator|=(rgb rhs) noexcept -> rgb&;
  friend constexpr auto operator|(rgb lhs, rgb rhs) noexcept -> rgb;
};
```

## Description

A [truecolor](https://en.wikipedia.org/wiki/Color_depth#True_color_(24-bit)) value with independent red, green, and blue channels.

Named colors are constexpr static members. See the [swatches](../../../../named-colors.md) and the [constant list](rgb-constants.md). Use [`color()`](../color.md) to construct a custom shade from normalized components.

## Nested types

| Name         | Definition                                            |
| ---          | ---                                                   |
| `value_type` | `std::uint32_t`, used for packed `0x00RRGGBB` values. |
| `chan_type`  | `std::uint8_t`, used for each channel.                |

## Data members

| Name                                    | Description                  |
| ---                                     | ---                          |
| `r`                                     | Red channel.                 |
| `g`                                     | Green channel.               |
| `b`                                     | Blue channel.                |
| [Named RGB constants](rgb-constants.md) | Constexpr static RGB values. |

## Member functions

| Name                                              | Description                                                                     |
| ---                                               | ---                                                                             |
| [`rgb`](constructor.md)                           | Constructs the value; see the constructor overloads.                            |
| [`operator=`](operator-assignment.md)             | Assignment replaces the three RGB channels from the source and returns `*this`. |
| [`operator value_type`](operator-value_type.md)   | Converts to `value_type`.                                                       |
| [`operator<=>`](operator-three-way-comparison.md) | Compares red, then green, then blue and returns a `std::strong_ordering`.       |
| [`operator==`](operator-equal.md)                 | Compares the three color channels for equality.                                 |
| [`operator\|=`](operator-or-assignment.md)        | Takes the bitwise OR of corresponding channels in place and returns `*this`.    |

## Non-member functions

| Name                           | Description                                                 |
| ---                            | ---                                                         |
| [`operator\|`](operator-or.md) | Returns the bitwise OR of corresponding channels.           |
| [`color`](../color.md)         | Creates an RGB value from normalized channels or grayscale. |

## Helper classes

| Name                                 | Description                                   |
| ---                                  | ---                                           |
| [`std::hash<rgb>`](../hash/index.md) | Hash support for use in unordered containers. |
