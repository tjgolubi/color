# [`tjg::color::text_style::overlay`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L116)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto overlay(const text_style& other) noexcept -> text_style&;
```

## Description

Specified colors from `other` replace the corresponding colors in this style. The result combines emphasis attributes and the absolute flag. Returns `*this`. See also the [free function](../overlay.md).
