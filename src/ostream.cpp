/// @copyright 2026 Terry Golubiewski, all rights reserved.
#include <tjg/color/bits/color-ostream.hpp>

#include <iostream>
#include <limits>

namespace tjg::color {

namespace detail {

// Assumes the standard streams use their usual buffers.
[[nodiscard]] auto is_tty(std::ostream& os) noexcept -> bool {
  if (&os == &std::cout)
    return is_tty(stdout);
  if (&os == &std::cerr || &os == &std::clog)
    return is_tty(stderr);
  return false;
} // is_tty

// Assumes the standard streams use their usual buffers.
[[nodiscard]] auto is_tty(std::wostream& os) noexcept -> bool {
  if (&os == &std::wcout)
    return is_tty(stdout);
  if (&os == &std::wcerr || &os == &std::wclog)
    return is_tty(stderr);
  return false;
} // is_tty

} // detail

void vprint_nonunicode(std::ostream& os,
                      std::string_view fmt, std::format_args args)
{
  auto guard = detail::sgr_enable_scope{detail::is_tty(os)};
  auto scope = detail::style_scope{};
  std::vprint_nonunicode(os, fmt, args);
}

void vprint_unicode(std::ostream& os,
                    std::string_view fmt, std::format_args args)
{
  auto guard = detail::sgr_enable_scope{detail::is_tty(os)};
  auto scope = detail::style_scope{};
  std::vprint_unicode(os, fmt, args);
}

void vprint_nonunicode(std::ostream& os, const text_style& style,
                      std::string_view fmt, std::format_args args)
{
  auto writer = [&](const char* data, std::size_t size)
    { os.write(data, static_cast<std::streamsize>(size)); };
  auto guard = detail::sgr_enable_scope{detail::is_tty(os)};
  TJG_SGR_SCOPE(writer, style);
  std::vprint_nonunicode(os, fmt, args);
}

void vprint_unicode(std::ostream& os, const text_style& style,
                    std::string_view fmt, std::format_args args)
{
  auto writer = [&](const char* data, std::size_t size)
    { os.write(data, static_cast<std::streamsize>(size)); };
  auto guard = detail::sgr_enable_scope{detail::is_tty(os)};
  TJG_SGR_SCOPE(writer, style);
  std::vprint_unicode(os, fmt, args);
}

namespace {

template<bool Wrap = false, CharType Char>
auto insert_styled_text(std::basic_ostream<Char>& os,
                        const basic_styled_text<Char>& value)
  -> std::basic_ostream<Char>&
{
  auto sentry = typename std::basic_ostream<Char>::sentry{os};
  if (!sentry)
    return os;

  auto specs = detail::string_format_specs<Char>{};
  const auto width = os.width();
  if (width > static_cast<decltype(width)>(std::numeric_limits<int>::max()))
    detail::standard_format_error("styled text stream width is too large");
  if (width > 0) specs.width = static_cast<std::size_t>(width);
  const auto fill = os.fill();
  specs.set_fill(std::basic_string_view<Char>{&fill, 1});
  const auto alignment = os.flags() & std::ios_base::adjustfield;
  specs.alignment = alignment == std::ios_base::left ? '<' : '>';
  os.width(0);

  auto wrap_width = std::size_t{0};
  if constexpr (Wrap) {
    wrap_width = specs.width == 0 ? detail::default_wrap_width : specs.width;
    if (wrap_width < detail::min_wrap_width)
      detail::standard_format_error("wrapped: width must be at least 4");
    specs.width = alignment == 0 ? 0 : wrap_width;
  }

  auto output = std::ostreambuf_iterator<Char>{os};
  auto guard  = detail::sgr_enable_scope(detail::is_tty(os));

  bool failed;
#if defined(__cpp_exceptions) || defined(_CPPUNWIND)
  try {
#endif
    if constexpr (Wrap) {
      failed = detail::render_wrapped(value, wrap_width, specs, output)
                .failed();
    } else {
      auto renderer = detail::styled_text_renderer<Char>{specs};
      failed = renderer.format(value, output).failed();
    }
#if defined(__cpp_exceptions) || defined(_CPPUNWIND)
  } catch (...) {
    const bool rethrow = (os.exceptions() & std::ios_base::badbit) != 0;
    // Keep the stream buffer's exception if setstate() also throws.
    try { os.setstate(std::ios_base::badbit); }
    catch (...) { }
    if (rethrow) throw;
    return os;
  }
#endif

  if (failed)
    os.setstate(std::ios_base::badbit);
  return os;
} // << styled_text

} // local

auto operator<<(std::ostream&  os, const styled_text&  value) -> std::ostream&
{ return insert_styled_text(os, value); }

auto operator<<(std::wostream& os, const wstyled_text& value) -> std::wostream&
{ return insert_styled_text(os, value); }

auto detail::operator<<(std::ostream& os, const wrapped_arg<char>& arg)
  -> std::ostream&
{ return insert_styled_text<true>(os, arg.text); }

auto detail::operator<<(std::wostream& os, const wrapped_arg<wchar_t>& arg)
  -> std::wostream&
{ return insert_styled_text<true>(os, arg.text); }

} // tjg::color
