# `tjg::basic_inline_buffer::basic_inline_buffer`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr basic_inline_buffer() noexcept;

constexpr basic_inline_buffer(const basic_inline_buffer&) noexcept;
```

Default construction creates an empty buffer. Copy construction copies the initialized prefix. At runtime the unused storage is left uninitialized.
