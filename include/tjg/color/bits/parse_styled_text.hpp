// Parse ordinary ANSI SGR into styled text.
#pragma once

#include <tjg/color/styled_text.hpp>

#include <string_view>

namespace tjg::color {

/**
 * Decodes standard ESC[...m SGR into owned text spans. Consecutive sequences
 * update one style. The first reset starts an absolute group for subsequent
 * text; later resets clear styles within that group. Text before reset remains
 * relative. No unconditional absolute root is imposed.
 * Text and non-SGR escapes are retained
 * verbatim. Malformed SGR is retained atomically; unknown valid parameters are
 * ignored. This parses appearance, not an exact escape-byte round trip.
 */
[[nodiscard]] auto parse_styled_text(std::string_view input) -> styled_text;
[[nodiscard]] auto parse_styled_text(std::wstring_view input) -> wstyled_text;

template<CharType Char>
[[nodiscard]] auto parse_styled_text(std::basic_string_view<Char> input)
  -> basic_styled_text<Char>
{ return parse_styled_text(input); }

} // tjg::color
