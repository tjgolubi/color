/// @copyright 2026 Terry Golubiewski, all rights reserved.
#include <tjg/color/styled_text.hpp>
#include <tjg/color/bits/unicode.hpp>
#include <tjg/strip_ansi.hpp>
#include "WrapData.hpp"

#include <algorithm>
#include <stdexcept>
#include <type_traits>

#include <cstdint>

namespace tjg::color::detail {
namespace {

template<std::size_t N>
auto contains(const wrap_range (&ranges)[N], std::uint32_t value) noexcept
  -> bool
{
  const auto it = std::lower_bound(std::begin(ranges), std::end(ranges), value,
    [](const wrap_range& range, std::uint32_t cp) { return range.last < cp; });
  return it != std::end(ranges) && it->first <= value;
}

template<CharType Char>
auto decode(std::basic_string_view<Char> text) noexcept
  -> unicode::utf8_character
{
  if constexpr (std::is_same_v<Char, char>) {
    return unicode::decode_utf8(text);
  } else {
    auto cp = static_cast<std::uint32_t>(text.front());
    if constexpr (sizeof(Char) == 2) {
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
} // decode

enum class token_kind {
  text, space, no_break_space, newline, punctuation, ideographic
};

constexpr auto is_space(token_kind kind) noexcept -> bool {
  return kind == token_kind::space || kind == token_kind::no_break_space;
}

struct token {
  std::size_t offset, size;
  std::size_t columns;
  token_kind kind;
  bool soft_hyphen_after = false;
};

struct line_range {
  std::size_t begin, end;
  bool hyphen{false};
};

// Each punctuation-delimited word is inspected once. Prefix sums avoid
// rescanning the remainder of an oversized word after each hyphenation.
auto select_lines(const std::vector<token>& tokens, std::size_t width,
                  std::size_t indent)
    TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> std::vector<line_range>
{
  auto sums = std::vector<std::size_t>{0};
  sums.reserve(tokens.size() + 1);
  for (const auto& t : tokens)
    sums.push_back(sums.back() + t.columns);
  auto lines = std::vector<line_range>{};
  auto limit = width;
  const auto continuation_limit = width - indent;

  auto emit = [&](std::size_t begin, std::size_t end, bool hyphen = false) {
    while (end > begin && is_space(tokens[end - 1].kind))
      --end;
    lines.push_back({begin, end, hyphen});
    limit = continuation_limit;
  }; // emit

  for (std::size_t paragraph = 0; paragraph < tokens.size();) {
    auto end = paragraph;
    while (end < tokens.size() && tokens[end].kind != token_kind::newline)
      ++end;
    auto begin = paragraph;
    auto pos = begin;
    auto columns = std::size_t{0};
    auto has_text = false;
    while (pos < end) {
      if (is_space(tokens[pos].kind)) {
        ++columns;
        ++pos;
        continue;
      }
      auto word_end = pos;
      auto has_no_break_space = false;
      do {
        has_no_break_space |= tokens[word_end].kind == token_kind::no_break_space;
        ++word_end;
      } while (word_end < end
            && tokens[word_end].kind != token_kind::space
            && (tokens[word_end - 1].kind != token_kind::punctuation
                || tokens[word_end].kind == token_kind::no_break_space));

      while (pos < word_end) {
        const auto word_width = sums[word_end] - sums[pos];
        if (columns <= limit && word_width <= limit - columns) {
          columns += word_width;
          pos = word_end;
          has_text = true;
        } else if (word_width <= limit || columns >= limit) {
          // A fitting word moves intact; separating spaces are consumed.
          // Excess leading indentation also ends at this wrap boundary.
          if (has_text)
            emit(begin, pos);
          begin = pos;
          columns = 0;
          has_text = false;
        } else {
          const auto available = limit - columns;
          auto cut = pos;
          auto preferred = pos;
          auto separator = pos;
          auto hyphen = true;
          for (auto next = pos + 1; next < word_end; ++next) {
            const auto width = sums[next] - sums[pos];
            if (width > available)
              break;
            const auto& before = tokens[next - 1];
            if (tokens[next].kind == token_kind::no_break_space) {
              if (before.kind != token_kind::no_break_space)
                separator = next;
              continue;
            }
            if (width < available) {
              cut = next;
              if (before.soft_hyphen_after) {
                preferred = next;
                hyphen = true;
                continue;
              }
            }
            if (before.kind == token_kind::ideographic
                && tokens[next].kind == token_kind::ideographic) {
              preferred = next;
              hyphen = false;
            }
          }
          auto consume_separator = false;
          if (preferred != pos) {
            cut = preferred;
          } else if (has_text && has_no_break_space) {
            // Use the preceding break before splitting a no-break group.
            cut = pos;
          } else if (separator != pos) {
            cut = separator;
            hyphen = false;
            consume_separator = true;
          }
          if (cut == pos) {
            if (has_text)
              emit(begin, pos);
            begin = pos;
          } else {
            emit(begin, cut, hyphen);
            pos = cut;
            if (consume_separator) {
              while (pos < word_end && tokens[pos].kind == token_kind::no_break_space)
                ++pos;
            }
            begin = pos;
          }
          columns = 0;
          has_text = false;
        }
      }
    }
    emit(begin, end);
    paragraph = end < tokens.size() ? end + 1 : end;
  }
  while (!lines.empty() && lines.back().begin == lines.back().end)
    lines.pop_back();
  return lines;
} // select_lines

} // local

struct styled_text_word_wrapper {
  template<CharType Char>
  struct record {
    const basic_styled_text<Char>* source;
    std::size_t begin, end;
    std::vector<std::size_t> children;
    std::basic_string<Char> text;
  };

  template<CharType Char>
  static void tokenize(record<Char>& leaf, std::vector<token>& tokens)
    TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  {
    if (!leaf.source->_text)
      return;
    const auto stripped = tjg::strip_ansi<Char>(*leaf.source->_text);
    const auto view = std::basic_string_view<Char>{stripped};
    for (std::size_t pos = 0; pos < view.size(); ) {
      const auto cp = decode(view.substr(pos));
      const auto source = view.substr(pos, cp.size);
      pos += cp.size;
      if (cp.value == 0x00ad) {
        // Record the break on the preceding character, even across spans.
        if (!tokens.empty() && !is_space(tokens.back().kind)
                            && tokens.back().kind != token_kind::newline)
          tokens.back().soft_hyphen_after = true;
        continue;
      }
      auto kind = token_kind::text;
      if (cp.value == '\n')
        kind = token_kind::newline;
      else if (cp.value == 0x00a0)
        kind = token_kind::no_break_space;
      else if (contains(wrap_spaces, cp.value))
        kind = token_kind::space;
      else if (cp.value < 0x20 || (cp.value >= 0x7f && cp.value <= 0x9f)) {
        continue;
      } else if (contains(wrap_punctuation, cp.value)) {
        kind = token_kind::punctuation;
      } else if (cp.value >= wrap_ideographic[0].first
                 && contains(wrap_ideographic, cp.value)) {
        kind = token_kind::ideographic;
      }
      const auto offset = leaf.text.size();
      if (kind == token_kind::space)
        leaf.text.push_back(Char{' '});
      else
        leaf.text.append(source);
      const auto columns = kind == token_kind::newline ? 0
                         : kind == token_kind::space   ? 1
                         : unicode::display_width_of(cp.value);
      tokens.push_back({offset, leaf.text.size() - offset, columns, kind});
    }
  }

  template<CharType Char>
  static auto collect(const basic_styled_text<Char>& text,
                      std::vector<token>& tokens) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
    -> std::vector<record<Char>>
  {
    auto records = std::vector<record<Char>>{{&text, 0, 0, {}, {}}};
    struct frame { std::size_t node, next; };
    auto stack = std::vector<frame>{{0, 0}};
    while (!stack.empty()) {
      const auto id = stack.back().node;
      const auto& children = records[id].source->_children;
      if (children.empty())
        tokenize(records[id], tokens);
      if (stack.back().next == children.size()) {
        records[id].end = tokens.size();
        stack.pop_back();
      } else {
        const auto* child = &children[stack.back().next++];
        const auto child_id = records.size();
        records[id].children.push_back(child_id);
        records.push_back({child, tokens.size(), tokens.size(), {}, {}});
        stack.push_back({child_id, 0});
      }
    }
    return records;
  } // collect

  template<CharType Char>
  static auto reconstruct(const std::vector<record<Char>>& records,
                          const std::vector<token>& tokens, line_range line,
                          std::size_t indent)
    TJG_NOEXCEPT_UNLESS_BAD_ALLOC -> basic_styled_text<Char>
  {
    auto result = basic_styled_text<Char>{};
    if (line.begin == line.end) {
      // Field padding uses the root style even when the line has no text.
      result._style = records.front().source->_style;
      return result;
    }
    struct frame { std::size_t node; basic_styled_text<Char>* output; };
    auto stack = std::vector<frame>{{0, &result}};
    while (!stack.empty()) {
      const auto [id, output] = stack.back();
      stack.pop_back();
      const auto& node = records[id];
      output->_style = node.source->_style;
      const auto prefix = id == 0 ? indent : 0;
      if (node.children.empty()) {
        const auto begin = std::max(line.begin, node.begin);
        const auto end = std::min(line.end, node.end);
        if (begin == end)
          continue;
        const auto offset = tokens[begin].offset;
        const auto& last = tokens[end - 1];
        auto text = node.text.substr(offset, last.offset + last.size - offset);
        if (prefix != 0)
          text.insert(0, prefix, Char{' '});
        if (line.hyphen && end == line.end)
          text.push_back(Char{'-'});
        output->_text =
          std::make_shared<const std::basic_string<Char>>(std::move(text));
      } else {
        // Skip unrelated subtrees without rescanning earlier siblings for
        // each line. Output vectors are sized before retaining pointers.
        const auto first = std::lower_bound(
          node.children.begin(), node.children.end(), line.begin,
          [&](std::size_t child, std::size_t pos) {
            return records[child].end <= pos;
          });
        const auto last = std::lower_bound(
          first, node.children.end(), line.end,
          [&](std::size_t child, std::size_t pos) {
            return records[child].begin < pos;
          });
        const auto first_child = prefix == 0 ? 0u : 1u;
        const auto count = static_cast<std::size_t>(last - first);
        output->_children.resize(first_child + count);
        if (prefix != 0)
          output->_children.front() = basic_styled_text<Char>{
            std::basic_string<Char>(prefix, Char{' '})};
        for (auto it = first; it != last; ++it) {
          const auto index = first_child + static_cast<std::size_t>(it - first);
          stack.push_back({*it, &output->_children[index]});
        }
      }
    }
    return result;
  } // reconstruct

  template<CharType Char>
  static auto wrap(const basic_styled_text<Char>& text, std::size_t width,
                   std::size_t indent, bool materialize_indent)
    -> std::vector<basic_styled_text<Char>>
  {
    if (width < min_wrap_width)
      TJG_THROW(std::invalid_argument{"word_wrap: width must be at least 4"});
    if (indent > width - min_wrap_width)
      TJG_THROW(std::invalid_argument{
        "word_wrap: width minus indent must be at least 4"});
    auto tokens = std::vector<token>{};
    const auto records = collect(text, tokens);
    const auto lines = select_lines(tokens, width, indent);
    auto result = std::vector<basic_styled_text<Char>>{};
    result.reserve(lines.size());
    for (const auto line : lines) {
      const auto prefix = materialize_indent && !result.empty() ? indent : 0;
      result.push_back(reconstruct(records, tokens, line, prefix));
    }
    return result;
  }
}; // styled_text_word_wrapper

// The formatter adds the indent before its alignment padding.
auto wrap_for_formatting(const styled_text& text, std::size_t width,
                         std::size_t indent) -> std::vector<styled_text>
{
  return styled_text_word_wrapper::wrap(text, width, indent, false);
}

} // tjg::color::detail

namespace tjg::color {

auto word_wrap(const styled_text& text, std::size_t width, std::size_t indent)
  -> std::vector<styled_text>
{ return detail::styled_text_word_wrapper::wrap(text, width, indent, true); }

auto word_wrap(const wstyled_text& text, std::size_t width, std::size_t indent)
  -> std::vector<wstyled_text>
{ return detail::styled_text_word_wrapper::wrap(text, width, indent, true); }

} // tjg::color
