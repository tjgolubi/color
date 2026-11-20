# [`tjg::color::underlay`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L428)

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto underlay(text_style base, text_style defaults) noexcept
  -> text_style;
```

## Description

Colors from `defaults` fill unspecified channels in `base`. The result combines emphasis attributes and the absolute flag. The input styles are unchanged. See also the [styled-text overload](../styled_text/underlay.md).

## See also

[`text_style::underlay`](text_style/underlay.md).
