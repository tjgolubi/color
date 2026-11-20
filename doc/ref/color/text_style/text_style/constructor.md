# [`tjg::color::text_style::text_style`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L66)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr text_style(emphasis emp = emphasis::none, color_t fg = {},
                     color_t bg = {}) noexcept;

constexpr text_style(color_t fg, color_t bg = {},
                     emphasis emp = emphasis::none) noexcept;
```

## Description

Constructs a relative style. Use [`no_color`](../../colors/no_color.md) for an unspecified channel.

### Emphasis first: `text_style(emphasis emp, color_t fg, color_t bg)`

Sets emphasis and the optional foreground and background. With no arguments, constructs an empty style: no emphasis and both colors unspecified.

### Color first: `text_style(color_t fg, color_t bg, emphasis emp)`

Sets the foreground, optional background, and optional emphasis. Background defaults to unspecified and emphasis defaults to `emphasis::none`.
