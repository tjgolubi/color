# `tjg::basic_inline_buffer::resize`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
constexpr void resize(std::size_t new_size, Char fill = Char{0}) noexcept;
```

## Description

Sets the size to `new_size`, which must be at most `Size`. Growing fills newly exposed characters with `fill`. Shrinking leaves the stored characters intact.

## Parameters

| Parameter  | Description                                                |
| ---        | ---                                                        |
| `new_size` | New initialized length, at most `Size`.                    |
| `fill`     | Value used for new characters on growth; defaults to zero. |
