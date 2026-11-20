# [`tjg::color::basic_styled_text::plain_text`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L133)

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto plain_text() const -> string_type;
```

## Description

Returns an independent string containing the text in order. Embedded nulls and escape sequences already present in the text are copied verbatim.
