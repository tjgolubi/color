# [`tjg::color::name_of`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L61)

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
constexpr auto name_of(term_color value) noexcept -> std::string_view;
```

## Description

`value` must be a valid [`term_color`](term_color.md) enumerator. Returns its unqualified spelling as a view of static storage, for example `"bright_red"`.
