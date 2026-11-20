# `tjg::basic_inline_buffer::size`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto size() const noexcept -> std::size_t;
```

Returns the number of characters in the initialized prefix, at most the template capacity `Size`.
