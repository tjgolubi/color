# [`tjg::hash_combine`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/hash_support.hpp#L55)

Header: [`<tjg/hash_support.hpp>`](index.md#tjghash_supporthpp).

## Synopsis

```cpp
template<typename T>
void hash_combine(hash_t& seed, const T& value)
  noexcept(noexcept(hash_value(value)));
```

## Description

Mixes the hash of `value` into `seed`. Start at zero and combine values in a consistent order. Requires [`hash_value`](hash_value.md) for `T` and propagates its exceptions. Hash values are unsuitable as persistent identifiers.
