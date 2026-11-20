# `tjg::color::basic_styled_text::operator=`

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto operator=(const basic_styled_text& other) -> basic_styled_text&;

auto operator=(basic_styled_text&& other) noexcept -> basic_styled_text&;
```

Replaces the current value with a copy or moved value of the source and returns `*this`. Self-assignment leaves the value unchanged. Copy assignment may allocate.
