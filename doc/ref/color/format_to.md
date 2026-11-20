# [`tjg::color::format_to`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/text_style-format.hpp#L426)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<std::output_iterator<const char&> OutputIt, typename... T>
auto format_to(OutputIt out, text_style style, std::format_string<T...> fmt,
               T&&... args) -> OutputIt;
template<std::output_iterator<const wchar_t&> OutputIt, typename... T>
auto format_to(OutputIt out, text_style style, std::wformat_string<T...> fmt,
               T&&... args) -> OutputIt;
```

## Description

Writes the result of styled [`format`](format.md) through `out` and returns the advanced iterator. The format string is checked at compile time. See [`vformat_to`](vformat_to.md) for runtime format strings.

### Narrow output: `OutputIt` for `char`

Writes a narrow formatted result through the output iterator.

### Wide output: `OutputIt` for `wchar_t`

Writes a wide formatted result through the output iterator.

## Parameters

| Parameter | Description                                            |
| ---       | ---                                                    |
| `out`     | Output iterator receiving the formatted characters.    |
| `style`   | Style applied to the formatted result.                 |
| `fmt`     | Compile-time-checked format string.                    |
| `args`    | Arguments used to replace fields in the format string. |

## Return value

The output iterator advanced past the written result.

## See also

[`std::format_to`](https://en.cppreference.com/w/cpp/utility/format/format_to.html).
