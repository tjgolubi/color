# [`tjg::color::wrap_sgr`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/sgr_support.hpp#L347)

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
auto wrap_sgr(const text_style& style, std::basic_string_view<Char> sv)
  -> std::basic_string<Char>;
auto wrap_sgr(const text_style& style, std::string_view sv) -> std::string;
```

## Description

Returns the opening [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) for `style`, the literal text `sv`, and a terminal reset. Empty text produces an empty string. An empty relative style returns a copy of the input text. Embedded nulls, braces, and escape sequences are copied without interpretation.

For wide text, supply a `std::wstring_view` or specify `wrap_sgr<wchar_t>` explicitly.

### Character-type template: `std::basic_string_view<Char>`

Returns `std::basic_string<Char>`. For wide text, supply `std::wstring_view` or specify `wrap_sgr<wchar_t>` explicitly.

### Narrow convenience overload: `std::string_view`

Returns `std::string` and accepts inputs implicitly convertible to `std::string_view`.

## Parameters

| Parameter | Description                                    |
| ---       | ---                                            |
| `style`   | Style applied to the literal text.             |
| `sv`      | Borrowed text copied into the returned string. |

## Return value

A string with the input character type and requested style wrapping.
