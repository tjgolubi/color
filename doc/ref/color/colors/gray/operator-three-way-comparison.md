# [`tjg::color::gray::operator<=>`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L402)

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator<=>(const gray&) const noexcept -> std::strong_ordering;
```

## Description

Compares the gray indices and returns a `std::strong_ordering`. The defaulted comparison also provides equality, and relational operators use the three-way comparison.
