# `tjg::color::text_style::operator<=>`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator<=>(const text_style&) const noexcept -> std::strong_ordering;
```

## Description

Compares the stored style components in their declaration order. Returns a `std::strong_ordering`. The relational operators use this comparison.
