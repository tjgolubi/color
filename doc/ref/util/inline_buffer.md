# [`tjg::inline_buffer`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L221)

Header: [`<tjg/inline_buffer.hpp>`](index.md#tjginline_bufferhpp).

## Synopsis

```cpp
template<std::size_t N = 256>
using inline_buffer = basic_inline_buffer<char, N>;
```

## Description

The narrow-character alias of [`basic_inline_buffer`](basic_inline_buffer/index.md), with capacity `N`.

## Template parameters

| Parameter | Description                                     |
| ---       | ---                                             |
| `N`       | Inline capacity in characters; defaults to 256. |
