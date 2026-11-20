# `tjg::color::absolute`

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto absolute(T&& text) -> basic_styled_text</* character type of T */>;
```

## Description

Returns styled text with an absolute outermost style, preserving the other components and child styles. See the [text input rules](basic_styled_text/index.md#text-inputs) and the [style overload](../text_style/absolute.md).
