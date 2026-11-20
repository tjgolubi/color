# `tjg::color::cube::b`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto b() const noexcept -> int;

constexpr auto b(int value) noexcept -> cube&;
```

## Description

Reads or changes the blue channel index.

### Getter: `b()`

Returns the blue channel index in `0..5`.

### Setter: `b(int value)`

Replaces this index, preserves the other channels, and returns `*this`. Assertion-enabled builds check the range. The current implementation clamps when assertions are disabled.
