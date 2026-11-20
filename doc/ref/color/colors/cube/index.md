# `tjg::color::cube`

Header: [`<tjg/color/colors.hpp>`](../index.md).

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

## Description

Selects a color in the indexed 6×6×6 cube. Channel indices are in `0..5`. The combined index is `36 * r + 6 * g + b` in `0..215`. Equality and ordering follow the combined index. [`std::hash<cube>`](../hash/index.md) is provided.

The setters replace one channel and return `*this`. Setters assert on invalid inputs in assertion-enabled builds. The current implementation clamps when assertions are disabled.

Output selects palette entry `16 + index()` using [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) `38;5;n` or `48;5;n`. Conversion to [`rgb`](../rgb/index.md) maps each channel to the corresponding level in `{0, 95, 135, 175, 215, 255}`. See the [cube palette](../../../../named-colors.md#cube-palette-colors).

See [Xterm-default palette behavior](../xterm-palette.md).

## Member functions

| Name                                              | Description                                                              |
| ---                                               | ---                                                                      |
| [`cube`](constructor.md)                          | Constructs the value; see the constructor overloads.                     |
| [`operator=`](operator-assignment.md)             | Copies all three channel indices from the source and returns `*this`.    |
| [`index`](palette-index.md)                       | Returns the zero-based cube palette index without modifying the color.   |
| [`r`](r.md)                                       | Reads or changes the red channel index.                                  |
| [`g`](g.md)                                       | Reads or changes the green channel index.                                |
| [`b`](b.md)                                       | Reads or changes the blue channel index.                                 |
| [`operator rgb`](operator-rgb.md)                 | Converts implicitly to `rgb`.                                            |
| [`operator<=>`](operator-three-way-comparison.md) | Compares the combined cube indices and returns a `std::strong_ordering`. |
| [`operator==`](operator-equal.md)                 | Compares the three channel indices for equality.                         |

## Helper classes

| Name                                  | Description                                   |
| ---                                   | ---                                           |
| [`std::hash<cube>`](../hash/index.md) | Hash support for use in unordered containers. |
