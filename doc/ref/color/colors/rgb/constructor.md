# [`tjg::color::rgb::rgb`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L96)

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr rgb() noexcept;

constexpr rgb(int r, int g, int b) noexcept;

constexpr explicit rgb(value_type hex) noexcept;

constexpr rgb(term_color color) noexcept;
```

## Description

Constructs an RGB value using one of the following forms.

### Default construction: `rgb()`

Produces black (`#000000`).

### Channel values: `rgb(int r, int g, int b)`

Sets the three channels. Each input must be in `0..255`. Assertion-enabled builds check the range. The current implementation clamps channels when assertions are disabled.

### Packed value: `rgb(value_type hex)`

Interprets the low 24 bits of [`value_type`](index.md#nested-types) as `0xRRGGBB`.

### Terminal color: `rgb(term_color color)`

Uses the fixed [Xterm-default RGB equivalent](../xterm-palette.md) of the supplied [`term_color`](../term_color.md).

## Parameters

| Parameter     | Description                                           |
| ---           | ---                                                   |
| `r`, `g`, `b` | Integer channel values in `0..255`.                   |
| `hex`         | Packed value whose low 24 bits encode `0xRRGGBB`.     |
| `color`       | Named terminal palette entry to convert to fixed RGB. |
