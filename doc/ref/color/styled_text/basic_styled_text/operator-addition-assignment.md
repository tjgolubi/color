# `tjg::color::basic_styled_text::operator+=`

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto operator+=(basic_styled_text rhs) -> basic_styled_text&;
```

## Description

Appends `rhs`, preserving the styles of the original pieces, and returns `*this`. Empty styled text acts as an identity. See also [`operator+`](operator-addition.md).
