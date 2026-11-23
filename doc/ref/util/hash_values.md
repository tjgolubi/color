# [`tjg::hash_values`](https://github.com/tjgolubi/color/blob/bf01e2dda7a63533f350ec19807749fca60a40cb/include/tjg/color/bits/hash-support.hpp#L67)

Header: [`<tjg/hash-support.hpp>`](index.md#hash-helpers).

## Synopsis

```cpp
template<typename... T>
auto hash_values(const T&... values)
  noexcept((noexcept(hash_combine(std::declval<hash_t&>(), values)) && ...))
  -> hash_t;
```

## Description

Starts with a zero seed and calls [`hash_combine`](hash_combine.md) once per
argument in order. Each argument must have a usable `std::hash` specialization.
The function is `noexcept` when all of those calls are `noexcept`. An empty
argument list returns zero.
