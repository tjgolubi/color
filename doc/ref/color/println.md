# [`tjg::color::println`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color.hpp)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<typename... T>
void println(FILE* f, text_style style, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(text_style style, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(std::ostream& os, text_style style, std::format_string<T...> fmt, T&&... args);
```

## Description

Writes the formatted message and a newline using `style`, then restores the
enclosing style.

### File output: `FILE* f`

Writes the formatted result to the supplied C file stream `f`.

### Standard output: no destination argument

Writes the formatted result to `stdout`.

### Stream output: `std::ostream& os`

Writes the formatted result to the supplied narrow C++ output stream `os`.

## Parameters

| Parameter | Description                                            |
| ---       | ---                                                    |
| `f`       | Destination C file stream.                             |
| `os`      | Destination narrow C++ output stream.                  |
| `style`   | Style applied to the formatted message and newline.   |
| `fmt`     | Compile-time-checked format string.                    |
| `args`    | Arguments used to replace fields in the format string. |

## See also

For runtime formatting, see [`vprint_unicode`](vprint_unicode.md) and [`vprint_nonunicode`](vprint_nonunicode.md). See the [styled output guide](../../print.md) for stream examples.

[`std::println`](https://en.cppreference.com/w/cpp/io/println.html).
