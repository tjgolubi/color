# [`tjg::color::text_style::faint`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L213)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto faint(bool enable = true) noexcept -> text_style&;
```

## Description

Enables decreased intensity when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_faint`](is_faint.md) to query the attribute or the [free function](../faint.md) to obtain a new style.
