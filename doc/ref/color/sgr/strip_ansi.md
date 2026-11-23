# [`tjg::color::strip_ansi`](https://github.com/tjgolubi/color/blob/bf01e2dda7a63533f350ec19807749fca60a40cb/include/tjg/color/bits/strip_ansi-style_text.hpp#L30)

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
auto strip_ansi(basic_styled_text<Char> input) -> basic_styled_text<Char>;
```

## Description

Removes well-formed ANSI escape sequences from the text, while preserving styles and grouping. Sequences may span pieces. See also the [plain string overloads](../../util/strip_ansi.md).
