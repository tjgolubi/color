# `tjg::color::reverse`

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto reverse(T&& text) -> basic_styled_text</* character type of T */>;
```

Returns [styled text](basic_styled_text.md) with reversed foreground and background enabled on the outermost group, preserving its other style and the styles of its children. See the [text input rules](basic_styled_text.md#text-inputs) and the [style overloads](../text_style/reverse.md).
