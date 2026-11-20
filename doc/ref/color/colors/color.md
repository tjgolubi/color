# [`tjg::color::color`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L321)

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
constexpr rgb color(double red, double green, double blue) noexcept;
constexpr rgb color(double grayscale) noexcept;
```

## Description

Returns an [`rgb`](rgb/index.md) from normalized inputs in `0.0..1.0`. In the current implementation, an interior value maps to the integer part of `256 * value`; the endpoints map to 0 and 255. Inputs below or above the range map to the nearest endpoint, and NaN maps to 0.

### Three channels: `color(double red, double green, double blue)`

Converts each normalized component independently to the corresponding RGB channel.

### Grayscale: `color(double grayscale)`

Applies the same normalized component to all three RGB channels.

## Parameters

| Parameter              | Description                                                             |
| ---                    | ---                                                                     |
| `red`, `green`, `blue` | Independent normalized channels in the three-argument overload.         |
| `grayscale`            | Normalized value applied to every channel in the one-argument overload. |

## Return value

The RGB value formed from the normalized channels.

## Example

```cpp
using namespace tjg::color;
constexpr auto accent = color(0.1, 0.6, 1.0); // rgb{25, 153, 255}
constexpr auto shade = color(0.25);           // rgb::dark_gray
```
