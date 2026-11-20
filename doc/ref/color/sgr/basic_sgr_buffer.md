# `tjg::color::basic_sgr_buffer`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
using basic_sgr_buffer = basic_inline_buffer<Char, sgr_max_length>;
```

A [fixed-capacity buffer](../../util/basic_inline_buffer.md) sized for one style’s SGR sequence. See also the narrow alias [`sgr_buffer`](sgr_buffer.md).
