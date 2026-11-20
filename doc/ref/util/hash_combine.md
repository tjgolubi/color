# `tjg::hash_combine`

Header: [`<tjg/hash_support.hpp>`](index.md#tjghash_supporthpp).

## Synopsis

```cpp
template<typename T>
void hash_combine(hash_t& seed, const T& value)
  noexcept(noexcept(hash_value(value)));
```

## Description

Mixes the hash of `value` into `seed`. Start at zero and combine values in a consistent order. Requires [`hash_value`](hash_value.md) for `T` and propagates its exceptions. Hash values are unsuitable as persistent identifiers.
