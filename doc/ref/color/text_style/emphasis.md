# `tjg::color::emphasis`

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
enum class emphasis : std::uint8_t {
  none = 0, bold = 1 << 0, faint = 1 << 1, italic = 1 << 2,
  underline = 1 << 3, blink = 1 << 4, reverse = 1 << 5,
  conceal = 1 << 6, strike = 1 << 7
};
constexpr auto operator|(emphasis lhs, emphasis rhs) noexcept -> emphasis;
constexpr auto operator|=(emphasis& lhs, emphasis rhs) noexcept -> emphasis&;
```

Combines independent text attributes as a bit mask. `none` selects no attributes. `operator|` returns the union and `operator|=` updates its left operand. The bit values are distinct from SGR parameter numbers. See [Text styles](text_style.md) and the [attribute table](../../../emphasis.md#attributes).
