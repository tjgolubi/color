# `tjg::color::bg`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto bg(color_t background) noexcept -> text_style;
```

Returns a [`text_style`](text_style.md) with the supplied background color. Passing [`no_color`](../colors/no_color.md) produces an empty style.
