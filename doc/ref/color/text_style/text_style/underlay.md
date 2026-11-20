# `tjg::color::text_style::underlay`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto underlay(const text_style& other) noexcept -> text_style&;
```

## Description

Colors from `other` fill the corresponding unspecified channels in this style. The result combines emphasis attributes and the absolute flag. Returns `*this`. See also the [free function](../underlay.md).
