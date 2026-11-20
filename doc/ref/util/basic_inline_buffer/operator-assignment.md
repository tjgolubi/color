# [`tjg::basic_inline_buffer::operator=`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L66)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto operator=(const basic_inline_buffer&) noexcept
  -> basic_inline_buffer&;
```

## Description

Copies the initialized prefix and size, leaving the rest of the destination storage intact. Returns `*this`.
