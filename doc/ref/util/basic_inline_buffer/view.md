# [`tjg::basic_inline_buffer::view`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L98)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto view() const noexcept -> std::basic_string_view<Char>;
```

## Description

Returns a string view of the initialized prefix. The view borrows storage and captures the current size. It does not track subsequent size changes.
