# `tjg::color::underline`

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto underline(T&& text) -> basic_styled_text</* character type of T */>;
```

## Description

Returns [styled text](basic_styled_text/index.md) with underlining enabled on the outermost group, preserving its other style and the styles of its children. See the [text input rules](basic_styled_text/index.md#text-inputs) and the [style overloads](../text_style/underline.md).
