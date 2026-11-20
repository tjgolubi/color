# [`tjg::color::strip_ansi`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/strip_ansi_styled_text.hpp#L50)

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
auto strip_ansi(basic_styled_text<Char> input) -> basic_styled_text<Char>;
```

## Description

Removes well-formed ANSI escape sequences from the text, while preserving styles and grouping. Sequences may span pieces. See also the [plain string overloads](../../util/strip_ansi.md).
