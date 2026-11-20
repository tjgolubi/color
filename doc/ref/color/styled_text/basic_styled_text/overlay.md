# `tjg::color::basic_styled_text::overlay`

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto overlay(text_style overrides) noexcept -> basic_styled_text&;
```

Applies specified colors and combines emphasis throughout the styled text in place. An absolute group and its contents are skipped. Returns `*this`. See also the [free function](../overlay.md).
