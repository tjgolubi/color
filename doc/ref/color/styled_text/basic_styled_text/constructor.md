# `tjg::color::basic_styled_text::basic_styled_text`

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
basic_styled_text();

basic_styled_text(string_type text, const text_style& style = {});

basic_styled_text(const Char* text, const text_style& style = {});

basic_styled_text(const basic_styled_text& other);

basic_styled_text(basic_styled_text&& other) noexcept;
```

Default construction produces empty styled text. A string or a non-null pointer to a null-terminated string supplies text, and the optional `style` applies to that text. Supply a string object to preserve embedded nulls. Copy construction preserves text, grouping, and styles. Move construction transfers the value and leaves the source empty.
