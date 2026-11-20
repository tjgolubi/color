# `tjg::color::text_style::absolute`

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto absolute(bool enable = true) noexcept -> text_style&;
```

Sets or clears the absolute flag and returns `*this`. An absolute style starts from terminal defaults when rendered. See also the [free function](../absolute.md).
