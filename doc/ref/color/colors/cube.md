# `tjg::color::cube`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
class cube {
public:
  constexpr cube() noexcept;
  constexpr explicit cube(int index) noexcept;
  constexpr cube(int r, int g, int b) noexcept;
  constexpr cube(const cube&) noexcept;
  constexpr cube& operator=(const cube&) noexcept;
  constexpr auto index() const noexcept -> int;
  constexpr auto r() const noexcept -> int;
  constexpr auto g() const noexcept -> int;
  constexpr auto b() const noexcept -> int;
  constexpr auto r(int value) noexcept -> cube&;
  constexpr auto g(int value) noexcept -> cube&;
  constexpr auto b(int value) noexcept -> cube&;
  constexpr operator rgb() const noexcept;
  constexpr auto operator<=>(const cube&) const noexcept -> std::strong_ordering;
};
```

Selects a color in the indexed 6×6×6 cube. Channel indices are in `0..5`. The combined index is `36 * r + 6 * g + b` in `0..215`. Default construction selects zero. Equality and ordering follow the combined index. `std::hash<cube>` is provided.

The setters replace one channel and return `*this`. Construction and setters assert on invalid inputs in assertion-enabled builds. The current implementation clamps when assertions are disabled.

Output selects palette entry `16 + index()` using SGR `38;5;n` or `48;5;n`. Conversion to [`rgb`](rgb.md) maps each channel to the corresponding level in `{0, 95, 135, 175, 215, 255}`. See the [cube palette](../../../named-colors.md#cube-palette-colors).
