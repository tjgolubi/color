# `tjg::color::gray`

Header: [`<tjg/color/colors.hpp>`](../index.md).

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

## Description

Selects one of the 24 indexed gray levels. The zero-based index is in `0..23`, and determines equality and ordering. Output selects palette entry `232 + index` using [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) `38;5;n` for foreground or `48;5;n` for background. Conversion to [`rgb`](../rgb/index.md) sets each channel to `8 + 10 * index`. [`std::hash<gray>`](../hash/index.md) is provided.

See the [gray swatches](../../../../named-colors.md#gray-palette-colors).

See [Xterm-default palette behavior](../xterm-palette.md).

## Member functions

| Name                                              | Description                                                            |
| ---                                               | ---                                                                    |
| [`gray`](constructor.md)                          | Constructs the value; see the constructor overloads.                   |
| [`operator=`](operator-assignment.md)             | Copies the gray index from the source and returns `*this`.             |
| [`index`](palette-index.md)                       | Returns the zero-based gray palette index without modifying the color. |
| [`operator rgb`](operator-rgb.md)                 | Converts implicitly to `rgb`.                                          |
| [`operator<=>`](operator-three-way-comparison.md) | Compares the gray indices and returns a `std::strong_ordering`.        |
| [`operator==`](operator-equal.md)                 | Compares the gray index for equality.                                  |

## Helper classes

| Name                                  | Description                                   |
| ---                                   | ---                                           |
| [`std::hash<gray>`](../hash/index.md) | Hash support for use in unordered containers. |
