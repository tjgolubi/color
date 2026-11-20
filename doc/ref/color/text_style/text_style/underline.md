# [`tjg::color::text_style::underline`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L221)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto underline(bool enable = true) noexcept -> text_style&;
```

## Description

Enables underlining when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_underline`](is_underline.md) to query the attribute or the [free function](../underline.md) to obtain a new style.
