# [`tjg::color::println`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color.hpp)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<typename... T>
void println(FILE* f, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(FILE* f, const text_style& style, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(const text_style& style, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(std::ostream& os, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void println(std::ostream& os, const text_style& style, std::format_string<T...> fmt, T&&... args);
void println(FILE* f = stdout);
```

## Description

Writes the formatted message and a newline. On a terminal, the overloads with
`style` apply it through the newline and then restore the enclosing style.
The formatting overloads without `style` still honor styles on individual
arguments.
See [Terminal detection](print.md#terminal-detection) for the shared policy.

### File output: `FILE* f`

Writes the formatted result to the supplied C file stream `f`.

### Standard output: no destination argument

Writes the formatted result to `stdout`.

### Stream output: `std::ostream& os`

Writes the formatted result to the supplied narrow C++ output stream `os`.
Use a qualified call such as `clr::println(os, fmt, args...)` with
`namespace clr = tjg::color;` to avoid ambiguity with `std::println`.

### Newline only

`println(f)` writes a single newline to `f`. `println()` writes it to
`stdout`.

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
