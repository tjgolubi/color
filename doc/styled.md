# Styled Arguments

## Structured styled text

Use `styled_text` to concatenate text with independently styled parts and
arrange it into nested groups. Grouping works like parentheses: a style applied
to a group provides the surrounding style for its contents. Include
`<tjg/color/styled_text.hpp>` to create and combine text that keeps its own
contents. Include `<tjg/color.hpp>` to use it with `std::format`,
`std::format_to`, or `std::println`. Use `{:?}` to inspect the text and its
groups.

Styled text keeps its own text, so the original strings need not remain alive.
Copies can be styled and regrouped independently; their unchanged text is
shared. Moves leave the source empty and unstyled.

### Concatenation preserves each part's style

Both `+` and `+=` concatenate complete styled spans. `+` returns a new value;
`+=` appends to the value on its left. Neither operation extends an existing
span's style over the text added after it, even if that span contains several
styled parts.

```cpp
using namespace tjg::color;
auto red_text = underlay(fg(rgb::red),
    "red text with " + bold("nested bold") + " still red");
auto line = styled_text{"plain | "} + red_text + " | plain again";
std::println("{}", line);
```

Expected output (followed by a newline):

<pre class="color-output">plain | <span style="color: #FF0000">red text with <strong>nested bold</strong> still red</span> | plain again</pre>

Only the middle phrase is red, and only `nested bold` is also bold. The prefix
and suffix use terminal defaults. The same boundary is preserved when appending
in place:

```cpp
auto extended = red_text;
extended += " | plain again";
```

The appended text is outside the red span. A plain string has no style of its
own; it inherits a surrounding group style only when you apply one to the
combined text. Empty text adds nothing.

### Use `underlay` to supply group defaults

Concatenate the parts first, then use `underlay(style, text)` to supply
defaults for the combined text. Existing foreground and background colors are
preserved. The supplied colors fill unspecified channels in the outermost
style. During formatting, each relative part inherits colors it does not
specify; explicit colors within the group take precedence. Emphasis attributes
are combined.

```cpp
using namespace tjg::color;
auto words =       styled_text{"red",   fg(rgb::red)}
           + " " + styled_text{"green", fg(rgb::green)}
           + " " + styled_text{"blue",  fg(rgb::blue)};
auto defaults = fg(rgb::black).bg(rgb::light_gray);
auto group = underlay(defaults, words);
std::println("{}", group);
```

Expected output (followed by a newline):

<pre class="color-output"><span style="color: #000000; background-color: #C0C0C0"><span style="color: #FF0000">red</span> <span style="color: #008000">green</span> <span style="color: #0000FF">blue</span></span></pre>

Each word keeps its foreground color. The spaces use the black default
foreground, and the light-gray background covers the whole group.

The free function returns an independent styled-text value; named inputs are
copied and rvalues can be moved. The member updates the value in place:

```cpp
words.underlay(defaults);
```

Underlay modifies only the outermost style. Formatting carries those defaults
to relative text and nested groups without changing their stored styles. An
absolute group starts from terminal initial conditions instead of inheriting
outer defaults.

### Use `overlay` for explicit overrides

`overlay(overrides, text)` replaces the specified colors throughout the text
and its nested groups, combining emphasis attributes. It skips existing absolute
groups and everything inside them. Use it when the supplied colors should
replace explicit choices:

```cpp
using namespace tjg::color;
auto all_red = overlay(fg(rgb::red), words);
std::println("{}", all_red);
```

Expected output (followed by a newline):

<pre class="color-output"><span style="color: #FF0000; background-color: #C0C0C0">red green blue</span></pre>

Here `words` has the defaults added by the preceding member call. All relative
parts become red, and the gray background remains. `words` itself is unchanged.
The member `words.overlay(overrides)` applies the same overrides throughout the
group in place. Unlike `underlay`, overlay changes styles stored within nested
groups. Neither operation changes how formatting combines enclosing and inner
styles.

To overlay only the outermost style, use the style getter and setter:

```cpp
words.style(words.style().overlay(fg(rgb::red)));
```

That changes the outermost foreground; the words' explicit foregrounds still
take precedence during formatting. Appending text with `+` or `+=` adds a
separate span. Concatenate before underlaying defaults or applying overrides if
the new text should be included.

### Absolute spans ignore the surrounding style

Use `absolute(text)` to make a span independent of its enclosing style. It
preserves the span's colors, emphasis, and nested groups, and makes the span as
a whole absolute. Like `overlay`, it returns an independent styled-text value:
named inputs are copied and temporaries can be moved. Narrow and wide strings
are also accepted. For a style value, `absolute(style)` returns an absolute
copy of that style.

An absolute style describes the complete appearance of its span. Missing
foreground and background colors mean terminal defaults, and absent emphasis
means off. Text and nested groups inside an absolute group can inherit from
that group as usual. Overlays applied from outside also skip the absolute group
and everything inside it. After the absolute span, the surrounding appearance
resumes.

On entry to an absolute group, the formatter emits an SGR reset and applies the
group's style before formatting its contents. This can emit SGR even when the
remaining precision clips all of the group's text. An absolute text span with
no nested groups resets when it writes text or padding. These resets occur even
when the terminal already has the same attributes. Relative text and nested
groups inherit the group's style, and an absolute group nested within it
establishes its own reset boundary.

```cpp
using namespace tjg::color;
auto underline_only = absolute(underline("underline only"));
auto sentence = styled_text{"before "} + underline_only + " after";
auto decorated = strike(underlay(bg(rgb::gray), sentence));
std::println("{}", decorated);
```

Expected output (followed by a newline):

<pre class="color-output"><span style="background-color: #808080; text-decoration: line-through">before </span><span style="text-decoration: underline">underline only</span><span style="background-color: #808080; text-decoration: line-through"> after</span></pre>

`before ` and ` after` have a gray background and strikethrough. The absolute
span is underlined, without strikethrough or the gray background. The text after
it resumes both surrounding properties.

The [StyledTextDemo walkthrough](styled-text-demo.md) compares `underlay()`
and `overlay()` on the same line, including an absolute span.

### Formatting and plain text

Formatting leaves the value unchanged. Relative styled text inherits the
enclosing shared terminal state's colors and emphasis. After the complete
replacement field, the enclosing style is restored. The shared state initially
assumes terminal defaults. See the [shared-state rules](index.md) for
single-threaded use and nested formatting calls.

The formatter tracks the last style emitted to the terminal separately from the
enclosing group style. Relative groups emit no SGR on entry or exit.
Immediately before writing a text span or its padding, it emits the transition
from the recorded terminal state to the required style. Successive text spans
therefore transition directly without first restoring intermediate group
styles. At field completion, it restores the enclosing shared style from the
last emitted state.

```cpp
using namespace tjg::color;
print(underline(), "The result is {} after rounding.",
                    styled_text{"42", fg(term_color::bright_red)});
```

Expected output (without a trailing newline):

<pre class="color-output"><span style="text-decoration: underline">The result is <span style="color: #FF0000">42</span> after rounding.</span></pre>

The whole sentence is underlined, and `42` is also bright red. An absolute
group temporarily replaces the enclosing style, then restores it on completion.

Styled text accepts ordinary string fill, alignment (`<`, `>`, `^`), width, and
precision, with optional `s` presentation. Width and precision may also be
dynamic arguments. To inspect the text and its groups, use the separate `?`
presentation described below.

```cpp
using namespace tjg::color;
std::println("{:*>13.9}", bold("hello " + styled_text{"world", fg(rgb::blue)}));
// Four '*' characters followed by "hello wor", all bold; "wor" is blue.
```

Expected output (followed by a newline):

<pre class="color-output"><span style="font-weight: bold">&#42;&#42;&#42;&#42;hello <span style="color: #0000FF">wor</span></span></pre>

One precision limit applies across the complete styled text. If the next
character does not fit, formatting stops adding text. Width sets a minimum for
the displayed field after truncation. Padding uses the outermost style,
including for empty text or precision zero. Styles within the group apply to
their own text. After any right padding, the formatter restores the enclosing
shared style directly from the last emitted style.

Use `plain_text` when you need an independent string containing just the stored
text, without applying the styles:

```cpp
auto plain = line.plain_text();
// "plain | red text with nested bold still red | plain again"
```

Stored text is copied as supplied, including braces, embedded nulls, and raw
terminal escapes. Raw escapes are not interpreted or removed and can interfere
with the expected appearance. Express styling through the API when composing
styled text. Terminal support and themes can affect the displayed appearance.

For wide text, use `wstyled_text` and a wide format string. The same composition
and grouping rules apply.

### Measuring text width

The formatter estimates display width for narrow text from UTF-8 code points
using tables generated from Unicode 18.0.0. For example, `Café` occupies four
columns and `界` occupies two. Each malformed UTF-8 byte counts as one column.
Wide text uses code-unit counts. With 16-bit `wchar_t`, truncation keeps
surrogate pairs together within a text span.

Each concatenated text span is measured independently, so keep each encoded
character within a single span. Generated SGR sequences take no columns. Raw
escape sequences stored in text spans are measured as text.

### Wrapping text into lines

Use `word_wrap(text, width)` to split styled text into display lines. Styles
and nested groups stay with their text, and the original value is unchanged.
Pass a `std::size_t` width of at least 4 columns. The returned lines have no
padding, so your table or output code chooses how to align them.

Pass a third argument to reserve a hanging indent. `word_wrap(text, 40, 2)`
uses all 40 columns on the first line and adds two leading spaces to each
subsequent nonblank line. Those lines have 38 columns for text, including
after explicit newlines. The remaining width must be at least four columns.

```cpp
using namespace tjg::color;
auto message = bold(styled_text{"Build completed; "}
                  + styled_text{"all checks passed", fg(term_color::green)});
for (const auto& line : word_wrap(message, 20))
  std::println("{}", line);
// Build completed; all
// checks passed
```

Words that fit the column move intact to the next line. To mark a preferred
break in a longer word, insert a soft hyphen (`U+00AD`). It becomes a visible
hyphen only when used as a break. Breaks between adjacent ideographic
characters in an oversized run add no hyphen. Other oversized words can split
with a hyphen that inherits the preceding character's style.

Breaks can also follow punctuation, except opening punctuation and quotation
marks, including apostrophes. Punctuation stays on the preceding line.

Newlines force line breaks. A no-break space (`U+00A0`) takes one column and
keeps adjacent text together if it fits on a full line. In an oversized group,
wrapping can break at a no-break space when no preferred break fits. That
space is consumed and no hyphen is added.

Other Unicode whitespace becomes ordinary spaces, one space per character.
Leading and interior spaces are preserved, except
separating spaces at automatic wrap boundaries. Trailing spaces and trailing
blank lines are removed. Empty or whitespace-only input returns no lines.
Raw ANSI sequences are stripped independently from each text span; remaining
non-whitespace C0/C1 controls are discarded.

Both `styled_text` and `wstyled_text` use the narrow formatter's estimated
one/two-column Unicode width model for wrapping. Wide wrapping decodes UTF-16
or UTF-32 according to `wchar_t` size. Keep each encoded character within one
text span. Malformed code units are preserved and each counts as one column.
Combining marks and emoji sequences do not receive grapheme-cluster handling.
See the [`word_wrap` reference](ref/color/styled_text/word_wrap.md) for the
complete rules, including blank lines and invalid widths.

The [WrapTable walkthrough](wrap-table.md) shows how to use these lines in
your own table, with styled cells, column alignment, and Unicode borders.

Use [`wrapped()`](ref/color/wrapped.md) to write the lines as one argument.
The format field sets the wrap width. Use `{}` for 80 display columns or pass
a dynamic field width. Format precision sets the hanging indent. Use `<`,
`^`, or `>` to align each line within the area available for text after any
indent. In a stream, set the width with `std::setw()`.

```cpp
std::print("{:{}}", wrapped(message), column_width);
std::cout << std::setw(20) << wrapped(message);
```

```cpp
auto item = styled_text{"- Build finished with warnings."};
std::println("{:20.2}", wrapped(item));
// - Build finished
//   with warnings.
```

`wrapped()` writes newlines between the lines. Use `std::println()` or insert
`'\n'` yourself when you want a final newline.

### Debug output

Use `{:?}` to inspect stored styles and nested groups without rendering SGR.
Each text span or group shows its [readable
style](text-style.md#readable-style-output), a space, then either its quoted
debug string or an opening `{` and newline. An empty style and its following
space are omitted. Contents of a group are indented two spaces per level; each
closing `}` aligns with the group's style. Text strings use the library's debug
escaping, including quotes, backslashes, embedded nulls, and control
characters.

```cpp
using namespace tjg::color;
auto text = bold(styled_text{"hello\n", fg(term_color::red)}
                      + (underline("world") + "!"));
std::print("{:?}", text);
```

Output:

```text
b {
  red "hello\n"
  {
    _ "world"
    "!"
  }
}
```

Every text span inside a group and every closing brace ends with a newline. A
single text span outside any group has no trailing newline: an empty unstyled
span displays `""`, and a bold span displays `b "hello"`. No additional outer
enclosure is added. Debug output shows the styles stored on text spans and
groups, without resolving inheritance or modifying the styled text. Wide styled
text supports the same presentation. Use `{:?}` for the complete styled text.
Combining `?` with a width or precision is a format error, including with
dynamic arguments.

### Stream insertion

Include `<tjg/color.hpp>` to insert a `styled_text` value into a narrow stream
or a `wstyled_text` value into a wide stream. Insertion uses the same ANSI
rendering as the styled-text formatter.

```cpp
#include <tjg/color.hpp>
#include <iomanip>
#include <sstream>

std::ostringstream os;
os << std::left << std::setfill('*') << std::setw(14)
   << tjg::color::bold("hello world");
// Bold "hello world***", followed by a reset to terminal defaults.
```

Stream width, fill, and alignment control padding. Left alignment pads after
the text. Right, internal, and default alignment pad before it. Padding uses
the effective outermost style, and generated SGR takes no columns. A negative
or zero width adds no padding. Stream precision has no effect on the styled
text. Use the styled-text formatter with an explicit precision to truncate it.

Insertion consumes the field width and resets it to zero. It preserves fill,
precision, and flags. A stream already in an error state keeps its pending
width. A short write sets `badbit`, and the stream's exception mask controls
whether the failure throws. For a debug view of the text and its groups, insert
the result of `std::format("{:?}", text)` or its wide equivalent.

See the [TableDemo walkthrough](table-demo.md) for a complete dashboard
with column defaults, row emphasis, and fixed-width fields.

## Parsing SGR text

Include `<tjg/color.hpp>` and call `parse_styled_text` to turn text containing
ordinary ANSI SGR into an owned `styled_text` (or `wstyled_text` for wide input).

Start with `group` from [the `underlay` example](#use-underlay-to-supply-group-defaults).
Print its debug representation, then use `std::format` to capture the SGR
output in a string. `backslash_escape` from `<tjg/backslash.hpp>` makes the
escape bytes visible as `\e`. Parse the original string and print the parsed
value with `{:?}` as well.

```cpp
std::println("{:?}", group);
auto encoded = std::format("{}", group);
std::println("{}", tjg::backslash_escape(encoded));
auto parsed = tjg::color::parse_styled_text(encoded);
std::println("{:?}", parsed);
```

```text
#000000/#c0c0c0 {
  #ff0000 "red"
  " "
  #008000 "green"
  " "
  #0000ff "blue"
}

\e[38;2;255;0;0;48;2;192;192;192mred\e[38;2;0;0;0m \e[38;2;0;128;0mgreen\e[38;2;0;0;0m \e[38;2;0;0;255mblue\e[0m
{
  #ff0000/#c0c0c0 "red"
  #000000/#c0c0c0 " "
  #008000/#c0c0c0 "green"
  #000000/#c0c0c0 " "
  #0000ff/#c0c0c0 "blue"
}
```

The original group stores the background once and supplies the black
foreground to the spaces. SGR records the active style as the text is written.
The parsed value therefore stores the foreground and background on each
piece of text, including the spaces.

The parser follows the SGR state changes; it does not add an initial reset.
Before the first reset, parsed spans are relative and can inherit an enclosing
formatting style. A reset establishes terminal defaults for **all following
text**, not just the next span.

If a reset occurs before any text, the returned text is absolute as a whole.
Otherwise, earlier text remains relative and the suffix beginning at the reset
forms an absolute group. Its contents have relative styles based on terminal
defaults. Later resets clear the current style within that same group; they do
not create additional nested groups. A single run of text needs no enclosing
group.

For example, a reset prevents an enclosing underline from returning on later
text, even when that text enables another attribute:

```cpp
auto parsed = tjg::color::parse_styled_text("\x1b[1mA\x1b[mB\x1b[1mC");
tjg::color::println(tjg::color::underline(), "{}", parsed);
```

Expected output (followed by a newline):

<pre class="color-output"><span style="font-weight: bold; text-decoration: underline">A</span>B<span style="font-weight: bold">C</span></pre>

`A` inherits underline and adds bold. The reset before `B` establishes defaults,
so `B` is plain and `C` adds only bold. Formatting still restores the enclosing
style after the complete parsed value.

As with other relative styles, an unset attribute before the first reset does
not cancel an inherited attribute; selective clearing of an unknown enclosing
state cannot be represented by these relative style values. Use an explicit
reset when the input must establish a complete state independent of its context.

Consecutive SGR sequences update one current style. No empty text spans are
created; adjacent text with equal styles is combined within each group. A
trailing SGR without text creates no span or empty group. The result represents
styled text, not the original escape bytes or a trailing command's effect on
terminal state. Input text is copied, including embedded nulls when supplied
through a sized string or string view.

Recognized codes cover the library's eight emphasis attributes and their
removal, normal/bright terminal colors, indexed colors, truecolor, and
default-color restoration. Reset (`0`, empty parameters, or leading-zero forms)
clears the current style. Indexed and RGB colors accept semicolon forms and
colon forms, including an omitted/default RGB color space field. Unicode code
units are preserved without decoding.

Non-SGR escapes, including uppercase `M` commands and opaque OSC/DCS payloads,
remain verbatim text. Malformed SGR (including incomplete/out-of-range supported
colors or numeric overflow) is preserved in full and does not change style.
Unknown valid parameters and unsupported colon subparameter groups are ignored.
For an unknown semicolon extended-color mode, the remainder of that SGR is
ignored because its payload boundary is unknown. Preserved raw terminal commands
can affect the terminal outside the style model; parsing is not sanitization.

## Stripping ANSI sequences

Include `<tjg/strip_ansi.hpp>` and call `strip_ansi` to obtain an independent
string with complete ESC-prefixed ANSI sequences removed:

```cpp
auto plain = tjg::strip_ansi("\x1b[31mred\x1b[0m"); // "red"
```

The character-generic function accepts `std::basic_string_view<Char>`; convenience
overloads accept narrow/wide literals and standard strings. It recognizes CSI,
OSC, DCS, SOS, PM, APC, and ordinary ESC sequences by syntax. Private and
unknown commands are removed too, without validating parameter meanings. OSC
ends at BEL or `ESC \`; the other control strings end at `ESC \`. Their payloads
and terminators are removed with them. Hyperlink labels outside OSC markers
remain.

Standalone C0 controls (such as tabs, newlines, and embedded nulls) and
single-byte C1 forms are preserved. Malformed or incomplete escape prefixes are
preserved; scanning resumes at an interrupting character so a subsequent
independent escape can still be removed. Unterminated control strings are
preserved in full, including any apparent escapes inside their payload. CAN and
SUB cancel a control string: its preceding bytes and the cancellation character
are retained, and scanning resumes at that character. Text code units are copied
without Unicode decoding.

This function does not simulate cursor movement, erase commands, carriage
returns, or other terminal behavior, and is not a security sanitizer. Unlike
`parse_styled_text(...).plain_text()`, it removes non-SGR escapes too, without
constructing styled text.

Include `<tjg/color.hpp>` for the styled-text overload. It returns a new
`basic_styled_text<Char>` with the same nested groups, styles, and absolute
boundaries. It strips ANSI sequences from each text span independently,
retaining spans that become empty and sharing unchanged text. The input is
unchanged. Sequences split across text spans are preserved.

```cpp
auto text = tjg::color::bold("\x1b[31mred\x1b[0m");
auto clean = tjg::color::strip_ansi(text); // Bold "red", with raw escapes removed.
auto plain = clean.plain_text();   // "red", without the text's styling.
```

Both narrow and wide styled text are supported. To strip sequences after
joining all text spans, call `strip_ansi(text.plain_text())` instead; this also
removes any complete sequences formed across text-span boundaries.

## Backslash escaping and unescaping

Include `<tjg/backslash.hpp>` for `backslash_escape` and `backslash_unescape`.
These text utilities return independent strings and support narrow and wide
text, including embedded NULs when passed a string or a length-bearing view.
They require neither ANSI parsing nor styled text.

```cpp
#include <tjg/backslash.hpp>

auto readable = tjg::backslash_escape("\x1b[31mred\x1b[0m\n");
// readable contains the literal text: \e[31mred\e[0m\n
auto original = tjg::backslash_unescape(readable);
```

The decoder accepts the following escape sequences. The last column describes
the canonical spelling produced by `backslash_escape` and `backslash_escape_to`.

| Escape | Character or value   | ASCII  | Emits |
| ------ | -------------------- | ------ | ----- |
| `\a`   | Alert (bell)         | `0x07` | Yes   |
| `\b`   | Backspace            | `0x08` | Yes   |
| `\e`   | Escape (ESC)         | `0x1b` | Yes   |
| `\f`   | Form feed            | `0x0c` | Yes   |
| `\n`   | Line feed (newline)  | `0x0a` | Yes   |
| `\r`   | Carriage return      | `0x0d` | Yes   |
| `\t`   | Horizontal tab       | `0x09` | Yes   |
| `\v`   | Vertical tab         | `0x0b` | Yes   |
| `\\`   | Backslash            | `0x5c` | Yes   |
| `\"`   | Double quote         | `0x22` | Yes   |
| `\'`   | Apostrophe           | `0x27` | No    |
| `\?`   | Question mark        | `0x3f` | No    |
| `\x00` | NUL                  | `0x00` | Yes   |
| `\x7f` | Delete (DEL)         | `0x7f` | Yes   |
| `\xhh` | Exactly 2 hex digits | `0xhh` | Yes   |
| `\nnn` | 1 to 3 octal digits  |        | No    |
| `\u`   | Exactly 4 hex digits |        | No    |
| `\U`   | Exactly 8 hex digits |        | No    |

`backslash_escape` uses `\a`, `\b`, `\e`, `\f`, `\n`, `\r`, `\t`, and `\v` for
the corresponding controls. `\e` represents ESC (`0x1b`); it is an extension to
the standard C++ escape spellings. It uses `\xhh` with two lowercase hexadecimal
digits for other ASCII C0 controls and DEL (`0x7f`), including `\x00` for NUL.
Literal backslashes become `\\` and double quotes become `\"`. Other code units,
including non-ASCII text and UTF-8 bytes, are preserved. No surrounding quotes
are added.

`backslash_unescape` recognizes those forms, plus `\'` for an apostrophe and
`\?` for a question mark. Ordinary apostrophes and question marks remain
unchanged when escaping. Hex digits may use either case. The decoder also
accepts one to three octal digits (`\0` through `\377`). A `\x` escape consumes
exactly two hex digits, and an octal escape consumes at most three digits.
Subsequent digits remain ordinary text.

Unicode escapes take exactly four hex digits after `\u` and eight after `\U`.
For example, `backslash_unescape("\\u754C\\U0001F600")` produces the UTF-8 string
`界😀`. Wide output uses UTF-16 with 16-bit `wchar_t` and UTF-32 with 32-bit
`wchar_t`. Use `\U` for a code point above `U+FFFF`.

Unknown or malformed escapes throw `std::invalid_argument`. Examples include
`\q`, `\xG1`, `\u123`, a trailing backslash, and braced numeric escapes.
Unicode escapes naming surrogates also throw `std::invalid_argument`.
Octal values above 255 and Unicode values above `U+10FFFF` throw
`std::out_of_range`. The decoder preserves
surrounding quotes and processes each escape once. If `backslash_unescape_to`
throws, output already written remains in the destination.

To write into an existing destination, use `backslash_escape_to(out, text)` or
`backslash_unescape_to(out, text)`. Both accept output iterators and return the
advanced iterator. They support narrow and wide string views, literals, and
strings without allocating an intermediate string.

```cpp
#include <iterator>
#include <string>

std::string log = "Received: ";
tjg::backslash_escape_to(std::back_inserter(log), "\x1b[31mred\n");
// log contains: Received: \e[31mred\n
```

The iterator functions and functions returning strings support constant
evaluation when the standard library and output iterator support it. Any
dynamic storage allocated during constant evaluation must be released within
that constant evaluation; these functions can produce temporary strings for a
compile-time check.

The output must not invalidate or overwrite unread input. In particular, do not
append to the string supplying the input view, since reallocation can invalidate
that view.

`backslash_unescape(backslash_escape(text))` recovers the original code units.
To inspect a styled value's text, pass `text.plain_text()`; to inspect its
emitted SGR sequences too, pass the formatted string. These functions do not
interpret ANSI sequences or remove explicit styles.

## Individual styled arguments

Include `<tjg/color.hpp>` to style an individual replacement
field with `styled`. Its format specifications apply to the underlying value.

::: styled(const T&, text_style)
    options:
      color_reference: true

Expected output for the example above (without a trailing newline):

<pre class="color-output">Elapsed time: <span style="color: #008000; background-color: #191970">1.23</span> seconds</pre>

```cpp
using namespace tjg::color;
std::println("Amount: {:>8.2f}", styled(1.23, fg(rgb::green)));
```

Expected output (followed by a newline):

<pre class="color-output">Amount: <span style="color: #008000">    1.23</span></pre>

The width and precision apply to the number, including padding inside the styled
span. Relative styles inherit the shared terminal state; absolute styles replace
it for this value and always emit an explicit reset, even
when the enclosing state already has the same attributes. Both restore the
enclosing style afterward. For examples, see
[Text style rendering](index.md#TextStyleRendering).

To insert a styled value directly into an ostream, include
`<tjg/color.hpp>` and use `os << tjg::color::styled(value, style)`.
[Styled stream insertion](print.md#styled-stream-insertion) describes stream
formatting, wide streams, and the wrapper's reference lifetime.

```cpp
#include <tjg/color.hpp>
#include <iomanip>
#include <iostream>
#include <numbers>

using namespace tjg::color;
auto style = fg(rgb::green).bold();
std::cout << "Pi: " << std::fixed << std::setprecision(2)
          << styled(std::numbers::pi, style) << '\n';
```

Expected output (followed by a newline):

<pre class="color-output">Pi: <span style="color: #008000; font-weight: bold">3.14</span></pre>

Only `3.14` is styled in bold green. The value is rounded to two decimal places
using the ostream's formatting settings.

