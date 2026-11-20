# `tjg::color::strike`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto strike(bool enable = true) noexcept -> text_style;
constexpr auto strike(text_style style, bool enable = true) noexcept
  -> text_style;
```

By default enables strike-through. The first overload starts with an empty [`text_style`](text_style/index.md), and the second starts with a copy of `style`. Pass `false` to clear the bit in the result. See the [styled-text overload](../styled_text/strike.md).

See also [`text_style::strike`](text_style/strike.md).
