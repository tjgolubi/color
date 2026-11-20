# [`tjg::color::text_style::operator==`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L277)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto operator==(const text_style&) const noexcept -> bool;
```

## Description

Compares the stored foreground, background, emphasis, and absolute flag for equality. Color variants retain their kinds for comparison.
