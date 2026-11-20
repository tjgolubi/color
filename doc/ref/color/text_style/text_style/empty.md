# [`tjg::color::text_style::empty`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L83)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto empty() const noexcept -> bool;
```

## Description

Returns true if neither color is specified, there is no emphasis, and the absolute flag is clear. An absolute-only style is nonempty.
