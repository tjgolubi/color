# `tjg::color::basic_styled_text::plain_text`

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto plain_text() const -> string_type;
```

Returns an independent string containing the text in order. Embedded nulls and escape sequences already present in the text are copied verbatim. The operation can allocate.
