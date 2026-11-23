# [`tjg::color::print`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color.hpp)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<typename... T>
void print(FILE* f, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void print(FILE* f, const text_style& style, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void print(std::format_string<T...> fmt, T&&... args);
template<typename... T>
void print(const text_style& style, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void print(std::ostream& os, std::format_string<T...> fmt, T&&... args);
template<typename... T>
void print(std::ostream& os, const text_style& style, std::format_string<T...> fmt, T&&... args);
```

## Description

Formats arguments and writes to the supplied `FILE*` or narrow
`std::ostream`. With no destination, writes to `stdout`. The format string
supplies any desired trailing newline. On a terminal, the overloads with
`style` apply it to the message and restore the enclosing style afterward.
The overloads without `style` still honor styles on individual arguments.

### File output: `FILE* f`

Writes the formatted result to the supplied C file stream `f`.

### Standard output: no destination argument

Writes the formatted result to `stdout`.

### Stream output: `std::ostream& os`

Writes the formatted result to the supplied narrow C++ output stream `os`.
Use a qualified call such as `clr::print(os, fmt, args...)` with
`namespace clr = tjg::color;` to avoid ambiguity with `std::print`.

### Terminal detection

Printing and styled stream insertion emit SGR when the destination is
detected as a terminal. The `FILE*` overloads check the supplied stream's file
descriptor. The standard narrow and wide output streams check their associated
C streams. `cout` and `wcout` check `stdout`, and `cerr`, `clog`, `wcerr`,
and `wclog` check `stderr`. That mapping assumes the usual stream buffers
and still checks the same C streams after a call to replace `rdbuf()`.
Other C++ streams, including string streams, receive plain text.

This policy applies to SGR generated while rendering styles. Escape sequences
already present in a string are written as supplied. On native Windows, the
CRT check can also classify other character devices as terminals.

## Parameters

| Parameter | Description                                            |
| ---       | ---                                                    |
| `f`       | Destination C file stream.                             |
| `os`      | Destination narrow C++ output stream.                  |
| `style`   | Style applied to the formatted result.                 |
| `fmt`     | Compile-time-checked format string.                    |
| `args`    | Arguments used to replace fields in the format string. |

## See also

For runtime formatting, see [`vprint_unicode`](vprint_unicode.md) and [`vprint_nonunicode`](vprint_nonunicode.md). See the [styled output guide](../../print.md) for stream examples.

[`std::print`](https://en.cppreference.com/w/cpp/io/print.html).
