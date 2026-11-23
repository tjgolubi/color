/// @copyright 2026 Terry Golubiewski, all rights reserved.
#include <tjg/color/bits/text_style-format.hpp>

#include <system_error>

namespace tjg::color {

namespace detail {

[[nodiscard]] auto get_style_state() -> text_style& {
  static text_style _state{};
  return _state;
}

[[nodiscard]] auto get_sgr_enable() -> bool& {
  static bool _state = true;
  return _state;
}

void write_file(FILE* fp, const char* data, std::size_t size) {
  auto count = std::fwrite(data, 1, size, fp);
  if (count == size)
    return;
  const auto ec = std::make_error_code(std::io_errc::stream);
  const auto x  = std::system_error{ec, "writing SGR"};
  TJG_THROW(x);
}

} // detail

void vprint_nonunicode(FILE* fp, std::string_view fmt, std::format_args args) {
  auto guard = detail::sgr_enable_scope{detail::is_tty(fp)};
  auto scope = detail::style_scope{};
  std::vprint_nonunicode(fp, fmt, args);
}

void vprint_unicode(FILE* fp, std::string_view fmt, std::format_args args) {
  auto guard = detail::sgr_enable_scope{detail::is_tty(fp)};
  auto scope = detail::style_scope{};
  std::vprint_unicode(fp, fmt, args);
}

auto vformat(std::string_view fmt, std::format_args args) -> std::string {
  auto scope = detail::style_scope{};
  return std::vformat(fmt, args);
}

auto vformat(std::wstring_view pattern, std::wformat_args args) -> std::wstring
{
  auto scope = detail::style_scope{};
  return std::vformat(pattern, args);
}

void vprint_nonunicode(FILE* fp, const text_style& style, std::string_view fmt,
                      std::format_args args)
{
  auto writer = [&](const char* data, std::size_t size)
                { detail::write_file(fp, data, size); };

  auto guard = detail::sgr_enable_scope{detail::is_tty(fp)};
  TJG_SGR_SCOPE(writer, style);
  std::vprint_nonunicode(fp, fmt, args);
}

void vprint_unicode(FILE* fp, const text_style& style, std::string_view fmt,
                    std::format_args args)
{
  auto writer = [&](const char* data, std::size_t size)
                { detail::write_file(fp, data, size); };

  auto guard = detail::sgr_enable_scope{detail::is_tty(fp)};
  TJG_SGR_SCOPE(writer, style);
  std::vprint_unicode(fp, fmt, args);
}

auto vformat(const text_style& style, std::string_view fmt, std::format_args args)
  -> std::string
{
  auto result = std::string{};
  auto writer = [&](const char* data, std::size_t size)
                { result.append(data, size); };

  TJG_SGR_SCOPE(writer, style);
  std::vformat_to(std::back_inserter(result), fmt, args);
  scope.finish();
  return result;
}

auto vformat(const text_style& style,
             std::wstring_view pattern, std::wformat_args args)
  -> std::wstring
{
  auto result = std::wstring{};
  auto writer = [&](const char* data, std::size_t size)
                { result.append(data, data + size); };

  TJG_SGR_SCOPE(writer, style);
  std::vformat_to(std::back_inserter(result), pattern, args);
  scope.finish();
  return result;
}

} // tjg::color
