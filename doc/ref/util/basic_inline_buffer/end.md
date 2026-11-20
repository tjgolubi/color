# `tjg::basic_inline_buffer::end`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr auto end() const noexcept -> const Char*;
```

## Description

Returns a read-only pointer one past the end of the output range. It equals [`begin()`](begin.md) for an empty buffer.
