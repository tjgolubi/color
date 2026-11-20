# `tjg::color::text_style::set`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto set(emphasis em, bool enable = true) noexcept -> text_style&;
```

## Description

Enables all bits in `em` when `enable` is true, or clears them otherwise. Other bits are preserved. Returns `*this`.
