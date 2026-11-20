# `tjg::color::text_style::empty`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto empty() const noexcept -> bool;
```

## Description

Returns true if neither color is specified, there is no emphasis, and the absolute flag is clear. An absolute-only style is nonempty.
