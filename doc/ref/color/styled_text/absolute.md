# [`tjg::color::absolute`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L231)

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto absolute(T&& text) -> basic_styled_text</* character type of T */>;
```

## Description

Returns styled text with an absolute outermost style, preserving the other components and child styles. See the [text input rules](basic_styled_text/index.md#text-inputs) and the [style overload](../text_style/absolute.md).
