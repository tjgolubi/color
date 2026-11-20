# [`tjg::basic_inline_buffer::end`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L109)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto end() const noexcept -> const Char*;
```

## Description

Returns a read-only pointer one past the end of the output range. It equals [`begin()`](begin.md) for an empty buffer.
