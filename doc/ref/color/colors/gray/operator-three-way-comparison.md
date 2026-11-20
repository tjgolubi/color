# `tjg::color::gray::operator<=>`

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator<=>(const gray&) const noexcept -> std::strong_ordering;
```

## Description

Compares the gray indices and returns a `std::strong_ordering`. The defaulted comparison also provides equality, and relational operators use the three-way comparison.
