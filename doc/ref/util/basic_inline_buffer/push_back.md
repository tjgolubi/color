# `tjg::basic_inline_buffer::push_back`

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
template<CharType C>
  requires (std::same_as<C, Char>
         || (std::same_as<Char, wchar_t> && std::same_as<C, char>))
constexpr void push_back(C value) noexcept;
```

Appends one character. The buffer must have space for it. `C` must match `Char`, or be `char` when `Char` is `wchar_t`. Narrow characters in a wide buffer are widened through `unsigned char`.
