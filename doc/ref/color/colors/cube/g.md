# `tjg::color::cube::g`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto g() const noexcept -> int;

constexpr auto g(int value) noexcept -> cube&;
```

## Description

Reads or changes the green channel index.

### Getter: `g()`

Returns the green channel index in `0..5`.

### Setter: `g(int value)`

Replaces this index, preserves the other channels, and returns `*this`. Assertion-enabled builds check the range. The current implementation clamps when assertions are disabled.
