# `tjg::hash_value`

Header: [`<tjg/hash_support.hpp>`](index.md#tjghash_supporthpp).

## Synopsis

```cpp
template<typename T>
auto hash_value(const T& value) noexcept(noexcept(std::hash<T>{}(value)))
  -> hash_t;
```

## Description

Returns `std::hash<T>{}(value)`. Requires a usable standard hasher for `T`. Exceptions from that expression propagate. Hash values are suitable for in-process lookup.
