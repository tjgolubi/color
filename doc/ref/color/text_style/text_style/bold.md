# `tjg::color::text_style::bold`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto bold(bool enable = true) noexcept -> text_style&;
```

## Description

Enables increased intensity when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_bold`](is_bold.md) to query the attribute or the [free function](../bold.md) to obtain a new style.
