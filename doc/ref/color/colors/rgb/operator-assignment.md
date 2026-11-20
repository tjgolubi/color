# [`tjg::color::rgb::operator=`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L76)

Type: [`tjg::color::rgb`](index.md).

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared.
constexpr auto operator=(const rgb&) noexcept -> rgb&;
constexpr auto operator=(rgb&&) noexcept -> rgb&;
```

## Description

Assignment replaces the three RGB channels from the source and returns `*this`.

### Copy assignment: const-reference source

Assigns from the source using the copy-assignment overload shown in the synopsis.

### Move assignment: rvalue-reference source

Assigns from the source using the move-assignment overload shown in the synopsis.
