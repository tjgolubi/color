# `std::formatter::format` for {color}

Type: [`std::formatter` specializations](index.md).

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
// T is the type handled by the specialization.
template<typename FormatContext>
auto format(const T& value, FormatContext& ctx) const -> decltype(ctx.out());
```

Writes the selected representation to the format context and returns the
advanced output iterator. The [specialization table](index.md) describes the
representations for each type. A styled argument delegates to its underlying
formatter while applying the argument's style.
