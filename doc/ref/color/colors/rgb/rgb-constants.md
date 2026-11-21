# [Named `tjg::color::rgb` constants](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp)

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Representative constexpr static members of rgb.
static const rgb xterm_black;
static const rgb alice_blue;
// See the complete constant table below.
```

## Description

Each name denotes a static [`rgb`](index.md) member usable in constant expressions. The `xterm_*` entries use
fixed Xterm-default colors. See the [swatches](../../../../named-colors.md).

Most named colors follow the [W3C CSS named colors table](https://www.w3.org/TR/css-color-4/#named-colors).
C++ names use underscores between words, for example `alice_blue` for CSS
`aliceblue` and `rebecca_purple` for `rebeccapurple`.
The custom neutral shades `dark_gray` and `light_gray`, and the `xterm_*`
constants, are separate from the CSS-derived names. `gray` is `#808080`,
which also matches CSS gray. The CSS names `darkgray` and `lightgray` retain
their CSS values, distinct from the underscore names.
See [Xterm-default palette behavior](../xterm-palette.md) for the `xterm_*` colors.

### Terminal colors

| Constant                    | RGB       |
| --------------------------- | --------- |
| `rgb::xterm_black`          | `#000000` |
| `rgb::xterm_red`            | `#CD0000` |
| `rgb::xterm_green`          | `#00CD00` |
| `rgb::xterm_yellow`         | `#CDCD00` |
| `rgb::xterm_blue`           | `#0000EE` |
| `rgb::xterm_magenta`        | `#CD00CD` |
| `rgb::xterm_cyan`           | `#00CDCD` |
| `rgb::xterm_white`          | `#E5E5E5` |
| `rgb::xterm_gray`           | `#7F7F7F` |
| `rgb::xterm_bright_red`     | `#FF0000` |
| `rgb::xterm_bright_green`   | `#00FF00` |
| `rgb::xterm_bright_yellow`  | `#FFFF00` |
| `rgb::xterm_bright_blue`    | `#5C5CFF` |
| `rgb::xterm_bright_magenta` | `#FF00FF` |
| `rgb::xterm_bright_cyan`    | `#00FFFF` |
| `rgb::xterm_bright_white`   | `#FFFFFF` |

### CSS-derived and custom colors

| Constant                       | RGB       |
| ---                            | ---       |
| `rgb::alice_blue`              | `#F0F8FF` |
| `rgb::antique_white`           | `#FAEBD7` |
| `rgb::aqua`                    | `#00FFFF` |
| `rgb::aquamarine`              | `#7FFFD4` |
| `rgb::azure`                   | `#F0FFFF` |
| `rgb::beige`                   | `#F5F5DC` |
| `rgb::bisque`                  | `#FFE4C4` |
| `rgb::black`                   | `#000000` |
| `rgb::blanched_almond`         | `#FFEBCD` |
| `rgb::blue`                    | `#0000FF` |
| `rgb::blue_violet`             | `#8A2BE2` |
| `rgb::brown`                   | `#A52A2A` |
| `rgb::burly_wood`              | `#DEB887` |
| `rgb::cadet_blue`              | `#5F9EA0` |
| `rgb::chartreuse`              | `#7FFF00` |
| `rgb::chocolate`               | `#D2691E` |
| `rgb::coral`                   | `#FF7F50` |
| `rgb::cornflower_blue`         | `#6495ED` |
| `rgb::cornsilk`                | `#FFF8DC` |
| `rgb::crimson`                 | `#DC143C` |
| `rgb::cyan`                    | `#00FFFF` |
| `rgb::dark_blue`               | `#00008B` |
| `rgb::dark_cyan`               | `#008B8B` |
| `rgb::dark_golden_rod`         | `#B8860B` |
| `rgb::darkgray`                | `#A9A9A9` |
| `rgb::dark_gray`               | `#404040` |
| `rgb::dark_green`              | `#006400` |
| `rgb::dark_khaki`              | `#BDB76B` |
| `rgb::dark_magenta`            | `#8B008B` |
| `rgb::dark_olive_green`        | `#556B2F` |
| `rgb::dark_orange`             | `#FF8C00` |
| `rgb::dark_orchid`             | `#9932CC` |
| `rgb::dark_red`                | `#8B0000` |
| `rgb::dark_salmon`             | `#E9967A` |
| `rgb::dark_sea_green`          | `#8FBC8F` |
| `rgb::dark_slate_blue`         | `#483D8B` |
| `rgb::dark_slate_gray`         | `#2F4F4F` |
| `rgb::dark_turquoise`          | `#00CED1` |
| `rgb::dark_violet`             | `#9400D3` |
| `rgb::deep_pink`               | `#FF1493` |
| `rgb::deep_sky_blue`           | `#00BFFF` |
| `rgb::dim_gray`                | `#696969` |
| `rgb::dodger_blue`             | `#1E90FF` |
| `rgb::fire_brick`              | `#B22222` |
| `rgb::floral_white`            | `#FFFAF0` |
| `rgb::forest_green`            | `#228B22` |
| `rgb::fuchsia`                 | `#FF00FF` |
| `rgb::gainsboro`               | `#DCDCDC` |
| `rgb::ghost_white`             | `#F8F8FF` |
| `rgb::gold`                    | `#FFD700` |
| `rgb::golden_rod`              | `#DAA520` |
| `rgb::gray`                    | `#808080` |
| `rgb::green`                   | `#008000` |
| `rgb::green_yellow`            | `#ADFF2F` |
| `rgb::honey_dew`               | `#F0FFF0` |
| `rgb::hot_pink`                | `#FF69B4` |
| `rgb::indian_red`              | `#CD5C5C` |
| `rgb::indigo`                  | `#4B0082` |
| `rgb::ivory`                   | `#FFFFF0` |
| `rgb::khaki`                   | `#F0E68C` |
| `rgb::lavender`                | `#E6E6FA` |
| `rgb::lavender_blush`          | `#FFF0F5` |
| `rgb::lawn_green`              | `#7CFC00` |
| `rgb::lemon_chiffon`           | `#FFFACD` |
| `rgb::light_blue`              | `#ADD8E6` |
| `rgb::light_coral`             | `#F08080` |
| `rgb::light_cyan`              | `#E0FFFF` |
| `rgb::light_golden_rod_yellow` | `#FAFAD2` |
| `rgb::lightgray`               | `#D3D3D3` |
| `rgb::light_gray`              | `#C0C0C0` |
| `rgb::light_green`             | `#90EE90` |
| `rgb::light_pink`              | `#FFB6C1` |
| `rgb::light_salmon`            | `#FFA07A` |
| `rgb::light_sea_green`         | `#20B2AA` |
| `rgb::light_sky_blue`          | `#87CEFA` |
| `rgb::light_slate_gray`        | `#778899` |
| `rgb::light_steel_blue`        | `#B0C4DE` |
| `rgb::light_yellow`            | `#FFFFE0` |
| `rgb::lime`                    | `#00FF00` |
| `rgb::lime_green`              | `#32CD32` |
| `rgb::linen`                   | `#FAF0E6` |
| `rgb::magenta`                 | `#FF00FF` |
| `rgb::maroon`                  | `#800000` |
| `rgb::medium_aquamarine`       | `#66CDAA` |
| `rgb::medium_blue`             | `#0000CD` |
| `rgb::medium_orchid`           | `#BA55D3` |
| `rgb::medium_purple`           | `#9370DB` |
| `rgb::medium_sea_green`        | `#3CB371` |
| `rgb::medium_slate_blue`       | `#7B68EE` |
| `rgb::medium_spring_green`     | `#00FA9A` |
| `rgb::medium_turquoise`        | `#48D1CC` |
| `rgb::medium_violet_red`       | `#C71585` |
| `rgb::midnight_blue`           | `#191970` |
| `rgb::mint_cream`              | `#F5FFFA` |
| `rgb::misty_rose`              | `#FFE4E1` |
| `rgb::moccasin`                | `#FFE4B5` |
| `rgb::navajo_white`            | `#FFDEAD` |
| `rgb::navy`                    | `#000080` |
| `rgb::old_lace`                | `#FDF5E6` |
| `rgb::olive`                   | `#808000` |
| `rgb::olive_drab`              | `#6B8E23` |
| `rgb::orange`                  | `#FFA500` |
| `rgb::orange_red`              | `#FF4500` |
| `rgb::orchid`                  | `#DA70D6` |
| `rgb::pale_golden_rod`         | `#EEE8AA` |
| `rgb::pale_green`              | `#98FB98` |
| `rgb::pale_turquoise`          | `#AFEEEE` |
| `rgb::pale_violet_red`         | `#DB7093` |
| `rgb::papaya_whip`             | `#FFEFD5` |
| `rgb::peach_puff`              | `#FFDAB9` |
| `rgb::peru`                    | `#CD853F` |
| `rgb::pink`                    | `#FFC0CB` |
| `rgb::plum`                    | `#DDA0DD` |
| `rgb::powder_blue`             | `#B0E0E6` |
| `rgb::purple`                  | `#800080` |
| `rgb::rebecca_purple`          | `#663399` |
| `rgb::red`                     | `#FF0000` |
| `rgb::rosy_brown`              | `#BC8F8F` |
| `rgb::royal_blue`              | `#4169E1` |
| `rgb::saddle_brown`            | `#8B4513` |
| `rgb::salmon`                  | `#FA8072` |
| `rgb::sandy_brown`             | `#F4A460` |
| `rgb::sea_green`               | `#2E8B57` |
| `rgb::sea_shell`               | `#FFF5EE` |
| `rgb::sienna`                  | `#A0522D` |
| `rgb::silver`                  | `#C0C0C0` |
| `rgb::sky_blue`                | `#87CEEB` |
| `rgb::slate_blue`              | `#6A5ACD` |
| `rgb::slate_gray`              | `#708090` |
| `rgb::snow`                    | `#FFFAFA` |
| `rgb::spring_green`            | `#00FF7F` |
| `rgb::steel_blue`              | `#4682B4` |
| `rgb::tan`                     | `#D2B48C` |
| `rgb::teal`                    | `#008080` |
| `rgb::thistle`                 | `#D8BFD8` |
| `rgb::tomato`                  | `#FF6347` |
| `rgb::turquoise`               | `#40E0D0` |
| `rgb::violet`                  | `#EE82EE` |
| `rgb::wheat`                   | `#F5DEB3` |
| `rgb::white`                   | `#FFFFFF` |
| `rgb::white_smoke`             | `#F5F5F5` |
| `rgb::yellow`                  | `#FFFF00` |
| `rgb::yellow_green`            | `#9ACD32` |
