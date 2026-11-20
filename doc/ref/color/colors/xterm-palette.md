# Xterm-default palette behavior

The indexed color types [`term_color`](term_color.md), [`cube`](cube/index.md),
and [`gray`](gray/index.md) select entries in a terminal palette. Converting
them to [`rgb`](rgb/index.md) uses fixed values defined by the library. The
conversion does not query the terminal or read its theme.

[Xterm](https://invisible-island.net/xterm/) is a terminal emulator for the X
Window System. Its extended palette has 256 entries. See the official
[Xterm control-sequence reference](https://invisible-island.net/xterm/ctlseqs/ctlseqs.html)
for [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) color selection and palette customization.

## Palette layout

| Type                          | Library indices | Terminal entries | Fixed RGB conversion                                           |
| ---                           | ---             | ---              | ---                                                            |
| [`term_color`](term_color.md) | `0..15`         | `0..15`          | The 16 constants below.                                        |
| [`cube`](cube/index.md)       | `0..215`        | `16..231`        | Each channel index selects one of `0, 95, 135, 175, 215, 255`. |
| [`gray`](gray/index.md)       | `0..23`         | `232..255`       | Each channel is `8 + 10 * index`.                              |

### Named terminal colors

These are the library's fixed Xterm-default RGB equivalents. Rendering a
`term_color` selects the terminal's entry instead of emitting these RGB values.

| Entry | Enumerator                   | RGB constant               | Fixed RGB |
| ---   | ---                          | ---                        | ---       |
| 0     | `term_color::black`          | `rgb::term_black`          | `#000000` |
| 1     | `term_color::red`            | `rgb::term_red`            | `#CD0000` |
| 2     | `term_color::green`          | `rgb::term_green`          | `#00CD00` |
| 3     | `term_color::yellow`         | `rgb::term_yellow`         | `#CDCD00` |
| 4     | `term_color::blue`           | `rgb::term_blue`           | `#0000EE` |
| 5     | `term_color::magenta`        | `rgb::term_magenta`        | `#CD00CD` |
| 6     | `term_color::cyan`           | `rgb::term_cyan`           | `#00CDCD` |
| 7     | `term_color::white`          | `rgb::term_white`          | `#E5E5E5` |
| 8     | `term_color::gray`           | `rgb::term_gray`           | `#7F7F7F` |
| 9     | `term_color::bright_red`     | `rgb::term_bright_red`     | `#FF0000` |
| 10    | `term_color::bright_green`   | `rgb::term_bright_green`   | `#00FF00` |
| 11    | `term_color::bright_yellow`  | `rgb::term_bright_yellow`  | `#FFFF00` |
| 12    | `term_color::bright_blue`    | `rgb::term_bright_blue`    | `#5C5CFF` |
| 13    | `term_color::bright_magenta` | `rgb::term_bright_magenta` | `#FF00FF` |
| 14    | `term_color::bright_cyan`    | `rgb::term_bright_cyan`    | `#00FFFF` |
| 15    | `term_color::bright_white`   | `rgb::term_bright_white`   | `#FFFFFF` |

See the [named constants](rgb/rgb-constants.md#terminal-colors) and
[terminal swatches](../../../named-colors.md#terminal-colors).

### Color cube

For `cube{r, g, b}`, each channel index is in `0..5`. The library's combined
index is `36 * r + 6 * g + b`; the terminal palette entry is 16 greater.
For example, `cube{5, 0, 3}` has library index 183, selects terminal entry 199,
and converts to `rgb{255, 0, 175}`.

See the [complete cube palette](../../../named-colors.md#cube-palette-colors).

### Grayscale ramp

`gray{index}` uses library indices `0..23` and terminal entries `232..255`.
Its fixed RGB equivalent has three equal channels, ranging from 8 to 238 in
steps of 10. For example, `gray{12}` selects entry 244 and converts to
`rgb{128, 128, 128}`. The ramp excludes pure black and pure white.

See the [gray swatches](../../../named-colors.md#gray-palette-colors).

## Indexed output and RGB output

Direct styling with `term_color` uses foreground SGR `30..37` or `90..97`,
and background SGR `40..47` or `100..107`. The enum values are palette indices,
not SGR parameters. Cube and gray colors use `38;5;n` for foreground or
`48;5;n` for background, where `n` is the terminal entry from the table above.

RGB styling uses `38;2;r;g;b` or `48;2;r;g;b` to request explicit channel
values. A customized terminal palette can therefore make an indexed color
look different from its fixed RGB equivalent, including cube and gray colors.
Using an indexed color does not require the terminal to use Xterm's default
appearance.

```cpp
using namespace tjg::color;
auto themed = fg(term_color::red); // Select the terminal's red entry.
auto fixed = fg(rgb::term_red);    // Request RGB {205, 0, 0}.
```

The library uses the fixed conversion for [`to_rgb`](to_rgb.md), RGB
construction from `term_color`, and [color blending](blend.md). A
[`color_t`](color_t.md) preserves its active color kind until an operation
converts it. No palette query is performed by these operations.

## See also

[Terminal palette colors](../../../colors.md#terminal-palette-colors),
[`rgb`](rgb/index.md), [named RGB constants](rgb/rgb-constants.md).
