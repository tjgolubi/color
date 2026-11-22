/// @file
/// Styled std::ostream output
/// @copyright 2026 Terry Golubiewski, all rights reserved.
#pragma once

#include "styled_text-format.hpp"
#include "text_style-format.hpp"
#include "colors-format.hpp"
#include "emphasis-format.hpp"
#include "sgr_support.hpp"
#include <tjg/inline_buffer.hpp>
#include <tjg/utility.hpp>

#include <ostream>
#include <string_view>
#include <iterator>
#include <concepts>
#include <type_traits>
#include <utility>

namespace tjg::color {

/**
 * Inserts color values and emphasis using their value notation.
 * Emphasis names are enclosed in braces; empty emphasis displays `{}`.
 * Width, fill, and alignment apply as for ordinary string insertion.
 */
template<CharType Char, typename T>
  requires (Color<T>
            || std::same_as<std::remove_cvref_t<T>, color_t>
            || std::same_as<std::remove_cvref_t<T>, no_color_t>
            || std::same_as<std::remove_cvref_t<T>, text_style>
            || std::same_as<std::remove_cvref_t<T>, emphasis>)
        && requires(char* out, const T& value)
           { (void) tjg::color::write_value(out, value); }
auto operator<<(std::basic_ostream<Char>& os, const T& value)
  -> std::basic_ostream<Char>&
{
  auto buf = basic_inline_buffer<Char>{};
  (void) write_value(std::back_inserter(buf), value);
  return os << buf.view();
}

/**
 * Writes a style's SGR sequence without a trailing reset. An empty style
 * writes a reset. Pending stream width and other formatting settings are
 * preserved. This raw output does not update the tracked formatting style.
 */
template<CharType Char>
auto operator<<(std::basic_ostream<Char>& os, const text_style& style)
  -> std::basic_ostream<Char>&
{
  auto buffer = detail::basic_sgr_buffer<Char>{};
  detail::append_sgr(buffer, style.empty() ? absolute(style) : style);
  return os.write(buffer.data(), static_cast<std::streamsize>(buffer.size()));
}

namespace detail {

template<typename T, CharType Char>
auto operator<<(std::basic_ostream<Char>& os, const styled_arg<T>& arg)
  -> std::basic_ostream<Char>&
{
  if (arg.style.empty())
    return os << arg.value;

  constexpr auto reset = sgr_reset<Char>();

  auto write_view = [&os](std::basic_string_view<Char> sgr) -> decltype(os)
    { return os.write(sgr.data(), static_cast<std::streamsize>(sgr.size())); };

  auto sgr = basic_sgr_buffer<Char>{};
  append_sgr(sgr, arg.style);
  write_view(sgr.view());
#if defined(__cpp_exceptions) || defined(_CPPUNWIND)
  try {
#endif
    os << arg.value;
#if defined(__cpp_exceptions) || defined(_CPPUNWIND)
  } catch (...) {
    // Reset is best-effort; preserve the original insertion exception.
    try { write_view(reset); }
    catch (...) { }
    throw;
  }
#endif
  return write_view(reset);
} // << styled_arg

/// Inserts wrapped lines, consuming the stream's field width.
auto operator<<(std::ostream& os, const wrapped_arg& arg) -> std::ostream&;

} // detail

#define TJG_SGR_OSTREAM_SCOPE(stream, style) \
  auto writer = [&](const char* data, std::size_t size) \
    { stream.write(data, static_cast<std::streamsize>(size)); }; \
  TJG_SGR_SCOPE(writer, style)

/**
 * Prints styled text using the standard non-Unicode stream output path.
 * Restores the enclosing style after the formatted text.
 */
void vprint_nonunicode(std::ostream& os, text_style style,
                              std::string_view fmt, std::format_args args);

/// Prints styled text using the standard Unicode stream output path.
/// Restores the enclosing style after the formatted text.
void vprint_unicode(std::ostream& os, text_style style,
                           std::string_view fmt, std::format_args args);

/**
 * Prints formatted text to `os` using `style`, then restores the enclosing
 * style.
 *
 * **Example**:
 *
 *     tjg::color::print(os, tjg::color::text_style{tjg::color::emphasis::bold}, "Result: {}", 42);
 */
template<typename... T>
void print(std::ostream& os, text_style style, std::format_string<T...> fmt,
           T&&... args)
{
  TJG_SGR_OSTREAM_SCOPE(os, style);
  std::print(os, fmt, std::forward<T>(args)...);
}

/**
 * Prints formatted text to `os` using `style`, then restores the enclosing
 * style.
 */
template<typename... T>
void println(std::ostream& os, text_style style, std::format_string<T...> fmt,
             T&&... args)
{
  TJG_SGR_OSTREAM_SCOPE(os, style);
  std::println(os, fmt, std::forward<T>(args)...);
}

/**
 * Inserts styled text using the formatter's ANSI rendering machinery.
 * Stream width, fill, and alignment control padding. Stream precision is
 * ignored, as for string insertion. Internal alignment behaves as right
 * alignment; only left places padding after text.
 * Field width is consumed; other stream settings are preserved.
 */
auto operator<<(std::ostream& os, const styled_text& value) -> std::ostream&;
auto operator<<(std::wostream& os, const wstyled_text& value) -> std::wostream&;

template<CharType Char>
auto operator<<(std::basic_ostream<Char>& os,
                const basic_styled_text<Char>& value)
  -> std::basic_ostream<Char>&
{ return operator<<(os, value); }


} // tjg::color

#undef TJG_SGR_OSTREAM_SCOPE
