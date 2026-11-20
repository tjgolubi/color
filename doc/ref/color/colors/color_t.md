# `tjg::color::color_t`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
using color_t = std::variant<no_color_t, rgb, term_color, cube, gray>;
```

## Description

A [`std::variant`](https://en.cppreference.com/w/cpp/utility/variant.html) that holds one supported color kind. Default construction holds `no_color_t`. Construction and assignment from an alternative select that type. Standard [`std::get`](https://en.cppreference.com/w/cpp/utility/variant/get.html), [`std::get_if`](https://en.cppreference.com/w/cpp/utility/variant/get_if.html), [`std::holds_alternative`](https://en.cppreference.com/w/cpp/utility/variant/holds_alternative.html), and [`std::visit`](https://en.cppreference.com/w/cpp/utility/variant/visit2.html) apply.

| Index | Type                                |
| ---   | ---                                 |
| 0     | [`no_color_t`](no_color_t/index.md) |
| 1     | [`rgb`](rgb/index.md)               |
| 2     | [`term_color`](term_color.md)       |
| 3     | [`cube`](cube/index.md)             |
| 4     | [`gray`](gray/index.md)             |

Values with different alternatives remain distinct even if they produce the same RGB equivalent. Variant ordering compares the alternative index first. [`std::hash<color_t>`](hash/index.md) is provided; see also [standard variant hashing](https://en.cppreference.com/w/cpp/utility/variant/hash.html). References obtained with [`std::get`](https://en.cppreference.com/w/cpp/utility/variant/get.html) refer to storage in the variant and should not outlive it or a change of alternative.
