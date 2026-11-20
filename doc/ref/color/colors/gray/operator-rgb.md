# [`tjg::color::gray::operator rgb`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L413)

Type: [`tjg::color::gray`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
constexpr operator rgb() const noexcept;
```

## Description

Converts implicitly to [`rgb`](../rgb/index.md). Each channel is `8 + 10 * index()`.
