# `tjg::color::blend`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
// All arguments must be text_style values.
template<typename First, typename Second, typename... Styles>
constexpr auto blend(First first, Second second, Styles... rest) noexcept
  -> text_style;
```

## Description

Blends two or more styles. Foreground and background are [blended independently](../colors/blend.md), and emphasis attributes are combined. The result is always relative.

Each absolute input must specify both colors, since the RGB value of terminal defaults is unknown. Assertion-enabled builds check this precondition.
