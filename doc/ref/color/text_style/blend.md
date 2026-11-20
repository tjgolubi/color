# [`tjg::color::blend`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L485)

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
