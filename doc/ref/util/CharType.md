# [`tjg::CharType`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/utility.hpp#L12)

Header: [`<tjg/utility.hpp>`](index.md#tjgutilityhpp).

## Synopsis

```cpp
template<typename T>
concept CharType = std::same_as<T, char> || std::same_as<T, wchar_t>;
```

## Description

Constrains character parameters to `char` or `wchar_t`. Cv-qualified types, references, and the other standard character types do not satisfy it.

## Template parameters

| Parameter | Description                                              |
| ---       | ---                                                      |
| `T`       | Type tested for an exact match with `char` or `wchar_t`. |
