# [`tjg::color::basic_styled_text::style`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L93)

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto style() const noexcept -> text_style;

auto style(text_style value) noexcept -> basic_styled_text&;
```

## Description

Reads or replaces the outermost style.

### Getter: `style()`

Returns the outermost [`text_style`](../../text_style/text_style/index.md) by value.

### Setter: `style(text_style value)`

Replaces the outermost style, preserves child styles and text, and returns `*this`.
