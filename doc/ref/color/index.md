# Header `<tjg/color.hpp>`

Provides formatting, printing, styled-argument wrappers, stream insertion, and terminal sequence helpers.

[API reference](../index.md)

## Formatting and output

- [`tjg::color::format`](format.md)
- [`tjg::color::format_to`](format_to.md)
- [`std::formatter` specializations](formatter.md)
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

[SGR overview](sgr/index.md)

- [`tjg::color::basic_sgr_buffer`](sgr/basic_sgr_buffer.md)
- [`tjg::color::parse_styled_text`](sgr/parse_styled_text.md)
- [`tjg::color::sgr_buffer`](sgr/sgr_buffer.md)
- [`tjg::color::sgr_max_length`](sgr/sgr_max_length.md)
- [`tjg::color::sgr_reset`](sgr/sgr_reset.md)
- [`tjg::color::sgr_reset_length`](sgr/sgr_reset_length.md)
- [`tjg::color::strip_ansi`](sgr/strip_ansi.md)
- [`tjg::color::to_sgr`](sgr/to_sgr.md)
- [`tjg::color::wrap_sgr`](sgr/wrap_sgr.md)

## Headers available through this include

- [`<tjg/color/colors.hpp>`](colors/index.md)
- [`<tjg/color/text_style.hpp>`](text_style/index.md)
- [`<tjg/color/styled_text.hpp>`](styled_text/index.md)
- [TJG utilities](../util/index.md)
