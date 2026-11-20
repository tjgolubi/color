# `tjg::basic_inline_buffer`

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
template<CharType Char, std::size_t Size = 256>
  requires (Size > 0)
class basic_inline_buffer {
public:
  using value_type = Char;
  constexpr basic_inline_buffer() noexcept;
  constexpr basic_inline_buffer(const basic_inline_buffer&) noexcept;
  constexpr auto operator=(const basic_inline_buffer&) noexcept
    -> basic_inline_buffer&;
  constexpr auto empty() const noexcept -> bool;
  constexpr auto size() const noexcept -> std::size_t;
  constexpr auto data() noexcept -> Char*;
  constexpr auto data() const noexcept -> const Char*;
  constexpr auto view() const noexcept -> std::basic_string_view<Char>;
  constexpr auto begin() const noexcept -> const Char*;
  constexpr auto end() const noexcept -> const Char*;
  constexpr void clear() noexcept;
  constexpr void resize(std::size_t new_size, Char fill = Char{0}) noexcept;
  template<typename Operation>
  constexpr void resize_and_overwrite(std::size_t limit, Operation op) noexcept;

  // C is Char, or char when Char is wchar_t.
  template<CharType C> constexpr void push_back(C value) noexcept;
  template<CharType C> constexpr void append(const C* first, const C* last) noexcept;
  template<CharType C, typename Traits>
  constexpr void append(std::basic_string_view<C, Traits> text) noexcept;
  template<CharType C> constexpr void append(const C* cp) noexcept;
  constexpr void append(std::string_view text) noexcept
    requires std::same_as<Char, wchar_t>;
};
```

A character buffer with fixed inline capacity. It starts empty and maintains an explicit size. Its contents need not be null-terminated. `data()` points to its storage and `view()` covers the initialized prefix of length `size()`.

| Operation | Requirements and effects |
| --- | --- |
| `clear()` | Sets the size to zero. |
| `resize(new_size, fill)` | Requires `new_size <= Size`. Fills new positions on growth. |
| `resize_and_overwrite(limit, op)` | Requires `limit <= Size`. Calls `op(data(), limit)`. The callback must not throw and must return the initialized prefix length, at most `limit`. |
| `push_back(value)` | Appends one character within capacity. |
| `append(first, last)` | Appends a valid half-open range within capacity. For a same-type copy, the destination start must be outside the source range. |
| `append(view)` | Appends all characters, including embedded nulls. Nonempty views must refer to external storage and fit. |
| `append(cp)` | Appends a valid external null-terminated string, excluding the terminator. The characters must fit. |

A wide buffer accepts narrow characters by widening their unsigned byte values. This operation does not decode UTF-8. See [`inline_buffer`](../inline_buffer.md) for the narrow alias.

## Member functions

- [`basic_inline_buffer`](constructor.md)
- [`operator=`](operator-assignment.md)
- [`empty`](empty.md)
- [`size`](size.md)
- [`data`](data.md)
- [`view`](view.md)
- [`begin`](begin.md)
- [`end`](end.md)
- [`clear`](clear.md)
- [`resize`](resize.md)
- [`resize_and_overwrite`](resize_and_overwrite.md)
- [`push_back`](push_back.md)
- [`append`](append.md)
