# [`tjg::color::text_style::absolute`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L99)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto absolute(bool enable = true) noexcept -> text_style&;
```

## Description

Sets or clears the absolute flag and returns `*this`. An absolute style starts from terminal defaults when rendered. See also the [free function](../absolute.md).
