# `tjg::color::no_color_t::operator=`

Type: [`tjg::color::no_color_t`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared.
constexpr auto operator=(const no_color_t&) noexcept -> no_color_t&;
constexpr auto operator=(no_color_t&&) noexcept -> no_color_t&;
```

## Description

Assignment replaces the unspecified-color value from the source and returns `*this`.

### Copy assignment: const-reference source

Assigns from the source using the copy-assignment overload shown in the synopsis.

### Move assignment: rvalue-reference source

Assigns from the source using the move-assignment overload shown in the synopsis.
