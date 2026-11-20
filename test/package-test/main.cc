#include <tjg/color.hpp>

#include <print>
#include <sstream>

#ifdef FMT_VERSION
#  error "TJG must not include the fmt engine"
#endif
#if defined(_MSVC_LANG)
// /std:c++latest can report a C++20 draft value on MSVC. CMake also
// checks that the imported target explicitly requests cxx_std_23.
static_assert(_MSVC_LANG >= 202002L);
#else
static_assert(__cplusplus >= 202100L);
#endif

int main() {
  const auto hello = tjg::color::styled("hello", tjg::color::bold());
  const auto rendered = std::format("{} world", hello);
  if (rendered != "\x1b[1mhello\x1b[0m world") return 1;
  if (tjg::strip_ansi(rendered) != "hello world") return 2;
  if (tjg::backslash_unescape(tjg::backslash_escape(rendered)) != rendered)
    return 3;
  std::ostringstream output;
  output << hello << " world";
  if (output.str() != rendered) return 4;
  if (tjg::color::format(tjg::color::underline(), L"{}", L"wide") !=
      L"\x1b[4mwide\x1b[0m")
    return 5;
  const auto text = tjg::color::parse_styled_text<char>("\x1b[1mhello");
  if (std::format("{}", text) != "\x1b[1mhello\x1b[0m") return 6;
  const auto wide_text = tjg::color::parse_styled_text<wchar_t>(L"wide");
  if (std::format(L"{}", wide_text) != L"wide") return 7;
  std::wostringstream wide_output;
  wide_output << wide_text;
  if (wide_output.str() != L"wide") return 8;
  const auto lines = tjg::color::word_wrap(
    tjg::color::styled_text{"abcdefghijklmnop next"}, 16);
  if (lines.size() != 2 || lines[1].plain_text() != "next") return 9;
  const auto wide_lines = tjg::color::word_wrap(
    tjg::color::wstyled_text{L"abcdefghijklmnop next"}, 16);
  if (wide_lines.size() != 2 || wide_lines[1].plain_text() != L"next") return 10;
  std::println("{}", hello);
}
