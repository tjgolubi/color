# [`tjg::color::vformat_to`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/text_style-format.hpp#L212)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<std::output_iterator<const char&> OutputIt>
auto vformat_to(OutputIt out, text_style style,
                std::string_view fmt, std::format_args args) -> OutputIt;
template<std::output_iterator<const char&> OutputIt>
auto vformat_to(OutputIt out, const std::locale& loc, text_style style,
                std::string_view fmt, std::format_args args) -> OutputIt;
template<std::output_iterator<const wchar_t&> OutputIt>
auto vformat_to(OutputIt out, text_style style,
                std::wstring_view fmt, std::wformat_args args) -> OutputIt;
template<std::output_iterator<const wchar_t&> OutputIt>
auto vformat_to(OutputIt out, const std::locale& loc, text_style style,
                std::wstring_view fmt, std::wformat_args args) -> OutputIt;
```

## Description

Writes a styled, runtime-formatted result to `out` and returns the advanced iterator. Supply `loc` to control locale-specific formatting. The argument store and its referenced values must remain alive throughout the call. See [`vformat`](vformat.md) and [`format_to`](format_to.md).

### Narrow output: `std::string_view` and `std::format_args`

Writes narrow characters to `out`. The overload taking `const std::locale& loc` uses that locale for locale-specific formatting; the other uses the default formatting locale.

### Wide output: `std::wstring_view` and `std::wformat_args`

Writes wide characters to `out`. The overload taking `const std::locale& loc` uses that locale for locale-specific formatting; the other uses the default formatting locale.

## Parameters

| Parameter | Description                                                              |
| ---       | ---                                                                      |
| `out`     | Output iterator receiving the formatted characters.                      |
| `style`   | Style applied to the formatted result.                                   |
| `fmt`     | Runtime format string.                                                   |
| `args`    | Argument store; its referenced values must remain alive during the call. |
| `loc`     | Locale used by the overload with an explicit locale.                     |

## Return value

The output iterator advanced past the written result.

## See also

[`std::vformat_to`](https://en.cppreference.com/w/cpp/utility/format/vformat_to.html).
