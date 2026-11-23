# [`tjg::color::tagged`](https://github.com/tjgolubi/color/blob/f2cba0d4d2db3645637b95055efbf9741330282c/include/tjg/color/styled_text.hpp#L166)

Header: [`<tjg/color/styled_text.hpp>`](index.md), also available through
[`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
[[nodiscard]]
auto tagged(std::string_view text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> styled_text;

[[nodiscard]]
auto tagged(std::wstring_view text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> wstyled_text;

template<CharType Char>
[[nodiscard]] auto tagged(std::basic_string_view<Char> text)
    TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> basic_styled_text<Char>;
```

## Description

Parses inline markup into styled text. The narrow and wide overloads use
the same grammar. The template also lets you specify `char` or `wchar_t`
explicitly.

### Style tags

Tag names are lowercase and case-sensitive. Tags can nest. Each relative
tag inherits unspecified colors and combines its emphasis with the enclosing
style. Closing a tag restores the enclosing style.

| Markup                              | Effect                            |
| ----------------------------------- | --------------------------------- |
| `<bold white on dark_blue>text</>`  | Sets both colors and adds bold.   |
| `<color=cyan>text</color>`          | Sets the foreground.              |
| `<on dark_blue>text</>`             | Sets the background.              |
| `<b>text</b>`                       | Adds bold.                        |
| `<emphasis=bold, underline>text</>` | Combines emphasis attributes.     |
| `<absolute blue>text</>`            | Sets blue on a fresh style scope. |

Color tags accept [named RGB colors](../colors/rgb/rgb-constants.md),
`#RRGGBB` in either hex case, and `term_` names such as `term_red`.
The `term_` names use [terminal palette slots](../colors/term_color.md).
Fixed Xterm RGB names use `xterm_`, as in `xterm_red`. Close shorthand color
tags with `</>`. Explicit `<color=…>` tags accept `</color>` or `</>`.

Use the names in [`emphasis`](../text_style/emphasis.md) as standalone tags
or in an `<emphasis=…>` list separated by `,` or `|`. The short tags `<b>`,
`<i>`, `<u>`, and `<s>` mean bold, italic, underline, and strike.
`<absolute>text</absolute>` starts from terminal defaults. The `absolute`
keyword can also appear alongside colors or emphasis.

### Shorthand and literal text

Use `*italic*`, `**bold**`, `_underline_`, or `~~strike~~` on one line.
These spans can contain nested tags. A Unicode letter, number, or combining
mark immediately outside a delimiter pair prevents it from matching. Runs
of three or more asterisks are literal. `<br>` inserts a newline.

Backticks delimit literal text. Outside those spans, a backslash can escape
a markup delimiter or another backslash. `\u` with four hex digits and
`\U` with eight hex digits insert Unicode scalar values. `\ ` inserts a
no-break space, and `\-` inserts a soft hyphen.

Unrecognized tags and malformed markup stay visible. The parser continues
processing valid markup inside unknown tags and treats structurally valid
unknown tags as scopes for matching closing tags. A mismatched closing tag
stays visible and leaves the active style unchanged. Unrecognized escapes
and invalid Unicode escapes are preserved.

## Return value

Styled text containing the parsed text and styles. The result remains valid
after the input string is changed or destroyed.

## Example

```cpp
#include <tjg/color.hpp>

int main() {
  using namespace tjg::color;
  tjg::color::println(stdout, "{}", tagged("<cyan>Build **passed**.</>"));
}
```

The sentence is cyan, and “passed” is also bold.

## See also

- [Styling prose with tags](../../../styled.md#styling-prose-with-tags)
- [Tagged demo](../../../tagged-demo.md)
- [`word_wrap`](word_wrap.md) and [`wrapped`](../wrapped.md)
