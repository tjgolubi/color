# `tjg::color::text_style::operator==`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator==(const text_style&) const noexcept -> bool;
```

## Description

Compares the stored foreground, background, emphasis, and absolute flag for equality. Color variants retain their kinds for comparison.
