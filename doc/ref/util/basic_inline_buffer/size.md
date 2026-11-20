# [`tjg::basic_inline_buffer::size`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L84)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto size() const noexcept -> std::size_t;
```

## Description

Returns the number of characters in the initialized prefix, at most the template capacity `Size`.
