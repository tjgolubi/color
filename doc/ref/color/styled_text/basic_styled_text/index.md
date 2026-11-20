# `tjg::color::basic_styled_text`

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

Owns text together with its style. Concatenation preserves the styles of the original pieces. A relative group inherits unspecified components from its enclosing style. An absolute group starts from terminal defaults. See [`styled_text`](../styled_text.md) and [`wstyled_text`](../wstyled_text.md) for the narrow and wide aliases.

## Text inputs

Construct with a `string_type` or a non-null pointer to a null-terminated string. Use a `string_type` to preserve embedded nulls. The free styled-text helpers accept these inputs and matching `basic_styled_text` values. They copy styled lvalues and can move styled rvalues. The result owns its text.

## Member operations

| Members | Behavior |
| --- | --- |
| `style()`, `style(value)` | Read or replace the outermost style. |
| `overlay(overrides)` | Replace specified colors and combine emphasis throughout relative groups, skipping absolute groups and their contents. |
| `underlay(style)` | Supply defaults and emphasis to the outermost style. |
| `empty()` | Report whether the value contains any text. |
| `plain_text()` | Return a string with all text in order, preserving embedded nulls and escapes. |
| `operator+`, `operator+=` | Concatenate. Empty values act as identities. |
| `operator==`, `operator!=` | Compare text, styles, and grouping. |

The style mutators and `operator+=` return `*this`. Construction from text, copying, concatenation, and `plain_text()` can allocate. For rendering, include [`<tjg/color.hpp>`](../../index.md). See the [structured text guide](../../../../styled.md#structured-styled-text).

## Member functions

- [`basic_styled_text`](constructor.md)
- [`operator=`](operator-assignment.md)
- [`style`](style.md)
- [`overlay`](overlay.md)
- [`underlay`](underlay.md)
- [`empty`](empty.md)
- [`plain_text`](plain_text.md)
- [`operator+=`](operator-addition-assignment.md)

## Non-member functions

- [`operator==`](operator-equal.md)
- [`operator!=`](operator-not-equal.md)
- [`operator+`](operator-addition.md)
