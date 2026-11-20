# [`tjg::color::absolute`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L304)

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto absolute(text_style style) noexcept -> text_style;
```

## Description

Returns a copy of `style` with its absolute flag set. During rendering it starts from terminal defaults. See the [styled-text overload](../styled_text/absolute.md) and [`to_sgr`](../sgr/to_sgr.md).

## See also

[`text_style::absolute`](text_style/absolute.md).
