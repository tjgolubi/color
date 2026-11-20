# `tjg::color::print`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<typename... T>
void print(FILE* f, text_style ts, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void print(text_style ts, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void print(std::ostream& os, text_style ts, std::format_string<T...> fmt, T&&... args);
```

Formats arguments with `ts` and writes to the supplied `FILE*` or narrow `std::ostream`. With no destination, writes to `stdout`. The format string supplies any desired trailing newline. Styling is applied to the message and restored to defaults after styled output.

For runtime formatting, see [`vprint_unicode`](vprint_unicode.md) and [`vprint_nonunicode`](vprint_nonunicode.md). See the [styled output guide](../../print.md) for stream examples.
