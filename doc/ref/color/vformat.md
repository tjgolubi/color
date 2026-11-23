# [`tjg::color::vformat`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/text_style-format.hpp#L376)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
auto vformat(const text_style& style, std::string_view fmt, std::format_args args)
  -> std::string;
auto vformat(const text_style& style, std::wstring_view fmt, std::wformat_args args)
  -> std::wstring;
```

## Description

Formats a runtime format string and returns a narrow or wide string with the styling applied, as for [`format`](format.md). Use `std::make_format_args` or `std::make_wformat_args` with arguments that remain alive during formatting. Invalid format specifications can throw `std::format_error`.

### Narrow formatting: `std::string_view`

Uses `std::format_args` and returns `std::string`.

### Wide formatting: `std::wstring_view`

Uses `std::wformat_args` and returns `std::wstring`.

## Parameters

| Parameter | Description                                                              |
| ---       | ---                                                                      |
| `style`   | Style applied to the formatted result.                                   |
| `fmt`     | Runtime format string.                                                   |
| `args`    | Argument store; its referenced values must remain alive during the call. |

## Return value

`std::string` for the narrow overload, or `std::wstring` for the wide overload.

## See also

[`std::vformat`](https://en.cppreference.com/w/cpp/utility/format/vformat.html).
