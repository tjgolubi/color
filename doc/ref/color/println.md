# `tjg::color::println`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<typename... T>
void println(FILE* f, text_style ts, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(text_style ts, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(std::ostream& os, text_style ts, std::format_string<T...> fmt, T&&... args);
```

Formats arguments with `ts` and writes to the supplied `FILE*` or narrow `std::ostream`. With no destination, writes to `stdout`. Appends a newline after the formatted message and any trailing reset. Styling is applied to the message and restored to defaults after styled output.

For runtime formatting, see [`vprint_unicode`](vprint_unicode.md) and [`vprint_nonunicode`](vprint_nonunicode.md). See the [styled output guide](../../print.md) for stream examples.
