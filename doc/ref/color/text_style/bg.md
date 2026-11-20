# [`tjg::color::bg`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L299)

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto bg(color_t background) noexcept -> text_style;
```

## Description

Returns a [`text_style`](text_style/index.md) with the supplied background color. Passing [`no_color`](../colors/no_color.md) produces an empty style.

## See also

[`text_style::bg`](text_style/bg.md).
