# `tjg::color::write_debug_value`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
template<std::output_iterator<char> OutputIt>
auto write_debug_value(OutputIt out, emphasis value) -> OutputIt;
```

## Description

Writes one character per set [`emphasis`](text_style/emphasis.md) bit in declaration order and returns the advanced iterator. The letters and symbols `bfi_!r?-` stand for bold, faint, italic, underline, blink, reverse, conceal, and strike. `emphasis::none` writes `{}`. For spelled-out names, use [`write_value`](write_value.md).
