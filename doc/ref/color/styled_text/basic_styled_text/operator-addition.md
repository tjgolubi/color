# [`operator+` for `tjg::color::basic_styled_text`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L167)

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto operator+(basic_styled_text lhs, basic_styled_text rhs)
  -> basic_styled_text;
```

## Description

Returns the concatenated value, preserving the styles of both operands. An empty operand acts as an identity. See also [`operator+=`](operator-addition-assignment.md).
