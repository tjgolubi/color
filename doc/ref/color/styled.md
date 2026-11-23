# [`tjg::color::styled`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/bits/text_style-format.hpp#L527)

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
// Returns an object of unspecified type.
template<typename T>
constexpr auto styled(const T& value, const text_style& style);
```

## Description

Applies the specified text style when formatting a value. Formatting restores
the enclosing style afterward. Stream insertion applies the style and then
resets to terminal defaults when styling is enabled. See
[Terminal detection](print.md#terminal-detection) for printing and insertion.

## Parameters

| Parameter | Description                          |
| ---       | ---                                  |
| `value`   | Value to which the style is applied. |
| `style`   | Text style to apply.                 |

## Return value

Returns an object of unspecified type such that the described behavior takes place.

## Notes

The result borrows both `value` and `style`. Keep both alive until formatting
or stream insertion completes. Temporaries are valid within an immediate call.

## Example

```cpp
using namespace tjg::color;
using enum term_color;
tjg::color::println(stdout, "The result is {} bytes.", styled(42, fg(red)));
```
