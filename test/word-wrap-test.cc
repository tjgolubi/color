#include <tjg/color/styled_text.hpp>
#include <tjg/color.hpp>
#include "test-support.h"

#include <format>
#include <limits>
#include <stdexcept>
#include <type_traits>

#include <cstdint>

namespace {
using namespace tjg::color;

template<typename Char>
auto ascii(std::string_view value) -> std::basic_string<Char> {
  return {value.begin(), value.end()};
}

template<typename Char>
auto encoded(std::u32string_view value) -> std::basic_string<Char> {
  auto result = std::basic_string<Char>{};
  for (auto cp : value) {
    if constexpr (std::is_same_v<Char, char>) {
      if (cp < 0x80) {
        result.push_back(static_cast<char>(cp));
      } else {
        const int count = cp < 0x800 ? 2 : cp < 0x10000 ? 3 : 4;
        result.push_back(static_cast<char>(
          (0xff << (8 - count)) | (cp >> (6 * (count - 1)))));
        for (int i = count - 2; i >= 0; --i)
          result.push_back(static_cast<char>(0x80 | ((cp >> (6 * i)) & 63)));
      }
    } else {
      if constexpr (sizeof(Char) == 2) {
        if (cp >= 0x10000) {
          cp -= 0x10000;
          result.push_back(static_cast<Char>(0xd800 + (cp >> 10)));
          result.push_back(static_cast<Char>(0xdc00 + (cp & 1023)));
          continue;
        }
      }
      result.push_back(static_cast<Char>(cp));
    }
  }
  return result;
}

template<typename Char>
auto plain(const std::vector<basic_styled_text<Char>>& lines)
  -> std::vector<std::basic_string<Char>>
{
  auto result = std::vector<std::basic_string<Char>>{};
  for (const auto& line : lines)
    result.push_back(line.plain_text());
  return result;
}

template<typename Char>
auto rendered(const basic_styled_text<Char>& text) -> std::basic_string<Char> {
  if constexpr (std::is_same_v<Char, char>)
    return std::format("{}", text);
  else
    return std::format(L"{}", text);
}

template<typename Char> class WordWrap : public testing::Test {};
using Characters = testing::Types<char, wchar_t>;
TYPED_TEST_SUITE(WordWrap, Characters);

TYPED_TEST(WordWrap, AsciiAndPhysicalLines) {
  using Char = TypeParam;
  using text = basic_styled_text<Char>;
  auto check = [](std::string_view input,
                  std::initializer_list<std::string_view> expected) {
    auto wanted = std::vector<std::basic_string<Char>>{};
    for (const auto line : expected)
      wanted.push_back(ascii<Char>(line));
    EXPECT_EQ(plain(word_wrap(text{ascii<Char>(input)}, 16)), wanted);
  };
  check("", {});
  check("\t\n \n", {});
  check("a\n\nb\n\n", {"a", "", "b"});
  check("\n\na\n", {"", "", "a"});
  check("  a  b  ", {"  a  b"});
  check("a\r\nb", {"a", "b"});
  check("a\t\v\f\rb", {"a    b"});
  check("one two three four five", {"one two three", "four five"});
  check("abcdefghijklmnop next", {"abcdefghijklmnop", "next"});
  check("abcdefghi  klmnopqr", {"abcdefghi", "klmnopqr"});
  check("a                b", {"a", "b"});
  check("                 b", {"b"});
  check("abcdefghijklmnopqrstuvwxyz", {"abcdefghijklmno-", "pqrstuvwxyz"});
  check("abc abcdefghijklmnopqrstuvwxyz",
        {"abc abcdefghijk-", "lmnopqrstuvwxyz"});
  check("abcdefghijklmn abcdefghijklmnopqrstuvwxyz",
        {"abcdefghijklmn", "abcdefghijklmno-", "pqrstuvwxyz"});
}

TYPED_TEST(WordWrap, BlankLinesPreservePaddingStyle) {
  using Char = TypeParam;
  using text = basic_styled_text<Char>;
  const auto red = bg(term_color::red);
  for (const auto style : {red, absolute(red)}) {
    const auto lines = word_wrap(text{ascii<Char>("\na\n\n \t\nb"), style}, 16);
    ASSERT_EQ(lines.size(), 5u);
    const auto padding = rendered(text{std::basic_string<Char>(16, ' '), style});
    for (const auto i : {0, 2, 3}) {
      EXPECT_TRUE(lines[i].empty());
      EXPECT_EQ(lines[i].style(), style);
      if constexpr (std::is_same_v<Char, char>) {
        EXPECT_EQ(std::format("{:16}", lines[i]), padding);
      } else {
        EXPECT_EQ(std::format(L"{:16}", lines[i]), padding);
      }
    }
  }
}

TYPED_TEST(WordWrap, WidthValidatedBeforeInput) {
  using text = basic_styled_text<TypeParam>;
  for (const auto width : {std::ptrdiff_t{-1}, std::ptrdiff_t{0},
                          std::ptrdiff_t{15},
                          std::numeric_limits<std::ptrdiff_t>::min()}) {
    EXPECT_THROW((void)word_wrap(text{}, width), std::invalid_argument);
    EXPECT_THROW((void)word_wrap(text{ascii<TypeParam>(" \n")}, width),
                 std::invalid_argument);
  }
  EXPECT_EQ(word_wrap(text{ascii<TypeParam>("a b")},
                     std::numeric_limits<std::ptrdiff_t>::max()).size(), 1u);
}

TYPED_TEST(WordWrap, PunctuationAndQuotes) {
  using Char = TypeParam;
  using text = basic_styled_text<Char>;
  const auto prefix = ascii<Char>("12345678");
  const auto suffix = ascii<Char>("abcdefgh");
  for (const auto cp : U",.;:!?/-)\u3001\u3002\uff09") {
    if (cp == 0) continue;
    const auto punctuation = encoded<Char>(std::u32string{cp});
    const auto lines = plain(word_wrap(
      text{prefix + punctuation + suffix}, 16));
    ASSERT_EQ(lines.size(), 2u);
    EXPECT_EQ(lines[0], prefix + punctuation);
    EXPECT_EQ(lines[1], suffix);
  }
  for (const auto cp : U"('\"\u2019\u201c\u301e\uff02\uff07") {
    if (cp == 0) continue;
    const auto punctuation = encoded<Char>(std::u32string{cp});
    const auto lines = plain(word_wrap(
      text{prefix + punctuation + suffix}, 16));
    ASSERT_EQ(lines.size(), 2u);
    EXPECT_EQ(lines[0].back(), Char{'-'});
  }
  const auto lines = plain(word_wrap(text{ascii<Char>("123456789 don't")}, 16));
  ASSERT_EQ(lines.size(), 1u);
  EXPECT_EQ(lines[0], ascii<Char>("123456789 don't"));
}

TYPED_TEST(WordWrap, UnicodeWidthsAndWhitespace) {
  using Char = TypeParam;
  using text = basic_styled_text<Char>;
  auto lines = plain(word_wrap(
    text{encoded<Char>(U"abcdefghijklmno\u754c")}, 16));
  ASSERT_EQ(lines.size(), 2u);
  EXPECT_EQ(lines[0], ascii<Char>("abcdefghijklmno-"));
  EXPECT_EQ(lines[1], encoded<Char>(U"\u754c"));
  lines = plain(word_wrap(
    text{encoded<Char>(U"12345678901234\U0001f600")}, 16));
  ASSERT_EQ(lines.size(), 1u);
  EXPECT_EQ(lines[0], encoded<Char>(U"12345678901234\U0001f600"));
  lines = plain(word_wrap(text{encoded<Char>(U"\U0001f600\U0001f600\U0001f600"
    U"\U0001f600\U0001f600\U0001f600\U0001f600\U0001f600\U0001f600")}, 16));
  ASSERT_EQ(lines.size(), 2u);
  EXPECT_EQ(lines[0], encoded<Char>(U"\U0001f600\U0001f600\U0001f600"
    U"\U0001f600\U0001f600\U0001f600\U0001f600-"));
  EXPECT_EQ(lines[1], encoded<Char>(U"\U0001f600\U0001f600"));
  lines = plain(word_wrap(
    text{encoded<Char>(U"a\u0085\u00a0\u2003\u2028\u2029b")}, 16));
  ASSERT_EQ(lines.size(), 1u);
  EXPECT_EQ(lines[0], ascii<Char>("a     b"));
  // Combining marks count as one, matching the UTF-8 formatter's model.
  lines = plain(word_wrap(text{encoded<Char>(U"123456789012345a\u0301")}, 16));
  ASSERT_EQ(lines.size(), 2u);
  EXPECT_EQ(lines[0], ascii<Char>("123456789012345-"));
  EXPECT_EQ(lines[1], encoded<Char>(U"a\u0301"));
}

TYPED_TEST(WordWrap, ControlsAndPerSpanAnsi) {
  using Char = TypeParam;
  using text = basic_styled_text<Char>;
  auto value = ascii<Char>("a");
  for (char32_t cp = 0; cp < 0xa0; ++cp) {
    if (cp > 0x1f && cp < 0x7f) continue;
    if ((cp >= 9 && cp <= 13) || cp == 0x85 || cp == 0x1b) continue;
    value += encoded<Char>(std::u32string{cp});
  }
  value += ascii<Char>("b\x1b");
  EXPECT_EQ(plain(word_wrap(text{value}, 16)),
            (std::vector{ascii<Char>("ab")}));
  EXPECT_EQ(plain(word_wrap(text{ascii<Char>("a\x1b[31mb\x1b[0m")}, 16)),
            (std::vector{ascii<Char>("ab")}));
  EXPECT_EQ(plain(word_wrap(text{ascii<Char>("a\x1b[31")}
                         + text{ascii<Char>("mb")}, 16)),
            (std::vector{ascii<Char>("a[31mb")}));
  EXPECT_EQ(plain(word_wrap(text{ascii<Char>("a\x1b]unfinished\x1b[31m")}, 32)),
            (std::vector{ascii<Char>("a]unfinished[31m")}));
  EXPECT_EQ(plain(word_wrap(text{encoded<Char>(U"a\u00e9\u0100b")}, 16)),
            (std::vector{encoded<Char>(U"a\u00e9\u0100b")}));
}

TYPED_TEST(WordWrap, StylesHyphensAndInputPreservation) {
  using Char = TypeParam;
  using text = basic_styled_text<Char>;
  const auto red = fg(term_color::red);
  const auto input = bold(text{ascii<Char>("abc "), red}
    + absolute(underline(text{ascii<Char>("abcdefghijkl")}
                       + text{ascii<Char>("mnopqrstuvwxyz")})));
  const auto saved = input;
  const auto lines = word_wrap(input, 16);
  ASSERT_EQ(lines.size(), 2u);
  EXPECT_EQ(input, saved);
  const auto expected0 = bold(text{ascii<Char>("abc "), red}
    + absolute(underline(text{ascii<Char>("abcdefghijk-")})));
  const auto expected1 = absolute(underline(
    text{ascii<Char>("l")} + text{ascii<Char>("mnopqrstuvwxyz")}));
  for (const auto style : {bg(term_color::blue), fg(term_color::green)}) {
    EXPECT_EQ(rendered(underlay(style, lines[0])),
              rendered(underlay(style, expected0)));
    EXPECT_EQ(rendered(overlay(style, lines[0])),
              rendered(overlay(style, expected0)));
    EXPECT_EQ(rendered(underlay(style, lines[1])),
              rendered(expected1));
    EXPECT_EQ(rendered(overlay(style, lines[1])),
              rendered(overlay(style, expected1)));
  }
  // A style change does not create a word boundary.
  const auto joined = text{ascii<Char>("12345678 abc"), red}
                    + text{ascii<Char>("defghij"), underline()};
  EXPECT_EQ(plain(word_wrap(joined, 16)),
            (std::vector{ascii<Char>("12345678"), ascii<Char>("abcdefghij")}));
  const auto trailing = text{ascii<Char>("a  "), red}
                      + text{ascii<Char>(" \n  "), underline()};
  EXPECT_EQ(plain(word_wrap(trailing, 16)), (std::vector{ascii<Char>("a")}));
}

TEST(WordWrapEncoding, MalformedUtf8AndSplitSequences) {
  const auto invalid = std::string{"\x80\xc0\xaf\xed\xa0\x80\xf4\x90\x80\x80"};
  EXPECT_EQ(plain(word_wrap(styled_text{invalid}, 16)), (std::vector{invalid}));
  const auto input = styled_text{std::string(14, 'a') + "\xe7"}
                   + styled_text{"\x95\x8c"};
  const auto lines = plain(word_wrap(input, 16));
  ASSERT_EQ(lines.size(), 2u);
  EXPECT_EQ(lines[0], std::string(14, 'a') + "\xe7-");
  EXPECT_EQ(lines[1], "\x95\x8c");
}

TEST(WordWrapEncoding, MalformedWideAndSplitSurrogates) {
  const auto invalid = std::wstring{static_cast<wchar_t>(0xd800), L'x',
                                    static_cast<wchar_t>(0xdc00)};
  EXPECT_EQ(plain(word_wrap(wstyled_text{invalid}, 16)),
            (std::vector{invalid}));
  if constexpr (sizeof(wchar_t) == 2) {
    const auto input = wstyled_text{std::wstring(14, L'a')
                                   + static_cast<wchar_t>(0xd83d)}
                     + wstyled_text{
                         std::wstring{static_cast<wchar_t>(0xde00), L'b'}};
    const auto lines = plain(word_wrap(input, 16));
    ASSERT_EQ(lines.size(), 2u);
    EXPECT_EQ(lines[0], std::wstring(14, L'a')
                       + static_cast<wchar_t>(0xd83d) + L'-');
    EXPECT_EQ(lines[1], (std::wstring{static_cast<wchar_t>(0xde00), L'b'}));
  } else {
    const auto input = std::wstring{static_cast<wchar_t>(0x110000),
                                    static_cast<wchar_t>(0xffffffff)};
    EXPECT_EQ(plain(word_wrap(wstyled_text{input}, 16)), (std::vector{input}));
  }
}

TEST(WordWrapStructure, ManyLinesAndNestedGroups) {
  auto input = styled_text{};
  for (int i = 0; i < 1000; ++i)
    input += styled_text{"abcdefghijklmnop\n", bold()};
  const auto lines = word_wrap(input, 16);
  ASSERT_EQ(lines.size(), 1000u);
  for (const auto& line : lines)
    EXPECT_EQ(rendered(line), rendered(bold("abcdefghijklmnop")));
  auto deep = styled_text{"abcdefghijklmnop next"};
  for (int i = 0; i < 300; ++i)
    deep = bold(styled_text{" "} + std::move(deep));
  const auto wrapped = word_wrap(deep, 16);
  ASSERT_EQ(wrapped.size(), 2u);
  EXPECT_EQ(wrapped[0].plain_text(), "abcdefghijklmnop");
  EXPECT_EQ(wrapped[1].plain_text(), "next");
}

TYPED_TEST(WordWrap, WidthAndContentInvariants) {
  using Char = TypeParam;
  using text = basic_styled_text<Char>;
  auto state = std::uint32_t{12345};
  for (int trial = 0; trial < 200; ++trial) {
    auto input = std::basic_string<Char>{};
    auto content = std::basic_string<Char>{};
    for (int i = 0; i < 500; ++i) {
      state = state * 1664525u + 1013904223u;
      const auto cp = "abcdefghij,;(' \t\n"[(state >> 16) % 18];
      input.push_back(static_cast<Char>(cp));
      if (cp != ' ' && cp != '\t' && cp != '\n' && cp != 0)
        content.push_back(static_cast<Char>(cp));
    }
    const auto width = 16 + trial % 33;
    const auto lines = word_wrap(text{input}, width);
    auto recovered = std::basic_string<Char>{};
    for (const auto& line : lines) {
      const auto value = line.plain_text();
      EXPECT_LE(value.size(), static_cast<std::size_t>(width));
      if (!value.empty()) {
        EXPECT_NE(value.back(), Char{' '});
      }
      for (const auto cp : value) {
        if (cp != Char{' '} && cp != Char{'-'})
          recovered.push_back(cp);
      }
    }
    EXPECT_EQ(recovered, content);
    if (!lines.empty()) {
      EXPECT_FALSE(lines.back().plain_text().empty());
    }
  }
}
} // namespace
