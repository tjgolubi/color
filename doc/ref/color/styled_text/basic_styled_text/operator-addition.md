# `operator+` for `tjg::color::basic_styled_text`

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto operator+(basic_styled_text lhs, basic_styled_text rhs)
  -> basic_styled_text;
```

Returns the concatenated value, preserving the styles of both operands. An empty operand acts as an identity. The operation can allocate. See also [`operator+=`](operator-addition-assignment.md).
