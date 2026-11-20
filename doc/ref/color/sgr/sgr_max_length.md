# `tjg::color::sgr_max_length`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
constexpr auto sgr_max_length = std::size_t{60};
```

The upper bound on SGR output length for one style, including a leading reset when needed.
