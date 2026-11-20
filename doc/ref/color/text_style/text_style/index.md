# [`tjg::color::text_style`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/text_style.hpp#L53)

Header: [`<tjg/color/text_style.hpp>`](../index.md).

## Synopsis

```cpp
class text_style {
public:
  constexpr text_style(emphasis emp = emphasis::none, color_t fg = {},
                       color_t bg = {}) noexcept;
  constexpr text_style(color_t fg, color_t bg = {},
                       emphasis emp = emphasis::none) noexcept;

  constexpr auto empty() const noexcept -> bool;
  constexpr auto clear() noexcept -> text_style&;
  constexpr auto absolute(bool enable = true) noexcept -> text_style&;
  constexpr auto is_absolute() const noexcept -> bool;
  constexpr auto overlay(const text_style& other) noexcept -> text_style&;
  constexpr auto underlay(const text_style& other) noexcept -> text_style&;

  constexpr auto has_fg() const noexcept -> bool;
  constexpr auto has_bg() const noexcept -> bool;
  constexpr auto has_emph() const noexcept -> bool;
  constexpr auto fg() const noexcept -> color_t;
  constexpr auto bg() const noexcept -> color_t;
  constexpr auto emph() const noexcept -> emphasis;
  constexpr auto fg(color_t color) noexcept -> text_style&;
  constexpr auto bg(color_t color) noexcept -> text_style&;
  constexpr auto emph(emphasis em) noexcept -> text_style&;
  constexpr auto set(emphasis em, bool enable = true) noexcept -> text_style&;
  constexpr auto is_enabled(emphasis em) const noexcept -> bool;
  constexpr auto bold(bool enable = true) noexcept -> text_style&;
  constexpr auto is_bold() const noexcept -> bool;
  constexpr auto faint(bool enable = true) noexcept -> text_style&;
  constexpr auto is_faint() const noexcept -> bool;
  constexpr auto italic(bool enable = true) noexcept -> text_style&;
  constexpr auto is_italic() const noexcept -> bool;
  constexpr auto underline(bool enable = true) noexcept -> text_style&;
  constexpr auto is_underline() const noexcept -> bool;
  constexpr auto blink(bool enable = true) noexcept -> text_style&;
  constexpr auto is_blink() const noexcept -> bool;
  constexpr auto reverse(bool enable = true) noexcept -> text_style&;
  constexpr auto is_reverse() const noexcept -> bool;
  constexpr auto conceal(bool enable = true) noexcept -> text_style&;
  constexpr auto is_conceal() const noexcept -> bool;
  constexpr auto strike(bool enable = true) noexcept -> text_style&;
  constexpr auto is_strike() const noexcept -> bool;
  constexpr auto operator==(const text_style&) const noexcept -> bool;
  constexpr auto operator<=>(const text_style&) const noexcept -> std::strong_ordering;
};
```

## Description

Stores optional foreground and background [`color_t`](../../colors/color_t.md) values, [`emphasis`](../emphasis.md), and an absolute flag. An absolute-only style is nonempty.

Both composition members combine emphasis attributes and the absolute flag and return `*this`. Equality, ordering, and [`std::hash<text_style>`](../hash/index.md) include the stored colors, emphasis, and absolute flag. See the [text styles guide](../../../../text-style.md) and [stream insertion](../../operator-insertion.md).

## Member functions

### Construction and assignment

| Name                                  | Description                                                                                             |
| ---                                   | ---                                                                                                     |
| [`text_style`](constructor.md)        | Constructs the value; see the constructor overloads.                                                    |
| [`operator=`](operator-assignment.md) | Assignment replaces the stored colors, emphasis, and absolute flag from the source and returns `*this`. |

### State and composition

| Name                            | Description                                                                                       |
| ---                             | ---                                                                                               |
| [`empty`](empty.md)             | Returns true if neither color is specified, there is no emphasis, and the absolute flag is clear. |
| [`clear`](clear.md)             | Restores the default relative style and returns `*this`.                                          |
| [`absolute`](absolute.md)       | Sets or clears the absolute flag and returns `*this`.                                             |
| [`is_absolute`](is_absolute.md) | Returns true if the style is absolute.                                                            |
| [`overlay`](overlay.md)         | Specified colors from `other` replace the corresponding colors in this style.                     |
| [`underlay`](underlay.md)       | Colors from `other` fill the corresponding unspecified channels in this style.                    |

### Colors and emphasis

| Name                          | Description                                                               |
| ---                           | ---                                                                       |
| [`has_fg`](has_fg.md)         | Returns true if a foreground color is specified.                          |
| [`has_bg`](has_bg.md)         | Returns true if a background color is specified.                          |
| [`has_emph`](has_emph.md)     | Returns true if any emphasis is enabled.                                  |
| [`fg`](fg.md)                 | Reads or changes the foreground.                                          |
| [`bg`](bg.md)                 | Reads or changes the background.                                          |
| [`emph`](emph.md)             | Reads or replaces the emphasis attributes.                                |
| [`set`](set.md)               | Enables all bits in `em` when `enable` is true, or clears them otherwise. |
| [`is_enabled`](is_enabled.md) | Returns true if any bit in `em` is enabled.                               |

### Named emphasis attributes

| Name                              | Description                                                                           |
| ---                               | ---                                                                                   |
| [`bold`](bold.md)                 | Enables increased intensity when `enable` is true, or clears the attribute otherwise. |
| [`is_bold`](is_bold.md)           | Returns true if increased intensity is enabled.                                       |
| [`faint`](faint.md)               | Enables decreased intensity when `enable` is true, or clears the attribute otherwise. |
| [`is_faint`](is_faint.md)         | Returns true if decreased intensity is enabled.                                       |
| [`italic`](italic.md)             | Enables italics when `enable` is true, or clears the attribute otherwise.             |
| [`is_italic`](is_italic.md)       | Returns true if italics is enabled.                                                   |
| [`underline`](underline.md)       | Enables underlining when `enable` is true, or clears the attribute otherwise.         |
| [`is_underline`](is_underline.md) | Returns true if underlining is enabled.                                               |
| [`blink`](blink.md)               | Enables blinking when `enable` is true, or clears the attribute otherwise.            |
| [`is_blink`](is_blink.md)         | Returns true if blinking is enabled.                                                  |
| [`reverse`](reverse.md)           | Enables reverse video when `enable` is true, or clears the attribute otherwise.       |
| [`is_reverse`](is_reverse.md)     | Returns true if reverse video is enabled.                                             |
| [`conceal`](conceal.md)           | Enables concealment when `enable` is true, or clears the attribute otherwise.         |
| [`is_conceal`](is_conceal.md)     | Returns true if concealment is enabled.                                               |
| [`strike`](strike.md)             | Enables strike-through when `enable` is true, or clears the attribute otherwise.      |
| [`is_strike`](is_strike.md)       | Returns true if strike-through is enabled.                                            |

### Comparisons

| Name                                              | Description                                                                           |
| ---                                               | ---                                                                                   |
| [`operator==`](operator-equal.md)                 | Compares the stored foreground, background, emphasis, and absolute flag for equality. |
| [`operator<=>`](operator-three-way-comparison.md) | Compares the stored style components in their declaration order.                      |

## Non-member functions

| Name                             | Description                                                                 |
| ---                              | ---                                                                         |
| [`absolute`](../absolute.md)     | Returns a copy of a style with its absolute flag set.                        |
| [`fg`](../fg.md)                 | Returns a style with the supplied foreground color.                         |
| [`bg`](../bg.md)                 | Returns a style with the supplied background color.                         |
| [`bold`](../bold.md)             | Returns a style with increased intensity enabled or disabled.               |
| [`faint`](../faint.md)           | Returns a style with decreased intensity enabled or disabled.               |
| [`italic`](../italic.md)         | Returns a style with italic text enabled or disabled.                       |
| [`underline`](../underline.md)   | Returns a style with underlining enabled or disabled.                       |
| [`blink`](../blink.md)           | Returns a style with blinking enabled or disabled.                          |
| [`reverse`](../reverse.md)       | Returns a style with reversed foreground and background enabled or disabled. |
| [`conceal`](../conceal.md)       | Returns a style with concealment enabled or disabled.                       |
| [`strike`](../strike.md)         | Returns a style with crossed-out text enabled or disabled.                  |
| [`blend`](../blend.md)           | Averages foreground and background colors and combines emphasis attributes. |

## Helper classes

| Name                                        | Description                                   |
| ---                                         | ---                                           |
| [`std::hash<text_style>`](../hash/index.md) | Hash support for use in unordered containers. |
