# `tjg::color::text_style::italic`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto italic(bool enable = true) noexcept -> text_style&;
```

## Description

Enables italics when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_italic`](is_italic.md) to query the attribute or the [free function](../italic.md) to obtain a new style.
