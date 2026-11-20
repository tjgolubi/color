# `tjg::color::sgr_max_length`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto sgr_max_length = std::size_t{60};
```

## Description

The upper bound on [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) output length for one style, including a leading reset when needed.
