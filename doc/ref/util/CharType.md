# `tjg::CharType`

Header: [`<tjg/utility.hpp>`](index.md#tjgutilityhpp).

## Synopsis

```cpp
template<typename T>
concept CharType = std::same_as<T, char> || std::same_as<T, wchar_t>;
```

Constrains character parameters to `char` or `wchar_t`. Cv-qualified types, references, and the other standard character types do not satisfy it.
