# `tjg::color::fg`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto fg(color_t foreground) noexcept -> text_style;
```

## Description

Returns a [`text_style`](text_style/index.md) with the supplied foreground color. Passing [`no_color`](../colors/no_color.md) produces an empty style.

## See also

[`text_style::fg`](text_style/fg.md).
