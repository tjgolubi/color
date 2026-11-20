# `tjg::basic_inline_buffer::operator=`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto operator=(const basic_inline_buffer&) noexcept
  -> basic_inline_buffer&;
```

Copies the initialized prefix and size, leaving the rest of the destination storage intact. Returns `*this`.
