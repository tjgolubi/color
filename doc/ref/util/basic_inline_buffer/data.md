# [`tjg::basic_inline_buffer::data`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L91)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto data() noexcept -> Char*;

constexpr auto data() const noexcept -> const Char*;
```

## Description

Provides access to the start of the buffer storage. Use [`size()`](size.md) for the length of the populated range.

### Writable access: `data()`

Returns a `Char*` to the start of the storage.

### Read-only access: `data() const`

Returns a `const Char*` to the start of the storage.
