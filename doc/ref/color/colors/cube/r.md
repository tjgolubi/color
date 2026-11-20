# [`tjg::color::cube::r`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L443)

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
