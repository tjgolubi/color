#include "tjg/color.hpp"

int main() {
  const auto value = tjg::color::styled("hello", tjg::color::bold());
  const auto narrow = tjg::color::format(tjg::color::underline(), "{}", value);
  const auto wide = tjg::color::format(tjg::color::bold(), L"{}", L"wide");
  const auto lines = tjg::color::word_wrap(
    tjg::color::styled_text{"abcdefghijklmnop next"}, 16);
  const auto wide_lines = tjg::color::word_wrap(
    tjg::color::wstyled_text{L"abcdefghijklmnop next"}, 16);
  return narrow != "\x1b[4m\x1b[1mhello\x1b[22m\x1b[0m" ||
         wide != L"\x1b[1mwide\x1b[0m" ||
         lines.size() != 2 || lines.back().plain_text() != "next" ||
         wide_lines.size() != 2 || wide_lines.back().plain_text() != L"next" ||
         tjg::color::detail::get_style_state() != tjg::color::text_style{};
}
