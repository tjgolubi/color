# [`tjg::color::basic_styled_text::underlay`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L120)

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto underlay(text_style style) noexcept -> basic_styled_text&;
```

## Description

Applies the supplied style as defaults for the outermost group in place. Specified outermost colors remain, emphasis attributes and the absolute flag are combined, and child styles are preserved. Returns `*this`. See also the [free function](../underlay.md).
