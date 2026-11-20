# `tjg::color::text_style::faint`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto faint(bool enable = true) noexcept -> text_style&;
```

Enables decreased intensity when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_faint`](is_faint.md) to query the attribute or the [free function](../faint.md) to obtain a new style.
