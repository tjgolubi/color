# `tjg::color::absolute`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto absolute(text_style style) noexcept -> text_style;
```

Returns a copy of `style` with its absolute flag set. During rendering it starts from terminal defaults. See the [styled-text overload](../styled_text/absolute.md) and [`to_sgr`](../sgr/to_sgr.md).
