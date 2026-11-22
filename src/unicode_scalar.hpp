/// @copyright 2026 Terry Golubiewski, all rights reserved.
#pragma once

#include <tjg/color/bits/unicode.hpp>

#include <algorithm>

namespace tjg::color::detail::unicode {

constexpr auto decode(std::string_view text) noexcept -> utf8_character {
  return decode_utf8(text);
}

constexpr auto decode(std::wstring_view text) noexcept -> utf8_character {
  auto cp = static_cast<std::uint32_t>(text.front());
  if constexpr (sizeof(wchar_t) == 2) {
    if (cp >= 0xd800 && cp <= 0xdbff && text.size() > 1) {
      const auto low = static_cast<std::uint32_t>(text[1]);
      if (low >= 0xdc00 && low <= 0xdfff)
        return {0x10000 + ((cp - 0xd800) << 10) + low - 0xdc00, 2};
    }
  }
  if (cp > 0x10ffff || (cp >= 0xd800 && cp <= 0xdfff))
    cp = 0xffffffffu;
  return {cp, 1};
}

template<typename Range, std::size_t N>
constexpr auto contains(const Range (&ranges)[N], std::uint32_t value)
  noexcept -> bool
{
  const auto it = std::lower_bound(std::begin(ranges), std::end(ranges), value,
    [](const Range& range, std::uint32_t cp) { return range.last < cp; });
  return it != std::end(ranges) && it->first <= value;
}

} // tjg::color::detail::unicode
