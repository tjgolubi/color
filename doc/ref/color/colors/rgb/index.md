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

A truecolor value with independent red, green, and blue channels.

## Construction and conversion

| Form | Meaning |
| --- | --- |
| `rgb{}` | Black (`#000000`). |
| `rgb{r, g, b}` | Three components in `0..255`. |
| `rgb{hex}` | The low 24 bits of `hex`, interpreted as `0xRRGGBB`. |
| `rgb{color}` | The fixed Xterm-default RGB equivalent of a [`term_color`](../term_color.md). |
| `static_cast<rgb::value_type>(value)` | The numeric value `0x00RRGGBB`. |

The component constructor asserts on invalid values in assertion-enabled builds. The current implementation clamps channels when assertions are disabled.

## Operations

Equality compares channels, and ordering compares red, then green, then blue. `operator|` combines channels by bitwise OR, and `operator|=` applies the operation in place and returns `*this`. [`std::hash<rgb>`](../hash/index.md) is provided.

## Named constants

Named colors are constexpr static members. See the [swatches](../../../../named-colors.md) and the [constant list](rgb-constants.md). Use [`color()`](../color.md) to construct a custom shade from normalized components.

## Member functions

- [`rgb`](constructor.md)
- [`operator=`](operator-assignment.md)
- [`operator value_type`](operator-value_type.md)
- [`operator<=>`](operator-three-way-comparison.md)
- [`operator==`](operator-equal.md)
- [`operator|=`](operator-or-assignment.md)

## Non-member functions

- [`operator|`](operator-or.md)
