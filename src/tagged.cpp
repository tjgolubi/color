/// @copyright 2026 Terry Golubiewski, all rights reserved.
#include <tjg/color/styled_text.hpp>

#include "WrapData.hpp"
#include "unicode_scalar.hpp"

#include <algorithm>
#include <optional>

namespace tjg::color::detail {
namespace {

template<CharType Char>
constexpr auto matches(std::basic_string_view<Char> text,
                       std::string_view name) noexcept -> bool
{
  return std::ranges::equal(text, name);
}

constexpr auto tag_space(auto ch) noexcept -> bool {
  return ch == ' ' || ch == '\t';
}

template<CharType Char>
constexpr void skip_space(std::basic_string_view<Char>& text) noexcept {
  while (!text.empty() && tag_space(text.front()))
    text.remove_prefix(1);
}

template<CharType Char>
constexpr auto take_word(std::basic_string_view<Char>& text) noexcept
  -> std::basic_string_view<Char>
{
  if (text.empty()) return {};
  const auto end = std::ranges::find_if(text, [](Char ch) {
    return tag_space(ch) || ch == '=' || ch == ',' || ch == '|';
  });
  const auto word = text.substr(0, static_cast<std::size_t>(end - text.begin()));
  text.remove_prefix(word.size());
  skip_space(text);
  return word;
}

constexpr auto ascii_letter(auto ch) noexcept -> bool {
  return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

template<CharType Char>
constexpr auto is_tag_name(std::basic_string_view<Char> text) noexcept -> bool {
  return !text.empty() && ascii_letter(text.front())
      && std::ranges::all_of(text, [](Char ch) {
           return ascii_letter(ch) || (ch >= '0' && ch <= '9')
               || ch == '_' || ch == '-';
         });
}

constexpr auto hex_digit(auto ch) noexcept -> int {
  if (ch >= '0' && ch <= '9') return static_cast<int>(ch - '0');
  if (ch >= 'a' && ch <= 'f') return static_cast<int>(ch - 'a' + 10);
  if (ch >= 'A' && ch <= 'F') return static_cast<int>(ch - 'A' + 10);
  return -1;
}

template<CharType Char>
constexpr auto read_hex(std::basic_string_view<Char> text) noexcept
  -> std::optional<std::uint32_t>
{
  std::uint32_t value = 0;
  for (const auto ch : text) {
    const auto digit = hex_digit(ch);
    if (digit < 0) return std::nullopt;
    value = (value << 4) | static_cast<std::uint32_t>(digit);
  }
  return value;
}

template<CharType Char>
auto apply_attribute(std::basic_string_view<Char> name, text_style& style,
                     bool allow_short = false) noexcept -> bool
{
  if (matches(name, "absolute")) {
    style.absolute();
    return true;
  }
  struct entry { std::string_view name, short_name; emphasis value; };
  using enum emphasis;
  static constexpr entry attributes[] = {
    {"bold", "b", bold}, {"faint", {}, faint}, {"italic", "i", italic},
    {"underline", "u", underline}, {"blink", {}, blink},
    {"reverse", {}, reverse}, {"conceal", {}, conceal}, {"strike", "s", strike}
  };
  for (const auto& e : attributes) {
    if (matches(name, e.name)
        || (allow_short && !e.short_name.empty() && matches(name, e.short_name))) {
      style.emph(style.emph() | e.value);
      return true;
    }
  }
  return false;
}

struct rgb_entry { std::string_view name; rgb value; };
constexpr rgb_entry rgb_names[] = {
#include "TaggedColors.inc"
};

template<CharType Char>
auto color_named(std::basic_string_view<Char> name) noexcept
  -> std::optional<color_t>
{
  if (name.empty()) return std::nullopt;
  if (name.front() == '#') {
    if (name.size() == 7)
      if (const auto value = read_hex(name.substr(1)))
        return rgb{*value};
    return std::nullopt;
  }
  if (matches(name.substr(0, 5), "term_")) {
    for (int i = 0; i < 16; ++i) {
      const auto value = static_cast<term_color>(i);
      if (matches(name.substr(5), name_of(value))) return value;
    }
    return std::nullopt;
  }
  const auto found = std::ranges::lower_bound(rgb_names, name,
    [](auto lhs, auto rhs) {
      return std::lexicographical_compare(lhs.begin(), lhs.end(),
                                          rhs.begin(), rhs.end());
    }, &rgb_entry::name);
  if (found != std::end(rgb_names) && matches(name, found->name))
    return found->value;
  return std::nullopt;
}

template<CharType Char>
auto parse_attributes(std::basic_string_view<Char> text) noexcept
  -> std::optional<text_style>
{
  auto style = text_style{};
  for (;;) {
    if (!apply_attribute(take_word(text), style)) return std::nullopt;
    if (text.empty()) return style;
    if (text.front() != '|' && text.front() != ',') return std::nullopt;
    text.remove_prefix(1);
    skip_space(text);
  }
}

template<CharType Char>
auto parse_colors(std::basic_string_view<Char> text, bool named) noexcept
  -> std::optional<text_style>
{
  auto style = text_style{};
  auto seen_on = false;
  while (!text.empty()) {
    if (named && text.front() == ',') {
      text.remove_prefix(1);
      skip_space(text);
      if (!matches(take_word(text), "absolute") || !text.empty())
        return std::nullopt;
      style.absolute();
      break;
    }
    const auto name = take_word(text);
    if (matches(name, "on")) {
      if (seen_on) return std::nullopt;
      seen_on = true;
    } else if (!apply_attribute(name, style)) {
      const auto color = color_named(name);
      if (!color) return std::nullopt;
      if (seen_on) {
        if (style.has_bg()) return std::nullopt;
        style.bg(*color);
      } else {
        if (style.has_fg()) return std::nullopt;
        style.fg(*color);
      }
    }
  }
  if (seen_on && !style.has_bg()) return std::nullopt;
  if (!seen_on && !style.has_fg() && (named || !style.is_absolute()))
    return std::nullopt;
  return style;
}

constexpr auto word_character(std::uint32_t cp) noexcept -> bool {
  if (cp < 0x80) return ascii_letter(cp) || (cp >= '0' && cp <= '9');
  return unicode::contains(word_characters, cp);
}

template<CharType Char>
void append_scalar(std::basic_string<Char>& text, std::uint32_t cp) {
  const auto append = [&](std::uint32_t unit) {
    text.push_back(static_cast<Char>(unit));
  };
  if constexpr (std::same_as<Char, char>) {
    if (cp < 0x80) {
      append(cp);
    } else {
      const auto count = cp < 0x800 ? 1 : cp < 0x10000 ? 2 : 3;
      constexpr std::uint32_t lead[] = {0, 0xc0, 0xe0, 0xf0};
      append(lead[count] | (cp >> (6 * count)));
      for (auto shift = 6 * (count - 1); shift >= 0; shift -= 6)
        append(0x80 | ((cp >> shift) & 0x3f));
    }
  } else if constexpr (sizeof(Char) == 2) {
    if (cp >= 0x10000) {
      cp -= 0x10000;
      append(0xd800 | (cp >> 10));
      append(0xdc00 | (cp & 0x3ff));
    } else {
      append(cp);
    }
  } else {
    append(cp);
  }
}

} // namespace

template<CharType Char>
class tagged_parser {
  using view = std::basic_string_view<Char>;
  using styled_type = basic_styled_text<Char>;

  // Tentative openers stay in the text buffer. Only matched markers turn
  // them into styled groups, so recovery never needs to scan the input again.
  // Literal scopes share the nesting stack and need no output markers.
  struct marker {
    std::size_t offset, size;
    text_style style;
    bool matched;
  };
  struct scope {
    std::optional<std::size_t> marker_index;
    view name;
    emphasis delimiter;
    std::size_t line;
  };

  view _input;
  std::basic_string<Char> _text;
  std::vector<marker> _markers;
  std::vector<scope> _scopes;
  std::size_t _line = 0;

  void open(view literal, std::optional<text_style> style, view name = {},
            emphasis delimiter = emphasis::none)
  {
    auto index = std::optional<std::size_t>{};
    if (style) {
      index = _markers.size();
      _markers.push_back({_text.size(), literal.size(), *style, false});
    }
    _scopes.push_back({index, name, delimiter, _line});
    _text.append(literal);
  }

  void close(view literal = {}) {
    const auto index = _scopes.back().marker_index;
    _scopes.pop_back();
    if (index) {
      _markers[*index].matched = true;
      _markers.push_back({_text.size(), 0, {}, true});
    } else {
      _text.append(literal);
    }
  }

  void expire_shorthand() noexcept {
    // A named scope may still be active above a shorthand from a prior line.
    // Leave buried entries in place until they reach the top of the stack.
    while (!_scopes.empty() && _scopes.back().delimiter != emphasis::none
           && _scopes.back().line != _line)
      _scopes.pop_back();
  }

  void newline() {
    _text.push_back(Char{'\n'});
    ++_line;
  }

  static auto shorthand_name(view name) noexcept -> bool {
    return !name.empty() && (matches(name, "on") || name.front() == '#'
      || matches(name.substr(0, 5), "term_") || matches(name.substr(0, 6), "xterm_")
      || color_named(name).has_value());
  }

  void close_tag(view literal, view body) {
    const auto name = take_word(body);
    if (!body.empty()) {
      _text.append(literal);
      return;
    }
    const auto is_generic = name.empty();
    expire_shorthand();
    if (!_scopes.empty()
        && _scopes.back().delimiter == emphasis::none
        && (is_generic || _scopes.back().name == name)) {
      close(literal);
    } else {
      _text.append(literal);
    }
  }

  void open_tag(view literal, view body) {
    while (!body.empty() && tag_space(body.back())) body.remove_suffix(1);
    if (!body.empty() && body.back() == '/') {
      _text.append(literal);
      return;
    }
    const auto arguments = body;
    const auto name = take_word(body);
    if (matches(name, "br") && body.empty()) {
      newline();
      return;
    }
    const auto named_color = matches(name, "color");
    const auto named_emphasis = matches(name, "emphasis");
    auto standalone = text_style{};
    const auto is_attribute = apply_attribute(name, standalone, true);
    auto style = std::optional<text_style>{};
    auto close_name = name;
    if (named_color || named_emphasis) {
      if (!body.empty() && body.front() == '=') {
        body.remove_prefix(1);
        skip_space(body);
        style = named_color ? parse_colors(body, true) : parse_attributes(body);
      }
    } else if (is_attribute && body.empty()) {
      style = standalone;
    } else if (is_attribute || shorthand_name(name)) {
      style = parse_colors(arguments, false);
      if (style || !is_tag_name(name)) close_name = {};
    } else if (!is_tag_name(name)) {
      _text.append(literal);
      return;
    }
    open(literal, style, close_name);
  }

  auto tag(view text) -> std::size_t {
    if (text.size() < 2 || text[1] == '>' || tag_space(text[1])) return 0;
    std::size_t end = 1;
    auto quote = Char{};
    for (; end < text.size(); ++end) {
      const auto ch = text[end];
      if (ch == '<' || ch == '\n') return 0;
      if (quote != Char{}) {
        if (ch == quote) quote = Char{};
      } else if (ch == '>') {
        break;
      } else if (ch == '\'' || ch == '"') {
        quote = ch;
      }
    }
    if (end == text.size()) return 0;
    const auto literal = text.substr(0, end + 1);
    if (text[1] == '/') close_tag(literal, text.substr(2, end - 2));
    else open_tag(literal, text.substr(1, end - 1));
    return literal.size();
  }

  auto escape(view text) -> std::size_t {
    if (text.size() < 2) return 0;
    const auto ch = text[1];
    switch (ch) {
    case ' ': append_scalar(_text, 0x00a0); return 2;
    case '-': append_scalar(_text, 0x00ad); return 2;
    case '\\': case '<': case '>': case '*': case '_': case '~': case '`':
      _text.push_back(ch);
      return 2;
    case 'u': case 'U': {
      const std::size_t end = ch == 'u' ? 6 : 10;
      auto size = std::size_t{2};
      while (size < end && size < text.size() && hex_digit(text[size]) >= 0)
        ++size;
      const auto cp = size == end ? read_hex(text.substr(2, size - 2))
                                 : std::nullopt;
      if (!cp || *cp > 0x10ffff || (*cp >= 0xd800 && *cp <= 0xdfff))
        _text.append(text.substr(0, size));
      else if (*cp == '\n')
        newline();
      else
        append_scalar(_text, *cp);
      return size;
    }
    default: return 0;
    }
  }

  auto literal(view text) -> std::size_t {
    const auto end = text.find(Char{'`'}, 1);
    if (end == view::npos) return 0;
    const auto content = text.substr(1, end - 1);
    if (content.find(Char{'\n'}) != view::npos) ++_line;
    _text.append(content);
    return end + 1;
  }

  auto word_before(std::size_t pos) const noexcept -> bool {
    if (pos == 0) return false;
    auto start = pos - 1;
    if constexpr (std::same_as<Char, char>) {
      while (start != 0 && pos - start < 4
             && (static_cast<unsigned char>(_input[start]) & 0xc0) == 0x80)
        --start;
    } else if constexpr (sizeof(Char) == 2) {
      const auto unit = static_cast<std::uint32_t>(_input[start]);
      if (start != 0 && unit >= 0xdc00 && unit <= 0xdfff) --start;
    }
    const auto cp = unicode::decode(_input.substr(start, pos - start));
    return cp.size == pos - start && word_character(cp.value);
  }

  auto delimiter(view text, std::size_t pos) -> std::size_t {
    const auto ch = text.front();
    std::size_t size = 1;
    while (size < text.size() && text[size] == ch) ++size;
    const auto mark = text.substr(0, size);
    auto kind = emphasis::none;
    if (ch == '*' && size <= 2)
      kind = size == 1 ? emphasis::italic : emphasis::bold;
    else if (ch == '_' && size == 1)
      kind = emphasis::underline;
    else if (ch == '~' && size == 2)
      kind = emphasis::strike;
    if (kind == emphasis::none) {
      _text.append(mark);
      return size;
    }
    expire_shorthand();
    const auto can_close = size == text.size()
      || !word_character(unicode::decode(text.substr(size)).value);
    if (can_close && !_scopes.empty() && _scopes.back().delimiter == kind)
      close();
    else if (!word_before(pos))
      open(mark, text_style{}.emph(kind), {}, kind);
    else
      _text.append(mark);
    return size;
  }

  static auto finish_group(styled_type group) noexcept -> styled_type {
    if (group._children.size() == 1) {
      auto& child = group._children.front();
      if (group._style.empty()) return std::move(child);
      if (child._style.empty()) {
        child._style = group._style;
        return std::move(child);
      }
    }
    return group;
  }

  auto styled_result() -> styled_type {
    if (_markers.empty()) return styled_type{std::move(_text)};
    auto groups = std::vector<styled_type>(1);
    auto pos = std::size_t{0};
    const auto append_to = [&](std::size_t end) {
      if (pos != end)
        groups.back()._children.emplace_back(_text.substr(pos, end - pos));
    };
    for (const auto& m : _markers) {
      if (!m.matched) continue;
      append_to(m.offset);
      pos = m.offset + m.size;
      if (m.size != 0) {
        groups.emplace_back();
        groups.back()._style = m.style;
      } else {
        auto group = finish_group(std::move(groups.back()));
        groups.pop_back();
        if (!group.empty()) groups.back()._children.push_back(std::move(group));
      }
    }
    append_to(_text.size());
    return finish_group(std::move(groups.front()));
  }

public:
  explicit tagged_parser(view text) noexcept : _input{text} {}

  auto parse() -> styled_type {
    _text.reserve(_input.size());
    for (std::size_t pos = 0; pos < _input.size();) {
      const auto text = _input.substr(pos);
      std::size_t consumed = 0;
      switch (text.front()) {
      case '<': consumed = tag(text); break;
      case '\\': consumed = escape(text); break;
      case '`': consumed = literal(text); break;
      case '*': case '_': case '~': consumed = delimiter(text, pos); break;
      case '\n': newline(); consumed = 1; break;
      default: break;
      }
      if (consumed == 0) {
        _text.push_back(text.front());
        consumed = 1;
      }
      pos += consumed;
    }
    return styled_result();
  }
}; // tagged_parser

} // tjg::color::detail

namespace tjg::color {

template<CharType Char>
auto tagged(std::basic_string_view<Char> text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> basic_styled_text<Char>
{
  return detail::tagged_parser<Char>{text}.parse();
}

template auto tagged<char>(std::string_view) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> styled_text;
template auto tagged<wchar_t>(std::wstring_view) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> wstyled_text;

auto tagged(std::string_view text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> styled_text
{
  return tagged<char>(text);
}

auto tagged(std::wstring_view text) TJG_NOEXCEPT_UNLESS_BAD_ALLOC
  -> wstyled_text
{
  return tagged<wchar_t>(text);
}

} // tjg::color
