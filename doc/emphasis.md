# Emphasis

Use emphasis values as styles or combine them with colors through
[`text_style`](text-style.md).

## Attributes

`tjg::color::emphasis::none` is the zero mask. It specifies no attributes.
`tjg::color::emphasis::strike` selects crossed-out text (SGR 9).

::: emphasis
    options:
      color_reference: true
      enum_value_placeholder: unspecified value

## Combining attributes

::: operator|(emphasis, emphasis)
    options:
      color_reference: true

The result is an `emphasis` value containing both sets of attribute bits.
An `emphasis` value converts implicitly to `text_style`.

```cpp
using namespace tjg::color;
auto style = emphasis::bold | emphasis::underline;
println(style, "Important: {}", 42);
```

```cpp
text_style style = emphasis::bold | emphasis::underline;
if (style.has_emph())
  println(style, "Important");
```

Bold and faint remain independent bits: combining them preserves both and
emits both SGR attributes. Their combined appearance depends on the terminal.

## Integer representation

The underlying representation of `tjg::color::emphasis` is `uint8_t`.

```cpp
using namespace tjg::color;
using emphasis_t = std::underlying_type_t<emphasis>;
constexpr auto bold_bit = std::to_underlying(emphasis::bold); // 1
constexpr auto attributes = emphasis::bold | emphasis::faint;
constexpr auto bits = std::to_underlying(attributes);         // 3
static_assert(std::is_same_v<const emphasis_t, decltype(bits)>);
static_assert(bold_bit == 1);
static_assert(bits     == 3);
```
