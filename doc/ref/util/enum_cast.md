# [`tjg::enum_cast`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/utility.hpp#L21)

Header: [`<tjg/utility.hpp>`](index.md#tjgutilityhpp).

## Synopsis

```cpp
template<typename T, typename U>
constexpr auto enum_cast(U x) noexcept -> T;
```

## Description

Spells an enum-related conversion as `static_cast<T>(x)`. The cast must be well-formed. It performs no range checking or clamping.
