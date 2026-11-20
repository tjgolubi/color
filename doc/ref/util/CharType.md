# `tjg::CharType`

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
