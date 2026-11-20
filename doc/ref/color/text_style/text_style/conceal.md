# `tjg::color::text_style::conceal`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto conceal(bool enable = true) noexcept -> text_style&;
```

## Description

Enables concealment when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_conceal`](is_conceal.md) to query the attribute or the [free function](../conceal.md) to obtain a new style.
