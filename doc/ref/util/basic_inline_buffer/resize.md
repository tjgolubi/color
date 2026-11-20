# `tjg::basic_inline_buffer::resize`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr void resize(std::size_t new_size, Char fill = Char{0}) noexcept;
```

Sets the size to `new_size`, which must be at most `Size`. Growing fills newly exposed characters with `fill`. Shrinking leaves the stored characters intact.
