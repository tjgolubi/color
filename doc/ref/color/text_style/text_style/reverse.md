# `tjg::color::text_style::reverse`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto reverse(bool enable = true) noexcept -> text_style&;
```

## Description

Enables reverse video when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_reverse`](is_reverse.md) to query the attribute or the [free function](../reverse.md) to obtain a new style.
