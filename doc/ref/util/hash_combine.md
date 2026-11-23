# [`tjg::hash_combine`](https://github.com/tjgolubi/color/blob/bf01e2dda7a63533f350ec19807749fca60a40cb/include/tjg/color/bits/hash-support.hpp#L55)

Header: [`<tjg/hash-support.hpp>`](index.md#hash-helpers).

## Synopsis

```cpp
template<typename T>
void hash_combine(hash_t& seed, const T& value)
  noexcept(noexcept(hash_value(value)));
```

## Description

Mixes the hash of `value` into `seed`. Start at zero and combine values in a consistent order. Requires [`hash_value`](hash_value.md) for `T` and propagates its exceptions. Hash values are unsuitable as persistent identifiers.
