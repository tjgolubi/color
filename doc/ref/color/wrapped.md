# [`tjg::color::wrapped`](https://github.com/tjgolubi/color/blob/fc368946e2c4bb836d487952935070698cfbf8d5/include/tjg/color/bits/styled_text-format.hpp#L300)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
// Returns an object of unspecified type.
auto wrapped(styled_text text) noexcept;
auto wrapped(wstyled_text text) noexcept;
```

## Description

Formats or inserts `text` as styled lines using [`word_wrap()`](styled_text/word_wrap.md).
Newlines separate the lines, with no trailing newline. Empty or whitespace-only
input produces no output.
Printing with {color} or inserting into a stream applies
[terminal detection](print.md#terminal-detection).

In a format string of the matching character type, the field width sets the
wrap width in display columns and defaults to 80. Precision sets the hanging
indent and defaults
to zero. Both can be dynamic. The first line uses the full width, and each
subsequent nonblank line starts with that many ordinary spaces, including
after an explicit newline. With a positive indent, blank lines remain empty.

An explicit alignment applies fill and padding to each line's text field.
For example, `{:^40.2}` centers the first line across 40 columns and centers
continuation lines in the 38 columns after their two leading spaces.
`{:>40.2}` keeps the right edge at column 40. Width below four, indent that
leaves fewer than four columns, and debug presentation are format errors.

In a `std::ostream` or `std::wostream`, a positive pending width supplies the
wrap width and is reset to zero. A positive width below 4 throws
`std::format_error`. Without a
positive width, wrapping uses 80 columns. An explicit stream alignment applies
the stream fill to each wrapped line. Stream precision is ignored.

## Return value

An object that stores the text and applies wrapping on formatting or insertion.

## Example

```cpp
using namespace tjg::color;
auto notes = styled_text{"Build completed with warnings."};
tjg::color::println(stdout, "{:{}}", wrapped(notes), 18);
tjg::color::println(stdout, "{:18.2}", wrapped(notes));
std::cout << std::setw(18) << wrapped(notes) << '\n';
```
