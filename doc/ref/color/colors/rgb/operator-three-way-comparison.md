# [`tjg::color::rgb::operator<=>`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L120)

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator<=>(const rgb&) const noexcept -> std::strong_ordering;
```

## Description

Compares red, then green, then blue and returns a `std::strong_ordering`. The defaulted comparison also provides equality, and relational operators use the three-way comparison.
