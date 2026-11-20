# [`tjg::color::no_color_t`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L31)

Header: [`<tjg/color/colors.hpp>`](../index.md).

## Synopsis

```cpp
struct no_color_t {
  constexpr auto operator<=>(const no_color_t&) const noexcept = default;
};
```

## Description

Represents an unspecified color channel. See the [`no_color`](../no_color.md) constant and the [`color_t`](../color_t.md) variant.

## Member functions

| Name                                              | Description                                                                          |
| ---                                               | ---                                                                                  |
| [`no_color_t`](constructor.md)                    | Constructs the value; see the constructor overloads.                                 |
| [`operator=`](operator-assignment.md)             | Assignment replaces the unspecified-color value from the source and returns `*this`. |
| [`operator<=>`](operator-three-way-comparison.md) | Compares two unspecified colors.                                                     |
| [`operator==`](operator-equal.md)                 | Compares the unspecified-color values for equality.                                  |

## Non-member functions

| Name                   | Description                                                |
| ---                    | ---                                                        |
| [`blend`](../blend.md) | Blends specified colors while ignoring unspecified inputs. |
