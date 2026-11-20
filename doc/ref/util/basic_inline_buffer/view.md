# `tjg::basic_inline_buffer::view`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto view() const noexcept -> std::basic_string_view<Char>;
```

Returns a string view of the initialized prefix. The view borrows storage and captures the current size. It does not track subsequent size changes.
