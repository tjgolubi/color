# [`tjg::color::overlay`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L202)

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto overlay(text_style overrides, T&& text)
  -> basic_styled_text</* character type of T */>;
```

## Description

Applies specified colors and emphasis throughout the returned text. An absolute group and everything inside it are skipped.

See the [text input rules](basic_styled_text/index.md#text-inputs) and the [style overload](../text_style/overlay.md).

## See also

[`basic_styled_text::overlay`](basic_styled_text/overlay.md).
