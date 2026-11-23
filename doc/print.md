# Styled Output

Include `<tjg/color.hpp>` to use these output overloads. See
[Text style rendering](index.md#TextStyleRendering) for the shared styling rules.

Use `tjg::color::print()` or `tjg::color::println()` whenever an argument may
contain styled text. Colors and emphasis appear on a terminal. Redirect output
to a file or pipe and you get plain text. Calls to `std::print()` and
`std::println()` skip {color}'s destination check and can put escape sequences
in redirected output.

Use [`format()`](format.md#format) when you want to build a string containing
styling sequences. Writing a string that already contains escape sequences
passes them through as text.

## print to a stream

Pass a `FILE*` and a format string to style individual arguments without
setting a style for the whole message.

```cpp
using namespace tjg::color;
tjg::color::print(stderr, "Status: {}", bold("failed"));
```

::: print(FILE*, const text_style&, std::format_string<T...>, T&&...)
    options:
      color_reference: true

## print to stdout

::: print(const text_style&, std::format_string<T...>, T&&...)
    options:
      color_reference: true

## println to a stream

::: println(FILE*, const text_style&, std::format_string<T...>, T&&...)
    options:
      color_reference: true

## println to stdout

::: println(const text_style&, std::format_string<T...>, T&&...)
    options:
      color_reference: true

## Runtime print

The runtime overloads take an argument pack created with
`std::make_format_args`. The arguments must remain alive while the pack is used.
The Unicode and non-Unicode overloads use the corresponding standard output
paths. Overloads without a destination write to stdout.

```cpp
int result = 42;
auto args = std::make_format_args(result);
tjg::color::vprint_unicode(stdout, tjg::color::fg(tjg::color::rgb::green), "Result: {}", args);
```

::: vprint_unicode(FILE*, const text_style&, std::string_view, std::format_args)
    options:
      color_reference: true

::: vprint_unicode(const text_style&, std::string_view, std::format_args)
    options:
      color_reference: true

::: vprint_nonunicode(FILE*, const text_style&, std::string_view, std::format_args)
    options:
      color_reference: true

::: vprint_nonunicode(const text_style&, std::string_view, std::format_args)
    options:
      color_reference: true

## Styled ostream output

Include `<tjg/color.hpp>` to use the styled `std::ostream` overloads.

```cpp
#include <tjg/color.hpp>
#include <sstream>

namespace clr = tjg::color;
std::ostringstream os;
clr::print(os, "Result: {}\n", clr::bold("42"));
clr::println(os, "Status: {}", clr::bold("failed"));
// os.str() contains "Result: 42\nStatus: failed\n".
```

Use `clr::print()` and `clr::println()` for these calls. An unqualified call
can be ambiguous because the stream argument also brings the standard
library's overloads into consideration.

To style the whole message, pass a `text_style` after the stream. On a terminal,
that style applies through the newline added by `println()`. The function
restores the enclosing style afterward.
The formatted-output functions use the stream's locale for localized format
specifications and preserve settings such as field width and numeric base.

If you write raw SGR directly, use `tjg::color::sgr_reset()` to explicitly
restore terminal defaults.

::: print(std::ostream&, const text_style&, std::format_string<T...>, T&&...)
    options:
      color_reference: true

::: println(std::ostream&, const text_style&, std::format_string<T...>, T&&...)
    options:
      color_reference: true

::: vprint_unicode(std::ostream&, const text_style&, std::string_view, std::format_args)
    options:
      color_reference: true

::: vprint_nonunicode(std::ostream&, const text_style&, std::string_view, std::format_args)
    options:
      color_reference: true

For wide streams, use styled stream insertion to get the destination check.

## Styled stream insertion

With `<tjg/color.hpp>`, insert the result of `tjg::color::styled(value, style)`
directly into a stream. The operator returns the same stream by reference for
chaining and supports both `std::ostream` and `std::wostream` in C++23 and later.
The value must support insertion into that stream; a standard formatter is not
required.

```cpp
#include <tjg/color.hpp>
#include <iomanip>
#include <sstream>

using namespace tjg::color;
const auto style = text_style{emphasis::bold};
std::ostringstream os;
os << "Result: " << std::hex << std::setfill('0') << std::setw(4)
   << styled(42, style) << '\n';
// "Result: 002a\n"

std::wostringstream wide;
wide << styled(L"message", style) << L'\n';
```

The underlying value uses normal stream formatting, including numeric base,
precision, fill, alignment, and field width. SGR sequences do not consume the
field width; any padding produced by the value's insertion is inside the
styled span. Stream formatting settings follow the value's ordinary insertion
behavior. Strings are inserted literally, without interpreting braces as format
fields.

On a terminal, a nonempty style emits an [opening SGR sequence](format.md#to_sgr),
followed by the value and a reset to terminal defaults. This also applies to an
empty string with a nonempty style. An empty style or a non-terminal stream
simply inserts the value.

If inserting the value throws after opening a style, the operator attempts
to write a reset, ignores any exception from that recovery write, and rethrows
the original exception. A failed stream may prevent the reset from being
written. On the normal path, stream failures follow the stream's exception
mask, including failures while writing the opening sequences or final reset.
The operator also supports builds with exceptions disabled.

Use `styled(value, style)` directly in an insertion or print call. If you save
the result, keep both the value and the style alive until the operation is
complete.

To insert a styled-text value directly, see [styled-text stream
insertion](styled.md#stream-insertion).
