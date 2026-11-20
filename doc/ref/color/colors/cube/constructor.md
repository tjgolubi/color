# `tjg::color::cube::cube`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr cube() noexcept;

constexpr explicit cube(int index) noexcept;

constexpr cube(int r, int g, int b) noexcept;

constexpr cube(const cube&) noexcept;
```

Default construction sets all channels to zero. Pass three indices in `0..5` or a combined index in `0..215`. A combined index is decomposed with red as the most significant channel and blue as the least significant. Assertion-enabled builds check the range. The current implementation clamps when assertions are disabled. The copy constructor preserves all channels.
