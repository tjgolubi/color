# `tjg::basic_inline_buffer::data`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto data() noexcept -> Char*;

constexpr auto data() const noexcept -> const Char*;
```

Returns a pointer to the start of the buffer storage. Its constness follows the buffer. Use [`size()`](size.md) for the length of the populated range.
