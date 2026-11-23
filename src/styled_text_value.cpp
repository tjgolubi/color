/// @copyright 2026 Terry Golubiewski, all rights reserved.
#include <tjg/color/styled_text.hpp>
#include <tjg/color/bits/strip_ansi-style_text.hpp>
#include <tjg/strip_ansi.hpp>

namespace tjg::color {

template<CharType Char>
void basic_styled_text<Char>::append_plain_text(string_type& result) const {
  if (_text) result.append(*_text);
  for (const auto& child : _children)
    child.append_plain_text(result);
}

template<CharType Char>
auto basic_styled_text<Char>::overlay(const text_style& overrides) noexcept
  -> basic_styled_text&
{
  if (_style.is_absolute()) return *this;
  _style.overlay(overrides);
  for (auto& child : _children)
    child.overlay(overrides);
  return *this;
}

template<CharType Char>
auto basic_styled_text<Char>::plain_text() const -> string_type {
  auto result = string_type{};
  append_plain_text(result);
  return result;
}

template<CharType Char>
auto basic_styled_text<Char>::operator+=(basic_styled_text rhs)
  -> basic_styled_text&
{
  if (rhs.empty()) return *this;
  if (empty()) return *this = std::move(rhs);
  if (!_children.empty() && _style.empty()) {
    _children.push_back(std::move(rhs));
    return *this;
  }
  auto children = branch{};
  // Allocate before moving either operand. The following moves cannot throw.
  children.reserve(2);
  children.push_back(std::move(*this));
  children.push_back(std::move(rhs));
  _children = std::move(children);
  return *this;
}

template void basic_styled_text<char>::append_plain_text(std::string&) const;

template
auto basic_styled_text<char>::overlay(const text_style&) noexcept
  -> styled_text&;

template auto basic_styled_text<char>::plain_text() const -> std::string;

template auto basic_styled_text<char>::operator+=(styled_text) -> styled_text&;

template
void basic_styled_text<wchar_t>::append_plain_text(std::wstring&) const;

template
auto basic_styled_text<wchar_t>::overlay(const text_style&) noexcept
  -> wstyled_text&;

template auto basic_styled_text<wchar_t>::plain_text() const -> std::wstring;

template
auto basic_styled_text<wchar_t>::operator+=(wstyled_text) -> wstyled_text&;

namespace detail {

struct styled_text_ansi_stripper {

  template<CharType Char>
  static void strip(basic_styled_text<Char>& text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  {
    if (!text._children.empty()) {
      for (auto& child : text._children)
        strip(child);
    } else if (text._text) {
      auto stripped =
              tjg::strip_ansi<Char>(std::basic_string_view<Char>{*text._text});
      if (stripped == *text._text)
        return;
      if (stripped.empty()) {
        text._text.reset();
      } else {
        text._text =
          std::make_shared<const std::basic_string<Char>>(std::move(stripped));
      }
    }
  }
}; // styled_text_ansi_stripper

void strip_styled_ansi(styled_text& text)
{ styled_text_ansi_stripper::strip(text); }

void strip_styled_ansi(wstyled_text& text)
{ styled_text_ansi_stripper::strip(text); }

} // detail

} // tjg::color
