# `tjg::color::basic_styled_text::style`

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
