# `tjg::color::text_style::blink`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto blink(bool enable = true) noexcept -> text_style&;
```

Enables blinking when `enable` is true, or clears the attribute otherwise. Returns `*this`. See [`is_blink`](is_blink.md) to query the attribute or the [free function](../blink.md) to obtain a new style.
