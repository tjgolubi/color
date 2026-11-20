# `tjg::color::vprint_nonunicode`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
void vprint_nonunicode(FILE* f, text_style ts, std::string_view fmt,
                         std::format_args args);
void vprint_nonunicode(text_style ts, std::string_view fmt,
                         std::format_args args);
void vprint_nonunicode(std::ostream& os, text_style ts, std::string_view fmt,
                         std::format_args args);
```

Writes styled output using the standard non-Unicode printing path. `fmt` and `args` are runtime formatting inputs. The destination defaults to `stdout`; explicit overloads take a `FILE*` or `std::ostream&`. These overloads append no newline. See [`print`](print.md) for compile-time format checking.
