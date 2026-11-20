# `tjg::color::to_rgb`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
template<Color T>
constexpr auto to_rgb(const T& color) noexcept -> rgb;
constexpr auto to_rgb(no_color_t color) noexcept -> no_color_t;
constexpr auto to_rgb(const color_t& color) noexcept -> color_t;
```

## Description

Returns a fixed RGB equivalent without changing the input.

### Concrete color: `to_rgb(const T& color)`

Accepts a [concrete color](Color.md). RGB is unchanged; terminal, cube, and gray colors use their [fixed palettes](xterm-palette.md).

### Unspecified color: `to_rgb(no_color_t color)`

Preserves the unspecified value, returning `no_color_t`.

### Variant: `to_rgb(const color_t& color)`

Returns a [`color_t`](color_t.md) holding `rgb` if specified, or `no_color_t` otherwise.

## Parameters

| Parameter | Description                                                     |
| ---       | ---                                                             |
| `color`   | Concrete color, unspecified color, or color variant to convert. |

## Return value

`rgb` for a concrete color, `no_color_t` for an unspecified color, or a `color_t` holding the converted alternative for a variant.
