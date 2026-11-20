# [`tjg::basic_inline_buffer::push_back`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/inline_buffer.hpp#L152)

Type: [`tjg::basic_inline_buffer`](index.md).

Header: [`<tjg/inline_buffer.hpp>`](../index.md#tjginline_bufferhpp).

## Synopsis

```cpp
template<CharType C>
  requires (std::same_as<C, Char>
         || (std::same_as<Char, wchar_t> && std::same_as<C, char>))
constexpr void push_back(C value) noexcept;
```

## Description

Appends one character. The buffer must have space for it. `C` must match `Char`, or be `char` when `Char` is `wchar_t`. Narrow characters in a wide buffer are widened through `unsigned char`.
