# `tjg::color::rgb::operator=`

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared.
constexpr auto operator=(const rgb&) noexcept -> rgb&;
constexpr auto operator=(rgb&&) noexcept -> rgb&;
```

Assignment replaces the three RGB channels from the source and returns `*this`.
