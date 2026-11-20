# [`tjg::color::rgb::operator value_type`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L118)

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr explicit operator value_type() const noexcept;
```

## Description

Converts to [`value_type`](index.md#nested-types). Returns the color as `0x00RRGGBB`. The conversion is explicit.
