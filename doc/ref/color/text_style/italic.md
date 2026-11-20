# `tjg::color::italic`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto italic(bool enable = true) noexcept -> text_style;
constexpr auto italic(text_style style, bool enable = true) noexcept
  -> text_style;
```

## Description

By default enables italics.

### New style: `italic(bool enable)`

Starts with an empty [`text_style`](text_style/index.md). Enables the attribute when `enable` is true (the default); otherwise returns an empty style.

### Existing style: `italic(text_style style, bool enable)`

Starts with a copy of `style`, enabling or disabling this attribute according to `enable`. Other attributes, colors, and the absolute flag are preserved.

## See also

[Styled-text overload](../styled_text/italic.md), [`text_style::italic`](text_style/italic.md).
