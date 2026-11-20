# `std::hash::operator()` for colors

Type: [`std::hash` specializations](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// T is the type handled by the specialization.
auto operator()(T value) const noexcept -> std::size_t;
```

Returns a hash of the argument. Equal keys produce equal hashes. Hash values
are suitable for in-process lookup and should not be used as persistent identifiers.
