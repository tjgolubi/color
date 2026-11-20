# `tjg::color::text_style::emph`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto emph() const noexcept -> emphasis;

constexpr auto emph(emphasis em) noexcept -> text_style&;
```

The getter returns the emphasis mask by value. The setter replaces the entire mask and returns `*this`. To change selected bits, use [`set`](set.md).
