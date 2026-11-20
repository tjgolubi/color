# `tjg::color::text_style::emph`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto emph() const noexcept -> emphasis;

constexpr auto emph(emphasis em) noexcept -> text_style&;
```

## Description

Reads or replaces the [emphasis attributes](../emphasis.md).

### Getter: `emph()`

Returns the emphasis mask by value.

### Setter: `emph(emphasis em)`

Replaces the entire mask and returns `*this`. To change selected attributes, use [`set`](set.md).
