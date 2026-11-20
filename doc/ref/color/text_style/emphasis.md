# [`tjg::color::emphasis`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/emphasis.hpp#L19)

Header: [`<tjg/color/text_style.hpp>`](index.md).

## Synopsis

```cpp
enum class emphasis : std::uint8_t {
  none,      // implementation-defined
  bold,      // implementation-defined
  faint,     // implementation-defined
  italic,    // implementation-defined
  underline, // implementation-defined
  blink,     // implementation-defined
  reverse,   // implementation-defined
  conceal,   // implementation-defined
  strike     // implementation-defined
};
constexpr auto operator|(emphasis lhs, emphasis rhs) noexcept -> emphasis;
constexpr auto operator|=(emphasis& lhs, emphasis rhs) noexcept -> emphasis&;
```

## Description

Combines independent text attributes as a bit mask. `none` selects no attributes. `operator|` returns the union and `operator|=` updates its left operand. The bit values are distinct from [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) parameter numbers. See [Text styles](text_style/index.md) and the [attribute table](../../../emphasis.md#attributes).

| Attribute   | Meaning                                    |
| ---         | ---                                        |
| `none`      | No emphasis attributes.                    |
| `bold`      | Increased text intensity.                  |
| `faint`     | Decreased text intensity.                  |
| `italic`    | Italic text.                               |
| `underline` | Underlined text.                           |
| `blink`     | Blinking text.                             |
| `reverse`   | Reversed foreground and background colors. |
| `conceal`   | Concealed text.                            |
| `strike`    | Crossed-out text.                          |
