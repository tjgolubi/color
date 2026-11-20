# [`tjg::color::no_color`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L42)

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
inline constexpr no_color_t no_color{};
```

## Description

An unspecified channel value of type [`no_color_t`](no_color_t/index.md). Passing it to [`fg`](../text_style/fg.md) or [`bg`](../text_style/bg.md) produces an empty style. RGB and terminal black are specified colors.

## See also

[`blend`](blend.md) ignores unspecified inputs when averaging colors.
