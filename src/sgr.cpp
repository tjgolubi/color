/// @copyright 2026 Terry Golubiewski, all rights reserved.
#include <tjg/color/bits/sgr_support.hpp>

namespace tjg::color {

namespace detail {

auto make_sgr(const text_style& style) -> std::string {
  if (style.empty()) return {};
  auto sgr = detail::sgr_buffer{};
  detail::append_sgr(sgr, style);
  return std::string{sgr.view()};
}

auto make_sgr(const text_style& target, const text_style& initial)
  -> std::string
{
  auto sgr = detail::sgr_buffer{};
  detail::append_sgr_transition(sgr, target, initial);
  return std::string{sgr.view()};
}

} // detail

template<CharType Char>
[[nodiscard]]
auto wrap_sgr(const text_style& style, std::basic_string_view<Char> sv)
  -> std::basic_string<Char>
{
  if (sv.empty()) return {};
  if (style.empty()) return std::basic_string<Char>{sv};
  constexpr auto reset = sgr_reset();
  auto sgr = detail::sgr_buffer{};
  detail::append_sgr(sgr, style);
  auto result = std::basic_string<Char>{};
  result.reserve(sgr.size() + sv.size() + reset.size());
  result.append(sgr.begin(), sgr.end());
  result.append(sv);
  result.append(reset.begin(), reset.end());
  return result;
}  // wrap_sgr

template
auto wrap_sgr<char>(const text_style&, std::string_view) -> std::string;

template
auto wrap_sgr<wchar_t>(const text_style&, std::wstring_view) -> std::wstring;

} // tjg::color
