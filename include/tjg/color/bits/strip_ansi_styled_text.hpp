/// @file
/// Remove syntactically complete ESC-prefixed ANSI control sequences from
/// `styled_text`.
/// @copyright 2026 Terry Golubiewski, all rights reserved.

#pragma once

#include <tjg/color/styled_text.hpp>

#include <string>
#include <string_view>

namespace tjg::color {

namespace detail {

void strip_styled_ansi(styled_text& text);
void strip_styled_ansi(wstyled_text& text);

} // detail

/**
 * Returns an owning copy with ANSI sequences removed independently from each
 * leaf. Preserves all node styles, absolute boundaries, and tree structure,
 * including leaves that become empty. Sequences spanning leaves are retained.
 * Does not modify the input; unchanged leaf strings remain shared.
 */
template<CharType Char>
[[nodiscard]]
auto strip_ansi(basic_styled_text<Char> input) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> basic_styled_text<Char>
{
  detail::strip_styled_ansi(input);
  return input;
}

} // tjg::color
