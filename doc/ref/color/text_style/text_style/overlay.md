# `tjg::color::text_style::overlay`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto overlay(const text_style& other) noexcept -> text_style&;
```

## Description

Specified colors from `other` replace the corresponding colors in this style. The result combines emphasis attributes and the absolute flag. Returns `*this`. See also the [free function](../overlay.md).
