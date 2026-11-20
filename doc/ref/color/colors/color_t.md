# `tjg::color::color_t`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
using color_t = std::variant<no_color_t, rgb, term_color, cube, gray>;
```

A variant that holds one supported color kind. Default construction holds `no_color_t`. Construction and assignment from an alternative select that type. Standard `std::get`, `std::get_if`, `std::holds_alternative`, and `std::visit` apply.

| Index | Type |
| --- | --- |
| 0 | [`no_color_t`](no_color_t.md) |
| 1 | [`rgb`](rgb.md) |
| 2 | [`term_color`](term_color.md) |
| 3 | [`cube`](cube.md) |
| 4 | [`gray`](gray.md) |

Values with different alternatives remain distinct even if they produce the same RGB equivalent. Variant ordering compares the alternative index first. `std::hash<color_t>` is provided. References obtained with `std::get` refer to storage in the variant and should not outlive it or a change of alternative.
