# `tjg::color::reverse`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto reverse(bool enable = true) noexcept -> text_style;
constexpr auto reverse(text_style style, bool enable = true) noexcept
  -> text_style;
```

## Description

By default enables reversed foreground and background.

### New style: `reverse(bool enable)`

Starts with an empty [`text_style`](text_style/index.md). Enables the attribute when `enable` is true (the default); otherwise returns an empty style.

### Existing style: `reverse(text_style style, bool enable)`

Starts with a copy of `style`, enabling or disabling this attribute according to `enable`. Other attributes, colors, and the absolute flag are preserved.

## See also

[Styled-text overload](../styled_text/reverse.md), [`text_style::reverse`](text_style/reverse.md).
