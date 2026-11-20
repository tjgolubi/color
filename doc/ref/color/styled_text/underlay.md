# [`tjg::color::underlay`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L217)

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto underlay(text_style style, T&& text)
  -> basic_styled_text</* character type of T */>;
```

## Description

Supplies defaults for the outermost group of the returned text. Existing specified colors take precedence, and emphasis attributes are combined. Child styles are preserved.

See the [text input rules](basic_styled_text/index.md#text-inputs) and the [style overload](../text_style/underlay.md).

## See also

[`basic_styled_text::underlay`](basic_styled_text/underlay.md).
