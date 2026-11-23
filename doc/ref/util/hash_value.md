# [`tjg::hash_value`](https://github.com/tjgolubi/color/blob/bf01e2dda7a63533f350ec19807749fca60a40cb/include/tjg/color/bits/hash-support.hpp#L47)

Header: [`<tjg/hash-support.hpp>`](index.md#hash-helpers).

## Synopsis

```cpp
template<typename T>
auto hash_value(const T& value) noexcept(noexcept(std::hash<T>{}(value)))
  -> hash_t;
```

## Description

Returns `std::hash<T>{}(value)`. Requires a usable standard hasher for `T`. Exceptions from that expression propagate. Hash values are suitable for in-process lookup.
