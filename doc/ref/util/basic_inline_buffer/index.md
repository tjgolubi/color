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

## Description

A character buffer with fixed inline capacity. It maintains an explicit size. Its contents need not be null-terminated. `data()` points to its storage and `view()` covers the initialized prefix of length `size()`.

A wide buffer accepts narrow characters by widening their unsigned byte values. This operation does not decode UTF-8. See [`inline_buffer`](../inline_buffer.md) for the narrow alias.

## Type definitions

| Name                                   | Description                                                                 |
| ---                                    | ---                                                                         |
| [`inline_buffer`](../inline_buffer.md) | Narrow-character alias of `basic_inline_buffer`, parameterized by capacity. |

## Template parameters

| Parameter | Description                                                   |
| ---       | ---                                                           |
| `Char`    | `char` or `wchar_t`, satisfying [`CharType`](../CharType.md). |
| `Size`    | Positive inline capacity in characters; defaults to 256.      |

## Nested types

| Name         | Definition                         |
| ---          | ---                                |
| `value_type` | `Char`, the stored character type. |

## Member functions

### Construction and assignment

| Name                                    | Description                                                                                 |
| ---                                     | ---                                                                                         |
| [`basic_inline_buffer`](constructor.md) | Constructs the value; see the constructor overloads.                                        |
| [`operator=`](operator-assignment.md)   | Copies the initialized prefix and size, leaving the rest of the destination storage intact. |

### Element access

| Name              | Description                                         |
| ---               | ---                                                 |
| [`data`](data.md) | Provides access to the start of the buffer storage. |
| [`view`](view.md) | Returns a string view of the initialized prefix.    |

### Iterators

| Name                | Description                                                       |
| ---                 | ---                                                               |
| [`begin`](begin.md) | Returns a read-only pointer to the start of the output range.     |
| [`end`](end.md)     | Returns a read-only pointer one past the end of the output range. |

### Capacity

| Name                | Description                                                                                       |
| ---                 | ---                                                                                               |
| [`empty`](empty.md) | Returns true if `size()` is zero.                                                                 |
| [`size`](size.md)   | Returns the number of characters in the initialized prefix, at most the template capacity `Size`. |

### Modifiers

| Name                                              | Description                                                                           |
| ---                                               | ---                                                                                   |
| [`clear`](clear.md)                               | Sets the size to zero and leaves the stored characters intact.                        |
| [`resize`](resize.md)                             | Sets the size to `new_size`, which must be at most `Size`.                            |
| [`resize_and_overwrite`](resize_and_overwrite.md) | Calls `std::move(op)(data(), limit)` and sets the size to the returned prefix length. |
| [`push_back`](push_back.md)                       | Appends one character.                                                                |
| [`append`](append.md)                             | Appends characters within the remaining capacity.                                     |
