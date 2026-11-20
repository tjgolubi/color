# `tjg::color::format_to`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<std::output_iterator<const char&> OutputIt, typename... T>
auto format_to(OutputIt out, text_style ts, std::format_string<T...> fmt,
               T&&... args) -> OutputIt;
template<std::output_iterator<const wchar_t&> OutputIt, typename... T>
auto format_to(OutputIt out, text_style ts, std::wformat_string<T...> fmt,
               T&&... args) -> OutputIt;
```

Writes the result of styled [`format`](format.md) through `out` and returns the advanced iterator. The format string is checked at compile time. See [`vformat_to`](vformat_to.md) for runtime format strings.
