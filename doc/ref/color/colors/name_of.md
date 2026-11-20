# `tjg::color::name_of`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto name_of(term_color value) noexcept -> std::string_view;
```

`value` must be a valid [`term_color`](term_color.md) enumerator. Returns its unqualified spelling as a view of static storage, for example `"bright_red"`.
