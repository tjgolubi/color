# `tjg::basic_inline_buffer::append`

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

Appends a pointer range, string view, or null-terminated string. The input must fit in the remaining capacity. View and range overloads preserve embedded nulls. The null-terminated overload excludes the terminator.

For the same-type pointer range, the destination start must be outside the source range. Nonempty views and null-terminated strings must use external storage. Character types must match, except that a wide buffer also accepts narrow input and widens each unsigned byte value.
