# `tjg::color::strip_ansi`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
auto strip_ansi(basic_styled_text<Char> input) -> basic_styled_text<Char>;
```

## Description

Removes well-formed ANSI escape sequences from the text, while preserving styles and grouping. Sequences may span pieces. An lvalue is copied into the parameter, and an rvalue can be moved. See also the [plain string overloads](../../util/strip_ansi.md).
