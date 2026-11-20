# `tjg::color::vformat_to`

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

Writes a styled, runtime-formatted result to `out` and returns the advanced iterator. Supply `loc` to control locale-specific formatting. The argument store and its referenced values must remain alive throughout the call. See [`vformat`](vformat.md) and [`format_to`](format_to.md).
