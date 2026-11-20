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

## Description

Constructs owned styled text.

### Default construction: `basic_styled_text()`

Produces empty styled text.

### String input: `basic_styled_text(string_type text, const text_style& style)`

Owns the supplied string, preserving embedded nulls. The optional `style` applies to this text.

### Null-terminated input: `basic_styled_text(const Char* text, const text_style& style)`

Copies a non-null pointer to a null-terminated string, excluding the terminator. The optional `style` applies to this text. Use the string overload to preserve embedded nulls.

### Copy construction: `basic_styled_text(const basic_styled_text& other)`

Preserves the source text, grouping, and styles.

### Move construction: `basic_styled_text(basic_styled_text&& other)`

Transfers the value and leaves the source empty.
