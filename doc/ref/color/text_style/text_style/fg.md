# `tjg::color::text_style::fg`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto fg() const noexcept -> color_t;

constexpr auto fg(color_t color) noexcept -> text_style&;
```

The getter returns the foreground by value. The setter replaces the foreground and returns `*this`. Pass [`no_color`](../../colors/no_color.md) to clear it. See also the [free function](../fg.md).
