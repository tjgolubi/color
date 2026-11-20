# `tjg::color::underlay`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto underlay(text_style base, text_style defaults) noexcept
  -> text_style;
```

## Description

Colors from `defaults` fill unspecified channels in `base`. The result combines emphasis attributes and the absolute flag. The input styles are unchanged. See also the [styled-text overload](../styled_text/underlay.md).

## See also

[`text_style::underlay`](text_style/underlay.md).
