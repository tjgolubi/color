# `tjg::color::cube::r`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto r() const noexcept -> int;

constexpr auto r(int value) noexcept -> cube&;
```

## Description

Reads or changes the red channel index.

### Getter: `r()`

Returns the red channel index in `0..5`.

### Setter: `r(int value)`

Replaces this index, preserves the other channels, and returns `*this`. Assertion-enabled builds check the range. The current implementation clamps when assertions are disabled.
