# `tjg::color::wrapped`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
// Returns an object of unspecified type.
auto wrapped(styled_text text) noexcept;
```

## Description

Formats or inserts `text` as styled lines using [`word_wrap()`](styled_text/word_wrap.md).
Newlines separate the lines, with no trailing newline. Empty or whitespace-only
input produces no output.

In a narrow format string, the field width sets the wrap width in display
columns. The default is 80. Dynamic width is supported. An explicit alignment
applies fill and padding to each wrapped line. A width below 4, precision, or
debug presentation produces a format error.

In a `std::ostream`, a positive pending width supplies the wrap width and is
reset to zero. A positive width below 4 throws `std::format_error`. Without a
positive width, wrapping uses 80 columns. An explicit stream alignment applies
the stream fill to each wrapped line. Stream precision is ignored.

## Return value

An object that stores the text and applies wrapping on formatting or insertion.

## Example

```cpp
using namespace tjg::color;
auto notes = styled_text{"Build completed with warnings."};
std::println("{:{}}", wrapped(notes), 18);
std::cout << std::setw(18) << wrapped(notes) << '\n';
```
