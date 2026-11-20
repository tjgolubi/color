# `tjg::color::gray::gray`

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr gray() noexcept;

constexpr explicit gray(int index) noexcept;

constexpr gray(const gray&) noexcept;
```

Default construction selects index zero. The indexed constructor accepts `0..23`. Assertion-enabled builds check the range. The current implementation clamps when assertions are disabled. The copy constructor preserves the index.
