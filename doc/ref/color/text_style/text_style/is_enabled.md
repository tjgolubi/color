# `tjg::color::text_style::is_enabled`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto is_enabled(emphasis em) const noexcept -> bool;
```

Returns true if any bit in `em` is enabled. An empty mask returns false.
