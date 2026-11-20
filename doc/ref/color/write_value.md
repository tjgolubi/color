# `tjg::color::write_value`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<std::output_iterator<char> Out>
constexpr auto write_value(Out out, no_color_t value) -> Out;
template<std::output_iterator<char> Out>
constexpr auto write_value(Out out, const rgb& value) -> Out;
template<std::output_iterator<char> Out>
constexpr auto write_value(Out out, term_color value) -> Out;
template<std::output_iterator<char> Out>
constexpr auto write_value(Out out, const cube& value) -> Out;
template<std::output_iterator<char> Out>
constexpr auto write_value(Out out, const gray& value) -> Out;
template<std::output_iterator<char> Out>
constexpr auto write_value(Out out, const color_t& value) -> Out;
template<std::output_iterator<char> Out>
auto write_value(Out out, emphasis value) -> Out;
```

Writes the readable representation to `out` and returns the advanced iterator. Examples include `no_color`, `#ff0080`, `bright_red`, `gray12`, `cube503`, and `{bold underline}`. A variant uses its active alternative. The result contains no SGR.
