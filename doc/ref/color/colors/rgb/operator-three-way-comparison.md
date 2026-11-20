# `tjg::color::rgb::operator<=>`

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator<=>(const rgb&) const noexcept -> std::strong_ordering;
```

Compares red, then green, then blue and returns a `std::strong_ordering`. The defaulted comparison also provides equality, and relational operators use the three-way comparison.
