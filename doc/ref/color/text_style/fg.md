# `tjg::color::fg`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto fg(color_t foreground) noexcept -> text_style;
```

Returns a [`text_style`](text_style.md) with the supplied foreground color. Passing [`no_color`](../colors/no_color.md) produces an empty style.
