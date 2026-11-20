# `tjg::color::cube::operator<=>`

Type: [`tjg::color::cube`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator<=>(const cube&) const noexcept -> std::strong_ordering;
```

Compares the combined cube indices and returns a `std::strong_ordering`. The defaulted comparison also provides equality, and relational operators use the three-way comparison.
