# [`tjg::color::text_style::operator=`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L53)

Type: [`tjg::color::text_style`](index.md).

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
// Implicitly declared.
constexpr auto operator=(const text_style&) noexcept -> text_style&;
constexpr auto operator=(text_style&&) noexcept -> text_style&;
```

## Description

Assignment replaces the stored colors, emphasis, and absolute flag from the source and returns `*this`.

### Copy assignment: const-reference source

Assigns from the source using the copy-assignment overload shown in the synopsis.

### Move assignment: rvalue-reference source

Assigns from the source using the move-assignment overload shown in the synopsis.
