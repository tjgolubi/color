# [`tjg::color::text_style::set`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L200)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto set(emphasis em, bool enable = true) noexcept -> text_style&;
```

## Description

Enables all bits in `em` when `enable` is true, or clears them otherwise. Other bits are preserved. Returns `*this`.
