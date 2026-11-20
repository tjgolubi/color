# `tjg::color::term_color`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
enum class term_color : std::int8_t {
  black, red, green, yellow, blue, magenta, cyan, white,
  gray, bright_red, bright_green, bright_yellow,
  bright_blue, bright_magenta, bright_cyan, bright_white
};
```

## Description

Selects one of the terminal’s 16 named palette entries. The actual colors follow the terminal theme.

| Entries                       | Palette slots | Foreground [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) | Background SGR |
| ---                           | ---           | ---                                                                                                  | ---            |
| `black` through `white`       | 0–7           | 30–37                                                                                                | 40–47          |
| `gray` through `bright_white` | 8–15          | 90–97                                                                                                | 100–107        |

Conversion to [`rgb`](rgb/index.md) uses the fixed Xterm-default palette. The corresponding constants are [`rgb::term_black` through `rgb::term_bright_white`](rgb/rgb-constants.md#terminal-colors). Use the named enumerators when selecting a color. See also [`name_of`](name_of.md).

See [Xterm-default palette behavior](xterm-palette.md).
