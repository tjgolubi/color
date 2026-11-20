# [`tjg::color::basic_styled_text`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L31)

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
template<CharType Char>
class basic_styled_text {
public:
  using char_type = Char;
  using string_type = std::basic_string<Char>;
  using view_type = std::basic_string_view<Char>;

  basic_styled_text();
  basic_styled_text(string_type text, const text_style& style = {});
  basic_styled_text(const Char* text, const text_style& style = {});
  basic_styled_text(const basic_styled_text& other);
  basic_styled_text(basic_styled_text&& other) noexcept;
  auto operator=(const basic_styled_text& other) -> basic_styled_text&;
  auto operator=(basic_styled_text&& other) noexcept -> basic_styled_text&;

  auto style() const noexcept -> text_style;
  auto style(text_style value) noexcept -> basic_styled_text&;
  auto overlay(text_style overrides) noexcept -> basic_styled_text&;
  auto underlay(text_style style) noexcept -> basic_styled_text&;
  auto empty() const noexcept -> bool;
  auto plain_text() const -> string_type;
  auto operator+=(basic_styled_text rhs) -> basic_styled_text&;

  friend bool operator==(const basic_styled_text&, const basic_styled_text&);
  friend bool operator!=(const basic_styled_text&, const basic_styled_text&);
  friend auto operator+(basic_styled_text lhs, basic_styled_text rhs)
    -> basic_styled_text;
};
```

## Description

Owns text together with its style. Concatenation preserves the styles of the original pieces. A relative group inherits unspecified components from its enclosing style. An absolute group starts from terminal defaults. See [`styled_text`](../styled_text.md) and [`wstyled_text`](../wstyled_text.md) for the narrow and wide aliases.

<span id="text-inputs"></span>

The free styled-text helpers accept matching text inputs and styled-text values.
They copy styled lvalues and can move styled rvalues. The result owns its text.
See the [constructor page](constructor.md) for accepted constructor inputs.

The style mutators and `operator+=` return `*this`. For rendering, include [`<tjg/color.hpp>`](../../index.md). See the [structured text guide](../../../../styled.md#structured-styled-text).

## Type definitions

| Name                                 | Description                   |
| ---                                  | ---                           |
| [`styled_text`](../styled_text.md)   | `basic_styled_text<char>`.    |
| [`wstyled_text`](../wstyled_text.md) | `basic_styled_text<wchar_t>`. |

## Template parameters

| Parameter | Description                                                               |
| ---       | ---                                                                       |
| `Char`    | Stored character type satisfying [`CharType`](../../../util/CharType.md). |

## Nested types

| Name          | Definition                      |
| ---           | ---                             |
| `char_type`   | `Char`.                         |
| `string_type` | `std::basic_string<Char>`.      |
| `view_type`   | `std::basic_string_view<Char>`. |

## Member functions

| Name                                            | Description                                                                         |
| ---                                             | ---                                                                                 |
| [`basic_styled_text`](constructor.md)           | Constructs the value; see the constructor overloads.                                |
| [`operator=`](operator-assignment.md)           | Replaces the value by copying or moving from the source.                            |
| [`style`](style.md)                             | Reads or replaces the outermost style.                                              |
| [`overlay`](overlay.md)                         | Applies specified colors and combines emphasis throughout the styled text in place. |
| [`underlay`](underlay.md)                       | Applies the supplied style as defaults for the outermost group in place.            |
| [`empty`](empty.md)                             | Returns true if the value contains no text.                                         |
| [`plain_text`](plain_text.md)                   | Returns an independent string containing the text in order.                         |
| [`operator+=`](operator-addition-assignment.md) | Appends `rhs`, preserving the styles of the original pieces, and returns `*this`.   |

## Non-member functions

| Name                                        | Description                                                             |
| ---                                         | ---                                                                     |
| [`operator==`](operator-equal.md)           | Returns true when text, styles, and grouping match.                     |
| [`operator!=`](operator-not-equal.md)       | Returns the negation of `operator==`.                                   |
| [`operator+`](operator-addition.md)         | Returns the concatenated value, preserving the styles of both operands. |
| [`overlay`](../overlay.md)                  | Applies specified colors and emphasis throughout relative groups.       |
| [`underlay`](../underlay.md)                | Supplies defaults for the outermost group.                              |
| [`absolute`](../absolute.md)                | Makes the outermost style absolute.                                     |
| [`bold`](../bold.md)                        | Applies increased intensity.                                            |
| [`faint`](../faint.md)                      | Applies decreased intensity.                                            |
| [`italic`](../italic.md)                    | Applies italic text.                                                    |
| [`underline`](../underline.md)              | Applies underlining.                                                    |
| [`blink`](../blink.md)                      | Applies blinking.                                                       |
| [`reverse`](../reverse.md)                  | Reverses foreground and background.                                     |
| [`conceal`](../conceal.md)                  | Applies concealment.                                                    |
| [`strike`](../strike.md)                    | Applies crossed-out text.                                               |
| [`strip_ansi`](../../sgr/strip_ansi.md)     | Removes escape sequences while preserving styles and grouping.          |
| [`operator<<`](../../operator-insertion.md) | Writes styled text to an output stream.                                 |

## Example

The combined text is green, and "passed" is also bold.

```cpp
#include <tjg/color.hpp>

int main() {
  using namespace tjg::color;
  using enum term_color;

  auto message = underlay(fg(green),
    styled_text{"Build "} + bold(styled_text{"passed"}));
  println(text_style{}, "{}", message);
}
```
