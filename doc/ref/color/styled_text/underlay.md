# `tjg::color::underlay`

Header: [`<tjg/color/styled_text.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
auto underlay(text_style style, T&& text)
  -> basic_styled_text</* character type of T */>;
```

Supplies defaults for the outermost group of the returned text. Existing specified colors take precedence, and emphasis bits are combined by OR. Child styles are preserved.

See the [text input rules](basic_styled_text/index.md#text-inputs) and the [style overload](../text_style/underlay.md).

See also [`basic_styled_text::underlay`](basic_styled_text/underlay.md).
