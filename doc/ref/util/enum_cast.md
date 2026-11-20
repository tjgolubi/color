# `tjg::enum_cast`

Header: [`<tjg/utility.hpp>`](index.md#tjgutilityhpp).

## Synopsis

```cpp
template<typename T, typename U>
constexpr auto enum_cast(U x) noexcept -> T;
```

## Description

Spells an enum-related conversion as `static_cast<T>(x)`. The cast must be well-formed. It performs no range checking or clamping.
