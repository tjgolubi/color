# [`tjg::color::vprint_unicode`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color.hpp)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
void vprint_unicode(FILE* f, text_style style, std::string_view fmt,
                         std::format_args args);
void vprint_unicode(text_style style, std::string_view fmt,
                         std::format_args args);
void vprint_unicode(std::ostream& os, text_style style, std::string_view fmt,
                         std::format_args args);
```

## Description

Writes styled output using the standard Unicode printing path. `fmt` and `args` are runtime formatting inputs. The destination defaults to `stdout`; explicit overloads take a `FILE*` or `std::ostream&`. These overloads append no newline. See [`print`](print.md) for compile-time format checking.

### File output: `FILE* f`

Writes the formatted result to the supplied C file stream `f`.

### Standard output: no destination argument

Writes the formatted result to `stdout`.

### Stream output: `std::ostream& os`

Writes the formatted result to the supplied narrow C++ output stream `os`.

## Parameters

| Parameter | Description                                                              |
| ---       | ---                                                                      |
| `f`       | Destination C file stream.                                               |
| `os`      | Destination narrow C++ output stream.                                    |
| `style`   | Style applied to the formatted result.                                   |
| `fmt`     | Runtime format string.                                                   |
| `args`    | Argument store; its referenced values must remain alive during the call. |

## See also

[`std::vprint_unicode`](https://en.cppreference.com/w/cpp/io/vprint_unicode.html).
