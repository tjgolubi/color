# [`std::formatter::parse` for {color}](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color.hpp)

Type: [`std::formatter` specializations](index.md).

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto parse(std::basic_format_parse_context<Char>& ctx)
  -> decltype(ctx.begin());
```

## Description

Parses the format specification and returns the iterator marking where parsing
stopped. The color, emphasis, style, and styled-text formatters accept
string-style fill, alignment, width, precision, and the optional `s` or `?`
presentation. For styled text, the `?` presentation rejects width and precision,
including dynamic values. The wrapper returned by [`styled`](../styled.md) uses
the underlying value's formatter and its accepted format specifiers.
