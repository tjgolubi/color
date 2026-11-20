# `tjg::color::bold`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto bold(bool enable = true) noexcept -> text_style;
constexpr auto bold(text_style style, bool enable = true) noexcept
  -> text_style;
```

By default enables increased intensity. The first overload starts with an empty [`text_style`](text_style.md), and the second starts with a copy of `style`. Pass `false` to clear the bit in the result. See the [styled-text overload](../styled_text/bold.md).
