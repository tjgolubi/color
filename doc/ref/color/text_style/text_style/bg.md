# `tjg::color::text_style::bg`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto bg() const noexcept -> color_t;

constexpr auto bg(color_t color) noexcept -> text_style&;
```

## Description

Reads or changes the background.

### Getter: `bg()`

Returns the background by value.

### Setter: `bg(color_t color)`

Replaces the background and returns `*this`. Pass [`no_color`](../../colors/no_color.md) to clear it.

## See also

[Free function](../bg.md).
