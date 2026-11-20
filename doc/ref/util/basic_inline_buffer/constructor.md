# [`tjg::basic_inline_buffer::basic_inline_buffer`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L51)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr basic_inline_buffer() noexcept;

constexpr basic_inline_buffer(const basic_inline_buffer&) noexcept;
```

## Description

Constructs a fixed-capacity buffer.

### Default construction: `basic_inline_buffer()`

Creates an empty buffer. At runtime, storage is left uninitialized.

### Copy construction: `basic_inline_buffer(const basic_inline_buffer&)`

Copies the initialized prefix. At runtime, unused storage is left uninitialized.
