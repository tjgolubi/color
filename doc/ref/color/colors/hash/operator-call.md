# [`std::hash::operator()` for colors](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp)

Type: [`std::hash` specializations](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// T is the type handled by the specialization.
auto operator()(T value) const noexcept -> std::size_t;
```

## Description

Returns a hash of the argument. Equal keys produce equal hashes. Hash values
are suitable for in-process lookup and should not be used as persistent identifiers.
