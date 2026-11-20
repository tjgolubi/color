# `tjg::color::text_style::text_style`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr text_style(emphasis emp = emphasis::none, color_t fg = {},
                     color_t bg = {}) noexcept;

constexpr text_style(color_t fg, color_t bg = {},
                     emphasis emp = emphasis::none) noexcept;
```

Constructs a relative style from emphasis and optional colors or from a foreground color with optional background and emphasis. With no arguments, the style is empty. Use [`no_color`](../../colors/no_color.md) for an unspecified channel.
