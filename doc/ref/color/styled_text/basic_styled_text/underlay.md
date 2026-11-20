# `tjg::color::basic_styled_text::underlay`

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto underlay(text_style style) noexcept -> basic_styled_text&;
```

Applies the supplied style as defaults for the outermost group in place. Specified outermost colors remain, emphasis and the absolute flag are combined by OR, and child styles are preserved. Returns `*this`. See also the [free function](../underlay.md).
