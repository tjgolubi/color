# `tjg::color::vprint_unicode`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
void vprint_unicode(FILE* f, text_style ts, std::string_view fmt,
                         std::format_args args);
void vprint_unicode(text_style ts, std::string_view fmt,
                         std::format_args args);
void vprint_unicode(std::ostream& os, text_style ts, std::string_view fmt,
                         std::format_args args);
```

Writes styled output using the standard Unicode printing path. `fmt` and `args` are runtime formatting inputs. The destination defaults to `stdout`; explicit overloads take a `FILE*` or `std::ostream&`. These overloads append no newline. See [`print`](print.md) for compile-time format checking.
