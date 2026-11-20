# `std::hash<tjg::color::text_style>::operator()`

Type: [`std::hash<tjg::color::text_style>`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
auto operator()(tjg::color::text_style value) const noexcept -> std::size_t;
```

## Description

Returns a hash for the stored style, including colors, emphasis, and the
absolute flag. Equal styles hash equally. Hash values are suitable for
in-process lookup.
