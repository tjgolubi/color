# `tjg::color::overlay`

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto overlay(text_style overrides, T&& text)
  -> basic_styled_text</* character type of T */>;
```

Applies specified colors and emphasis throughout the returned text. An absolute group and everything inside it are skipped.

See the [text input rules](basic_styled_text.md#text-inputs) and the [style overload](../text_style/overlay.md).
