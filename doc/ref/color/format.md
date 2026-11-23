# [`tjg::color::format`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/text_style-format.hpp#L407)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<typename... T>
auto format(const text_style& style, std::format_string<T...> fmt, T&&... args)
  -> std::string;
template<typename... T>
auto format(const text_style& style, std::wformat_string<T...> pattern, T&&... args)
  -> std::wstring;
```

## Description

Formats arguments using the standard format string syntax. Returns a string with the [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) needed to apply `style` and restore the terminal defaults. A relative empty style contributes no outer styling. Styled arguments can apply and restore their own styles.

`fmt` is checked at compile time. For a runtime format string, see [`vformat`](vformat.md). For an output iterator, see [`format_to`](format_to.md).

### Narrow formatting: `std::format_string<T...>`

Accepts a narrow compile-time-checked format string and returns `std::string`.

### Wide formatting: `std::wformat_string<T...>`

Accepts a wide compile-time-checked format string and returns `std::wstring`.

## Parameters

| Parameter        | Description                                            |
| ---              | ---                                                    |
| `style`          | Style applied to the formatted result.                 |
| `fmt`, `pattern` | Compile-time-checked format string.                    |
| `args`           | Arguments used to replace fields in the format string. |

## Return value

`std::string` for the narrow overload, or `std::wstring` for the wide overload.

## Example

```cpp
using namespace tjg::color;
using enum term_color;
auto status = format(fg(green), "{} checks passed", 4);
```

## See also

[`std::format`](https://en.cppreference.com/w/cpp/utility/format/format.html).
