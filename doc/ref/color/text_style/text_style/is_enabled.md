# [`tjg::color::text_style::is_enabled`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L241)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto is_enabled(emphasis em) const noexcept -> bool;
```

## Description

Returns true if any bit in `em` is enabled. If `em` is empty, returns `false`.
