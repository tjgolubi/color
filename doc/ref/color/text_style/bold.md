# [`tjg::color::bold`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L312)

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto bold(bool enable = true) noexcept -> text_style;
constexpr auto bold(text_style style, bool enable = true) noexcept
  -> text_style;
```

## Description

By default enables increased intensity.

### New style: `bold(bool enable)`

Starts with an empty [`text_style`](text_style/index.md). Enables the attribute when `enable` is true (the default); otherwise returns an empty style.

### Existing style: `bold(text_style style, bool enable)`

Starts with a copy of `style`, enabling or disabling this attribute according to `enable`. Other attributes, colors, and the absolute flag are preserved.

## See also

[Styled-text overload](../styled_text/bold.md), [`text_style::bold`](text_style/bold.md).
