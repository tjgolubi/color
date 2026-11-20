# Header `<tjg/color.hpp>`

Provides formatting, printing, styled-argument wrappers, stream insertion, and terminal sequence helpers.

[API reference](../index.md)

## Formatting and output

- [`tjg::color::format`](format.md)
- [`tjg::color::format_to`](format_to.md)
- [`std::formatter` specializations](formatter/index.md)
- [`tjg::color::operator<<`](operator-insertion.md)
- [`tjg::color::print`](print.md)
- [`tjg::color::println`](println.md)
- [`tjg::color::styled`](styled.md)
- [`tjg::color::vformat`](vformat.md)
- [`tjg::color::vformat_to`](vformat_to.md)
- [`tjg::color::vprint_nonunicode`](vprint_nonunicode.md)
- [`tjg::color::vprint_unicode`](vprint_unicode.md)
- [`tjg::color::write_debug_value`](write_debug_value.md)
- [`tjg::color::write_value`](write_value.md)

## SGR and ANSI helpers

See the [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) [helper overview](sgr/index.md).

| Name                                                       | Description                                                        |
| ---------------------------------------------------------- | ------------------------------------------------------------------ |
| [`tjg::color::parse_styled_text`](sgr/parse_styled_text.md) | Parses SGR sequences into styled text.                             |
| [`tjg::color::sgr_reset`](sgr/sgr_reset.md)                 | Returns a sequence that resets terminal colors and emphasis.       |
| [`tjg::color::strip_ansi`](sgr/strip_ansi.md)               | Removes escape sequences while preserving styles and grouping.     |
| [`tjg::color::to_sgr`](sgr/to_sgr.md)                       | Generates an opening style sequence or a style transition.         |
| [`tjg::color::wrap_sgr`](sgr/wrap_sgr.md)                   | Surrounds literal text with styling and a reset.                   |

## Headers available through this include

- [`<tjg/color/colors.hpp>`](colors/index.md)
- [`<tjg/color/text_style.hpp>`](text_style/index.md)
- [`<tjg/color/styled_text.hpp>`](styled_text/index.md)
- [TJG utilities](../util/index.md)
