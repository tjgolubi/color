# [`tjg::color::text_style::strike`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L237)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto strike(bool enable = true) noexcept -> text_style&;
```

## Description

Enables strike-through when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_strike`](is_strike.md) to query the attribute or the [free function](../strike.md) to obtain a new style.
