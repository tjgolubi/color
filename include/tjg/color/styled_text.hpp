/// @file
/// Owned structured styled text.
/// @copyright 2026 Terry Golubiewski, all rights reserved.
#pragma once

#include <tjg/color/text_style.hpp>
#include <tjg/utility.hpp>

#include <string>
#include <string_view>

#include <vector>
#include <memory>

#include <concepts>
#include <utility>

#include <cstddef>

namespace tjg::color {

namespace detail {

struct styled_text_ansi_stripper;
struct styled_text_word_wrapper;
inline constexpr std::size_t min_wrap_width = 4;
template<CharType Char> class styled_text_renderer;
template<CharType Char> class tagged_parser;

} // detail

/// An owned string or sequence of styled children, with a style for this node.
template<CharType Char>
class basic_styled_text {
public:
  using char_type   = Char;
  using string_type = std::basic_string<Char>;
  using view_type   = std::basic_string_view<Char>;

private:
  using leaf   = std::shared_ptr<const string_type>;
  using branch = std::vector<basic_styled_text>;
  friend class detail::styled_text_renderer<Char>;
  friend struct detail::styled_text_ansi_stripper;
  friend struct detail::styled_text_word_wrapper;
  friend class detail::tagged_parser<Char>;

  text_style _style{};
  leaf       _text{};
  branch     _children{}; // A node is a leaf when this is empty.

  void append_plain_text(string_type& result) const;

 public:
  constexpr basic_styled_text() noexcept = default;

  basic_styled_text(string_type text, const text_style& style = {})
    TJG_NOEXCEPT_UNLESS_BAD_ALLOC
    : _style{style}
    , _text{text.empty() ? leaf{}
                         : std::make_shared<const string_type>(std::move(text))}
    {}

  basic_styled_text(const Char* text, const text_style& style = {})
    : basic_styled_text{string_type{text}, style} {}

  basic_styled_text(const basic_styled_text&) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
    = default;

  basic_styled_text(basic_styled_text&& other) noexcept
    : _style{std::exchange(other._style, text_style{})}
    , _text{std::move(other._text)}
    , _children{std::move(other._children)}
  {
    other._children.clear();
  }

  auto operator=(const basic_styled_text& other) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
    -> basic_styled_text&
  {
    if (this == &other) return *this;
    auto copy = basic_styled_text{other};
    return *this = std::move(copy);
  }

  auto operator=(basic_styled_text&& other) noexcept -> basic_styled_text& {
    if (this == &other) return *this;
    _style    = std::exchange(other._style, text_style{});
    _text     = std::move(other._text);
    _children = std::move(other._children);
    return *this;
  }

  constexpr auto style() const noexcept -> text_style { return _style; }

  constexpr auto style(text_style value) noexcept -> basic_styled_text& {
    _style = value;
    return *this;
  }

  /**
   * Applies `overrides` recursively in place, skipping absolute nodes and
   * their entire subtrees. Preserves text and tree structure. Specified
   * colors replace matching channels; emphasis attributes are combined.
   * Returns this node for chaining.
   * To overlay only this node, use style(style().overlay(overrides)).
   */
  auto overlay(text_style overrides) noexcept -> basic_styled_text&;

  /**
   * Underlays this node's style in place, leaving its text and children intact.
   * Specified colors replace unspecified matching channels; emphasis attributes
   * are combined. Returns a reference to this node for chaining.
   */
  constexpr auto underlay(text_style style) noexcept -> basic_styled_text& {
    _style.underlay(style);
    return *this;
  }

  // Empty leaves are concatenation identities.
  auto empty() const noexcept -> bool { return _children.empty() && !_text; }

  /**
   * Returns an independent string containing all leaf text in order, without
   * applying styles. Preserves embedded nulls and escapes without interpreting
   * them. Does not modify this value. Allocation can throw.
   */
  [[nodiscard]] auto plain_text() const -> string_type;

  auto operator+=(basic_styled_text rhs) -> basic_styled_text&; // operator+=

  friend
  bool operator==(const basic_styled_text& lhs, const basic_styled_text& rhs)
    noexcept
  {
    if (lhs._style != rhs._style || lhs._children != rhs._children)
      return false;
    return lhs._text == rhs._text
        || (lhs._text && rhs._text && *lhs._text == *rhs._text);
  }

  friend
  bool operator!=(const basic_styled_text& lhs, const basic_styled_text& rhs)
    noexcept
  { return !(lhs == rhs); }

  friend auto operator+(basic_styled_text lhs, basic_styled_text rhs)
    -> basic_styled_text
  {
    lhs += std::move(rhs);
    return lhs;
  }
}; // basic_styled_text

using styled_text  = basic_styled_text<char>;
using wstyled_text = basic_styled_text<wchar_t>;

/**
 * Parses inline color and emphasis markup into styled text. Supports named
 * and shorthand style tags, Markdown-like emphasis on a single line, and
 * backtick-delimited literal text. Preserves unknown tags, malformed markup,
 * and unrecognized escapes.
 * The `absolute` keyword starts a style scope from the terminal defaults.
 */
[[nodiscard]]
auto tagged(std::string_view text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> styled_text;

/// Parses wide inline markup using the same grammar as the narrow overload.
[[nodiscard]]
auto tagged(std::wstring_view text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> wstyled_text;

/// Parses inline markup with an explicitly selectable character type.
template<CharType Char>
[[nodiscard]] auto tagged(std::basic_string_view<Char> text)
    TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> basic_styled_text<Char>;

/**
 * Wraps text into unpadded display lines, preserving nested and absolute styles.
 * Width must be at least 4; otherwise throws std::invalid_argument, even for
 * empty input. Prepends `indent` spaces to each nonblank line after the first.
 * Indentation counts toward `width`, and `width - indent` must be at least 4.
 * Leaves the input unchanged. Removes ANSI sequences per span,
 * normalizes whitespace except newlines and no-break spaces (U+00A0), and
 * discards remaining C0/C1 controls. Newlines force breaks. Trailing whitespace
 * and trailing blank lines are removed.
 * Breaks after eligible Unicode punctuation or at whitespace. For oversized
 * words, a soft hyphen marks a preferred split and becomes a styled ASCII
 * hyphen when used. Breaks between ideographic characters need no hyphen.
 * If no preferred break fits, an oversized word can split at a no-break space
 * and consume it without adding a hyphen.
 * Falls back to splitting at a decoded character boundary with an ASCII hyphen.
 * Uses the UTF-8 formatter's one/two-column model for both character types;
 * malformed code units are preserved and count as one column each.
 */
[[nodiscard]]
auto word_wrap(const styled_text& text, std::size_t width, std::size_t indent = 0)
  -> std::vector<styled_text>;

/// Wide-character overload; decodes UTF-16 or UTF-32 independently per span.
[[nodiscard]]
auto word_wrap(const wstyled_text& text, std::size_t width, std::size_t indent = 0)
  -> std::vector<wstyled_text>;

namespace detail {

template<CharType Char>
auto to_styled_text(basic_styled_text<Char> text) -> basic_styled_text<Char>
{ return text; }

template<typename S,
          CharType Char = typename decltype(std::basic_string_view{
              std::declval<S&>()})::value_type>
  requires std::constructible_from<basic_styled_text<Char>, S&&>
auto to_styled_text(S&& text) -> basic_styled_text<Char>
{ return basic_styled_text<Char>{std::forward<S>(text)}; }

} // detail

/**
 * Returns styled text with `overrides` applied recursively, skipping absolute
 * nodes and their entire subtrees. Specified colors replace matching channels;
 * Emphasis attributes are combined. Accepts styled text, character strings,
 * and std::basic_string. String
 * inputs become owned leaves. Styled-text lvalues copy their structure;
 * rvalues move it. Only the returned value is modified.
 */
template<typename T>
[[nodiscard]] auto overlay(text_style overrides, T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{
  auto result = detail::to_styled_text(std::forward<T>(text));
  result.overlay(overrides);
  return result;
}

/**
 * Returns styled text with `style` underlaid on its root. Accepts styled text,
 * character strings, and std::basic_string. String inputs become owned leaves.
 * Styled-text lvalues copy their structure; rvalues move it. Children retain
 * their styles. Only the returned value is modified.
 */
template<typename T>
[[nodiscard]] auto underlay(text_style style, T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{
  auto result = detail::to_styled_text(std::forward<T>(text));
  result.underlay(style);
  return result;
}

/**
 * Returns styled text with an absolute root, preserving its style and children.
 * Accepts the same owning text inputs as overlay. Lvalues copy; rvalues move.
 * Only the returned value is modified.
 */
template<typename T>
[[nodiscard]] auto absolute(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::absolute(text_style{}), std::forward<T>(text)); }

/// Returns styled text with bold enabled on its root, preserving other style.
template<typename T>
[[nodiscard]] auto bold(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::bold(), std::forward<T>(text)); }

/// Returns styled text with faint enabled on its root, preserving other style.
template<typename T>
[[nodiscard]] auto faint(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::faint(), std::forward<T>(text)); }

/// Returns styled text with italic enabled on its root, preserving other style.
template<typename T>
[[nodiscard]] auto italic(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::italic(), std::forward<T>(text)); }

/// Enables underline on the returned root, preserving its other style.
template<typename T>
[[nodiscard]] auto underline(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::underline(), std::forward<T>(text)); }

/// Returns styled text with blink enabled on its root, preserving other style.
template<typename T>
[[nodiscard]] auto blink(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::blink(), std::forward<T>(text)); }

/// Enables reverse on the returned root, preserving its other style.
template<typename T>
[[nodiscard]] auto reverse(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::reverse(), std::forward<T>(text)); }

/// Enables conceal on the returned root, preserving its other style.
template<typename T>
[[nodiscard]] auto conceal(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::conceal(), std::forward<T>(text)); }

/// Returns styled text with strike enabled on its root, preserving other style.
template<typename T>
[[nodiscard]] auto strike(T&& text)
  -> decltype(detail::to_styled_text(std::forward<T>(text)))
{ return tjg::color::underlay(tjg::color::strike(), std::forward<T>(text)); }

} // tjg::color
