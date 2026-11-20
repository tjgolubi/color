# [`tjg::hash_value`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/hash_support.hpp#L47)

Header: [`<tjg/hash_support.hpp>`](index.md#tjghash_supporthpp).

## Synopsis

```cpp
template<typename T>
auto hash_value(const T& value) noexcept(noexcept(std::hash<T>{}(value)))
  -> hash_t;
```

## Description

Returns `std::hash<T>{}(value)`. Requires a usable standard hasher for `T`. Exceptions from that expression propagate. Hash values are suitable for in-process lookup.
