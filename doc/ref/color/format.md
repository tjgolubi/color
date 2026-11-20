# `tjg::color::format`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<typename... T>
auto format(text_style ts, std::format_string<T...> fmt, T&&... args)
  -> std::string;
template<typename... T>
auto format(text_style ts, std::wformat_string<T...> pattern, T&&... args)
  -> std::wstring;
```

Formats arguments using the standard format string syntax. Returns a string with the SGR needed to apply `ts` and restore the terminal defaults. A relative empty style contributes no outer styling. Styled arguments can apply and restore their own styles.

`fmt` is checked at compile time. For a runtime format string, see [`vformat`](vformat.md). For an output iterator, see [`format_to`](format_to.md).

```cpp
using namespace tjg::color;
using enum term_color;
auto status = format(fg(green), "{} checks passed", 4);
```
