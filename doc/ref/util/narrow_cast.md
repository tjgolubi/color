# `tjg::narrow_cast`

Header: [`<tjg/utility.hpp>`](index.md#tjgutilityhpp).

## Synopsis

```cpp
template<typename T, typename U>
constexpr auto narrow_cast(U x) noexcept -> T;
```

Spells a narrowing conversion as `static_cast<T>(x)`. The cast must be well-formed. It performs no range checking or clamping.
