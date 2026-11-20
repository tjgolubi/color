# [`tjg::color::cube::cube`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L470)

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr cube() noexcept;

constexpr explicit cube(int index) noexcept;

constexpr cube(int r, int g, int b) noexcept;

constexpr cube(const cube&) noexcept;
```

## Description

Constructs a color in the indexed 6×6×6 cube.

### Default construction: `cube()`

Sets all three channel indices to zero.

### Combined index: `cube(int index)`

Accepts a combined index in `0..215`. Decomposes it with red as the most significant channel and blue as the least significant: `r = index / 36`, `g = (index / 6) % 6`, and `b = index % 6`. Assertion-enabled builds check the range. The current implementation clamps when assertions are disabled.

### Channel indices: `cube(int r, int g, int b)`

Accepts three indices in `0..5`. Assertion-enabled builds check each range. The current implementation clamps when assertions are disabled.

### Copy construction: `cube(const cube&)`

Preserves all source channel indices.

## Parameters

| Parameter     | Description                                 |
| ---           | ---                                         |
| `index`       | Combined cube index in `0..215`.            |
| `r`, `g`, `b` | Independent cube channel indices in `0..5`. |
