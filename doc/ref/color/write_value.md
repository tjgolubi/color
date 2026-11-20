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

## Description

Writes the readable representation to `out` and returns the advanced iterator. Examples include `no_color`, `#ff0080`, `bright_red`, `gray12`, `cube503`, and `{bold underline}`. A variant uses its active alternative. The result contains no [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters).

### Unspecified color: `no_color_t`

Writes `no_color`.

### RGB value: `const rgb&`

Writes a hexadecimal RGB value, for example `#ff0080`.

### Terminal color: `term_color`

Writes its named palette entry, for example `bright_red`.

### Cube color: `const cube&`

Writes `cube` followed by the three channel indices, for example `cube503`.

### Gray color: `const gray&`

Writes `gray` followed by its zero-based index, for example `gray12`.

### Color variant: `const color_t&`

Writes the representation of the active alternative.

### Emphasis: `emphasis`

Writes the enabled attribute names in braces, for example `{bold underline}`.

## Return value

The output iterator advanced past the readable representation.
