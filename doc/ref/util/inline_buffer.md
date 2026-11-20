# `tjg::inline_buffer`

Header: [`<tjg/inline_buffer.hpp>`](index.md#tjginline_bufferhpp).

## Synopsis

```cpp
template<std::size_t N = 256>
using inline_buffer = basic_inline_buffer<char, N>;
```

The narrow-character alias of [`basic_inline_buffer`](basic_inline_buffer/index.md), with capacity `N`.
