# `tjg::color::gray`

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
class gray {
public:
  constexpr gray() noexcept;
  constexpr explicit gray(int index) noexcept;
  constexpr gray(const gray&) noexcept;
  constexpr gray& operator=(const gray&) noexcept;
  constexpr auto index() const noexcept -> int;
  constexpr operator rgb() const noexcept;
  constexpr auto operator<=>(const gray&) const noexcept -> std::strong_ordering;
};
```

Selects one of the 24 indexed gray levels. The zero-based index is in `0..23`, defaults to zero, and determines equality and ordering. Output selects palette entry `232 + index` using SGR `38;5;n` for foreground or `48;5;n` for background. Conversion to [`rgb`](rgb.md) sets each channel to `8 + 10 * index`. `std::hash<gray>` is provided.

The constructor asserts on invalid indices in assertion-enabled builds. The current implementation clamps when assertions are disabled. See the [gray swatches](../../../named-colors.md#gray-palette-colors).
