# `tjg::color::text_style`

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

Stores optional foreground and background [`color_t`](../../colors/color_t.md) values, [`emphasis`](../emphasis.md), and an absolute flag. Default construction makes an empty relative style. An absolute-only style is nonempty. `clear()` restores the default and returns `*this`.

## Member operations

| Members | Behavior |
| --- | --- |
| `fg()`, `bg()`, `emph()` | Return component values by value. |
| `fg(color)`, `bg(color)`, `emph(em)` | Replace the component and return `*this`. Use `no_color` to clear a color. |
| `has_fg()`, `has_bg()`, `has_emph()` | Check which components are specified. |
| `set(em, enable)`, named attribute setters | Enable or disable the requested bits. |
| `is_enabled(em)`, named attribute queries | Test for any matching bit. |
| `absolute(enable)`, `is_absolute()` | Set or query whether output starts from terminal defaults. |
| `overlay(other)` | Replace matching colors with specified colors from `other`. |
| `underlay(other)` | Fill unspecified channels with colors from `other`. |

Both composition members union emphasis and absolute flags and return `*this`. Equality, ordering, and [`std::hash<text_style>`](../hash/index.md) include the stored colors, emphasis, and absolute flag. See the [text styles guide](../../../../text-style.md) and [stream insertion](../../operator-insertion.md).

## Member functions

- [`text_style`](constructor.md)
- [`operator=`](operator-assignment.md)
- [`empty`](empty.md)
- [`clear`](clear.md)
- [`absolute`](absolute.md)
- [`is_absolute`](is_absolute.md)
- [`overlay`](overlay.md)
- [`underlay`](underlay.md)
- [`has_fg`](has_fg.md)
- [`has_bg`](has_bg.md)
- [`has_emph`](has_emph.md)
- [`fg`](fg.md)
- [`bg`](bg.md)
- [`emph`](emph.md)
- [`set`](set.md)
- [`is_enabled`](is_enabled.md)
- [`bold`](bold.md)
- [`is_bold`](is_bold.md)
- [`faint`](faint.md)
- [`is_faint`](is_faint.md)
- [`italic`](italic.md)
- [`is_italic`](is_italic.md)
- [`underline`](underline.md)
- [`is_underline`](is_underline.md)
- [`blink`](blink.md)
- [`is_blink`](is_blink.md)
- [`reverse`](reverse.md)
- [`is_reverse`](is_reverse.md)
- [`conceal`](conceal.md)
- [`is_conceal`](is_conceal.md)
- [`strike`](strike.md)
- [`is_strike`](is_strike.md)
- [`operator==`](operator-equal.md)
- [`operator<=>`](operator-three-way-comparison.md)
