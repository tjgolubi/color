# [`tjg::basic_inline_buffer::append`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L167)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
template<CharType C>
  requires (std::same_as<C, Char>
         || (std::same_as<Char, wchar_t> && std::same_as<C, char>))
constexpr void append(const C* first, const C* last) noexcept;

template<CharType C, typename Traits>
  requires (std::same_as<C, Char>
         || (std::same_as<Char, wchar_t> && std::same_as<C, char>))
constexpr void append(std::basic_string_view<C, Traits> text) noexcept;

template<CharType C>
  requires (std::same_as<C, Char>
         || (std::same_as<Char, wchar_t> && std::same_as<C, char>))
constexpr void append(const C* cp) noexcept;

constexpr void append(std::string_view text) noexcept
  requires std::same_as<Char, wchar_t>;
```

## Description

Appends characters within the remaining capacity. Character types must match, except that a wide buffer also accepts narrow input and widens each unsigned byte value. This does not decode UTF-8.

### Pointer range: `append(const C* first, const C* last)`

Appends a valid half-open range, preserving embedded nulls. The range must fit. For a same-type copy, the destination start must be outside the source range.

### String view: `append(std::basic_string_view<C, Traits> text)`

Appends every character, including embedded nulls. The input must fit, and a nonempty view must refer to external storage.

### Null-terminated input: `append(const C* cp)`

Appends a valid external null-terminated string, excluding its terminator. The characters must fit.

### Narrow view for a wide buffer: `append(std::string_view text)`

Available when `Char` is `wchar_t`. Accepts implicit conversions to `std::string_view`, then widens each unsigned byte value. The input must fit, and a nonempty view must refer to external storage.

## Parameters

| Parameter       | Description                                             |
| ---             | ---                                                     |
| `first`, `last` | Valid half-open source range.                           |
| `text`          | String view containing the source characters.           |
| `cp`            | Non-null pointer to an external null-terminated string. |
