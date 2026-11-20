# `tjg::color::text_style::strike`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto strike(bool enable = true) noexcept -> text_style&;
```

## Description

Enables strike-through when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_strike`](is_strike.md) to query the attribute or the [free function](../strike.md) to obtain a new style.
