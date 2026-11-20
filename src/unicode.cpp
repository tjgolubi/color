/// @copyright 2026 Terry Golubiewski, all rights reserved.
// Unicode algorithms adapted from {fmt}, copyright (c) 2012-present
// Victor Zverovich and {fmt} contributors. See the repository's license.
#include <tjg/color/bits/unicode.hpp>
#include "UnicodeData.hpp"

#include <algorithm>
#include <type_traits>

namespace tjg::color::detail::unicode {

namespace detail {

/// Looks up the low 16 bits of a code point in one plane's compressed table.
auto is_printable(uint16_t x, const singleton* singletons,
                         size_t singletons_size,
                         const unsigned char* singleton_lowers,
                         const unsigned char* normal, size_t normal_size)
  -> bool
{
  auto upper = x >> 8;
  auto lower_start = 0;
  for (size_t i = 0; i < singletons_size; ++i) {
    auto s = singletons[i];
    auto lower_end = lower_start + s.lower_count;
    if (upper < s.upper)
      break;
    if (upper == s.upper) {
      for (auto j = lower_start; j < lower_end; ++j) {
        if (singleton_lowers[j] == (x & 0xff))
          return false;
      }
    }
    lower_start = lower_end;
  }

  auto xsigned = static_cast<int>(x);
  auto current = true;
  for (size_t i = 0; i < normal_size; ++i) {
    auto v = static_cast<int>(normal[i]);
    auto len = ((v & 0x80) != 0) ? ((v & 0x7f) << 8) | normal[++i] : v;
    xsigned -= len;
    if (xsigned < 0)
      break;
    current = !current;
  }
  return current;
} // is_printable

} // detail

/**
 * Tests whether debug quoting treats a code point as printable.
 * The generated table marks ASCII space printable and excludes controls,
 * format characters, surrogates, private-use and unassigned code points, and
 * other separators. Values above U+10FFFF also return false.
 */
auto is_printable(uint32_t cp) -> bool {
  const auto lower = static_cast<uint16_t>(cp);
  if (cp < 0x10000) {
    return detail::is_printable(lower, detail::singletons0,
                                std::size(detail::singletons0),
                                detail::singletons0_lower, detail::normal0,
                                std::size(detail::normal0));
  }
  if (cp < 0x20000) {
    return detail::is_printable(lower, detail::singletons1,
                                std::size(detail::singletons1),
                                detail::singletons1_lower, detail::normal1,
                                std::size(detail::normal1));
  }
  for (const auto& range : detail::nonprintable_ranges) {
    if (range.first <= cp && cp < range.end)
      return false;
  }
  return cp < 0x110000;
} // is_printable(uint32_t)

template<CharType Char>
auto text_prefix_impl(std::basic_string_view<Char> text, size_t limit)
  -> std::pair<size_t, size_t>
{
  if constexpr (!std::is_same_v<Char, char>) {
    auto size = std::min(text.size(), limit);
    if constexpr (sizeof(Char) == sizeof(uint16_t)) {
      if (size != 0 && size < text.size()) {
        const auto before = static_cast<uint16_t>(text[size - 1]);
        const auto after  = static_cast<uint16_t>(text[size]);
        if (0xd800 <= before && before <= 0xdbff
         && 0xdc00 <= after  && after  <= 0xdfff)
          --size;
      }
    }
    return {size, size};
  } else {
    size_t size = 0, width = 0;
    while (size < text.size()) {
      const auto cp = decode_utf8(text.substr(size));
      const auto columns = display_width_of(cp.value);
      if (columns > limit - width)
        break;
      size  += cp.size;
      width += columns;
    }
    return {size, width};
  }
} // text_prefix


auto text_prefix(std::string_view text, size_t limit)
  -> std::pair<size_t, size_t>
{ return text_prefix_impl<char>(text, limit); }

auto text_prefix(std::wstring_view text, size_t limit)
  -> std::pair<size_t, size_t>
{ return text_prefix_impl<wchar_t>(text, limit); }

} // tjg::color::detail::unicode
