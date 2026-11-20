# `tjg::color::basic_sgr_buffer`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
using basic_sgr_buffer = basic_inline_buffer<Char, sgr_max_length>;
```

## Description

A [fixed-capacity buffer](../../util/basic_inline_buffer/index.md) sized for one style’s [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) sequence. See also the narrow alias [`sgr_buffer`](sgr_buffer.md).

## Template parameters

| Parameter | Description                                                            |
| ---       | ---                                                                    |
| `Char`    | Stored character type satisfying [`CharType`](../../util/CharType.md). |
