# [`tjg::hash_values`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/hash_support.hpp#L67)

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
