# [`tjg::color::blink`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L344)

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto blink(bool enable = true) noexcept -> text_style;
constexpr auto blink(text_style style, bool enable = true) noexcept
  -> text_style;
```

## Description

By default enables blinking.

### New style: `blink(bool enable)`

Starts with an empty [`text_style`](text_style/index.md). Enables the attribute when `enable` is true (the default); otherwise returns an empty style.

### Existing style: `blink(text_style style, bool enable)`

Starts with a copy of `style`, enabling or disabling this attribute according to `enable`. Other attributes, colors, and the absolute flag are preserved.

## See also

[Styled-text overload](../styled_text/blink.md), [`text_style::blink`](text_style/blink.md).
