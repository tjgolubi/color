# `tjg::basic_inline_buffer::resize_and_overwrite`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
template<typename Operation>
constexpr void resize_and_overwrite(std::size_t limit, Operation op) noexcept;
```

## Description

Calls `std::move(op)(data(), limit)` and sets the size to the returned prefix length. The limit must be at most `Size`. The callback must not throw and must initialize the prefix it reports. Its result must be a `std::size_t` no greater than `limit`.

## Parameters

| Parameter | Description                                                                                                   |
| ---       | ---                                                                                                           |
| `limit`   | Maximum initialized prefix available to the callback, at most `Size`.                                         |
| `op`      | Non-throwing callback invoked with `(data(), limit)`; returns the initialized prefix length, at most `limit`. |
