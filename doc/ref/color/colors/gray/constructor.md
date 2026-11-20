# `tjg::color::gray::gray`

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr gray() noexcept;

constexpr explicit gray(int index) noexcept;

constexpr gray(const gray&) noexcept;
```

## Description

Constructs a gray palette index.

### Default construction: `gray()`

Selects index zero, whose fixed RGB equivalent is `{8, 8, 8}`.

### Indexed construction: `gray(int index)`

Accepts `0..23`. Assertion-enabled builds check the range. The current implementation clamps when assertions are disabled.

### Copy construction: `gray(const gray&)`

Preserves the source index.

## Parameters

| Parameter | Description                       |
| ---       | ---                               |
| `index`   | Zero-based gray index in `0..23`. |
