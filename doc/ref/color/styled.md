# `tjg::color::styled`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
// Returns an object of unspecified type.
template<typename T>
constexpr auto styled(const T& value, text_style style);
```

## Description

Applies the specified text style to a value when it is formatted or written to a
stream. After the value is written, the surrounding style is restored.

## Parameters

| Parameter | Description                          |
| ---       | ---                                  |
| `value`   | Value to which the style is applied. |
| `style`   | Text style to apply.                 |

## Return value

Returns an object of unspecified type such that the described behavior takes place.

## Notes

The value is borrowed and must remain alive until formatting or stream insertion
completes. The result stores a copy of `style`.

## Example

```cpp
using namespace tjg::color;
using enum term_color;
std::println("The result is {} bytes.", styled(42, fg(red)));
```
