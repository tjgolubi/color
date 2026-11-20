# `tjg::color::blend`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
template<Color First, Color Second, Color... Colors>
constexpr auto blend(First first, Second second, Colors... rest) noexcept -> rgb;

// Second and Colors must be concrete colors, color_t, or no_color_t.
template<typename Second, typename... Colors>
constexpr auto blend(color_t first, Second second, Colors... rest) noexcept
  -> color_t;
```

## Description

Averages two or more colors. Each RGB channel is summed before division and fractional results round down.

### Concrete colors: `blend(First first, Second second, Colors... rest)`

Converts concrete colors to their fixed RGB equivalents and returns the average as `rgb`.

### Variant colors: `blend(color_t first, Second second, Colors... rest)`

If any input is a `color_t` or `no_color_t`, returns a [`color_t`](color_t.md). Unspecified inputs are excluded. Zero specified inputs give `no_color`; one preserves its kind and value; two or more yield `rgb`.

## Parameters

| Parameter                 | Description                                                               |
| ---                       | ---                                                                       |
| `first`, `second`, `rest` | Two or more colors; the variant overload also accepts unspecified values. |

## Return value

`rgb` for concrete-color inputs, or `color_t` for the variant overload as described above.

## See also

[Style blending](../text_style/blend.md).
