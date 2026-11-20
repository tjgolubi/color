# [`tjg::color::text_style::fg`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L155)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto fg() const noexcept -> color_t;

constexpr auto fg(color_t color) noexcept -> text_style&;
```

## Description

Reads or changes the foreground.

### Getter: `fg()`

Returns the foreground by value.

### Setter: `fg(color_t color)`

Replaces the foreground and returns `*this`. Pass [`no_color`](../../colors/no_color.md) to clear it.

## See also

[Free function](../fg.md).
