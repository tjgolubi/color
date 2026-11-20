# `tjg::color::overlay`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto overlay(text_style base, text_style overrides) noexcept
  -> text_style;
```

## Description

Specified colors from `overrides` replace matching colors in `base`. The result combines emphasis attributes and the absolute flag. The input styles are unchanged. See also the [styled-text overload](../styled_text/overlay.md).

## See also

[`text_style::overlay`](text_style/overlay.md).
