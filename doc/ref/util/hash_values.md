# `tjg::hash_values`

Header: [`<tjg/hash_support.hpp>`](index.md#tjghash_supporthpp).

## Synopsis

```cpp
template<typename... T>
auto hash_values(const T&... values)
  noexcept((noexcept(hash_combine(std::declval<hash_t&>(), values)) && ...))
  -> hash_t;
```

## Description

Starts with a zero seed and calls [`hash_combine`](hash_combine.md) once per argument in order. An empty argument list returns zero.
