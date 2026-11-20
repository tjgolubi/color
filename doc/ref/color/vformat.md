# `tjg::color::vformat`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
auto vformat(text_style ts, std::string_view fmt, std::format_args args)
  -> std::string;
auto vformat(text_style ts, std::wstring_view fmt, std::wformat_args args)
  -> std::wstring;
```

Formats a runtime format string and returns a narrow or wide string with the styling applied, as for [`format`](format.md). Use `std::make_format_args` or `std::make_wformat_args` with arguments that remain alive during formatting. Invalid format specifications can throw `std::format_error`.
