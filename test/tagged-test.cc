#include <tjg/color.hpp>

#include "test-support.h"

#include <format>

namespace {
using namespace tjg::color;

template<tjg::CharType Char>
class Tagged : public testing::Test {
public:
  using text = basic_styled_text<Char>;
  using string = std::basic_string<Char>;

  static auto ascii(std::string_view value) -> string {
    return {value.begin(), value.end()};
  }

  static auto unicode(std::u8string_view utf8, std::wstring_view wide) -> string {
    if constexpr (std::same_as<Char, char>)
      return {reinterpret_cast<const char*>(utf8.data()), utf8.size()};
    else
      return string{wide};
  }

  static auto parse(std::string_view markup) -> text {
    return tagged<Char>(ascii(markup));
  }

  static auto leaf(std::string_view value, text_style style = {}) -> text {
    return text{ascii(value), style};
  }

  static auto render(const text& value) -> string {
    if constexpr (std::same_as<Char, char>) return std::format("{}", value);
    else return std::format(L"{}", value);
  }

  static void check(std::string_view markup, const text& expected) {
    SCOPED_TRACE(markup);
    const auto result = parse(markup);
    EXPECT_EQ(result.plain_text(), expected.plain_text());
    EXPECT_EQ(render(result), render(expected));
  }
};

using Characters = testing::Types<char, wchar_t>;
TYPED_TEST_SUITE(Tagged, Characters);

TYPED_TEST(Tagged, NamedAndShorthandStyles) {
  using T = TestFixture;
  T::check("<b>x</b><faint>x</faint><i>x</><u>x</u><s>x</s>",
    T::leaf("x", bold()) + T::leaf("x", faint()) + T::leaf("x", italic())
    + T::leaf("x", underline()) + T::leaf("x", strike()));
  T::check("<emphasis=blink|reverse, conceal>x</emphasis>",
    T::leaf("x", blink(reverse(conceal()))));
  T::check("<bold red underline on dark_blue>x</>",
    T::leaf("x", bold(underline(text_style{rgb::red, rgb::dark_blue}))));
  T::check("<color = bold red on underline dark_blue >x</color>",
    T::leaf("x", bold(underline(text_style{rgb::red, rgb::dark_blue}))));
  T::check("<on bold dark_blue>x</>", T::leaf("x", bold(bg(rgb::dark_blue))));
  T::check("<color=term_red on #00cDce>x</>",
    T::leaf("x", text_style{term_color::red, rgb{0x00cdce}}));
  T::check("<xterm_red>x</>", T::leaf("x", fg(rgb::xterm_red)));
  T::check("<#abcdEf>x</>", T::leaf("x", fg(rgb{0xabcdef})));
  T::check("<alice_blue>x</><yellow_green>x</>",
    T::leaf("x", fg(rgb::alice_blue)) + T::leaf("x", fg(rgb::yellow_green)));

  auto nested = T::leaf("before ") + T::leaf("inside", absolute(fg(rgb::red)))
              + T::leaf(" after");
  nested.style(bold());
  T::check("<bold>before <color=red, absolute>inside</color> after</bold>",
           nested);
}

TYPED_TEST(Tagged, MarkdownNestingAndLines) {
  using T = TestFixture;
  T::check("**bold** *italic* _underline_ ~~strike~~",
    T::leaf("bold", bold()) + T::leaf(" ") + T::leaf("italic", italic())
    + T::leaf(" ") + T::leaf("underline", underline()) + T::leaf(" ")
    + T::leaf("strike", strike()));
  auto nested = T::leaf("before ") + T::leaf("after", bold());
  nested.style(italic());
  T::check("*before <b>after</b>*", nested);
  auto shorthand = T::leaf("before ") + T::leaf("after", bold()) + T::leaf(" ");
  shorthand.style(italic());
  T::check("*before **after** *", shorthand);
  T::check("<b>*text*</>", T::leaf("text", italic(bold())));
  T::check("*before<br>after*", T::leaf("*before\nafter*"));
  T::check("**a\nb** _a\nb_ ~~a\nb~~", T::leaf("**a\nb** _a\nb_ ~~a\nb~~"));
  T::check("<i>before<br><br>after</i>", T::leaf("before\n\nafter", italic()));
  T::check("*before <b>one<br>two</b>*",
    T::leaf("*before ") + T::leaf("one\ntwo", bold()) + T::leaf("*"));
  T::check(R"(*one\u000Atwo*)", T::leaf("*one\ntwo*"));
}

TYPED_TEST(Tagged, LiteralAndMalformedMarkup) {
  using T = TestFixture;
  for (const auto markup : {"", "foo_bar_baz Really??", "***italic* and bold**",
       "a < b > c", "*italic</>", "*italic</i>", "<i>italic*", "<unclosed",
       "<color=redd>hello</color>", "<red bold underine>warning</>",
       "<color=red on>x</color>", "<red blue>x</>", "<red on blue on cyan>x</>",
       "<red>warn</red>", "<emphasis=bold unknown>x</emphasis>",
       "<b>unmatched", "</>", "</br>", "<i x>x</i>"})
    T::check(markup, T::leaf(markup));
  T::check("<b>bad</i>good</b>", T::leaf("bad</i>good", bold()));
  T::check("<b>unclosed <u>underline</u>",
    T::leaf("<b>unclosed ") + T::leaf("underline", underline()));
  T::check(R"(`\ <b>**literal**</b>\u00a0`)",
    T::leaf(R"(\ <b>**literal**</b>\u00a0)"));
  T::check(R"(\<bold> \` \*x\* \_x\_ \q \n \\ `)",
    T::leaf(R"(<bold> ` *x* _x_ \q \n \ `)"));
  T::check(R"(\uD800 \U00110000 \u12Z4 \U0000)",
    T::leaf(R"(\uD800 \U00110000 \u12Z4 \U0000)"));

  auto input = T::ascii("before<b>bold</b>");
  input.push_back(TypeParam{});
  const auto result = tagged(std::basic_string_view<TypeParam>{input});
  input.clear();
  auto expected = T::ascii("beforebold");
  expected.push_back(TypeParam{});
  EXPECT_EQ(result.plain_text(), expected);
}

TYPED_TEST(Tagged, LiteralTagNesting) {
  using T = TestFixture;
  T::check("<foo>Hello **world**</foo>",
    T::leaf("<foo>Hello ") + T::leaf("world", bold()) + T::leaf("</foo>"));
  T::check("<unknown>text</unknown>", T::leaf("<unknown>text</unknown>"));
  T::check("<on brown><unknown blue>text</> after</> outside",
    T::leaf("<unknown blue>text</> after", bg(rgb::brown)) + T::leaf(" outside"));
  T::check("<b><foo>x</b></foo> after</b>",
    T::leaf("<foo>x</b></foo> after", bold()));
  T::check("<b>before</foo>after</b>", T::leaf("before</foo>after", bold()));
  T::check("<b><color=redd>x</> after</b>",
    T::leaf("<color=redd>x</> after", bold()));
  T::check("<b><i x>x</i> after</b>", T::leaf("<i x>x</i> after", bold()));
  T::check(R"(<b><foo/><bar note="x > y" />after</b>)",
    T::leaf(R"(<foo/><bar note="x > y" />after)", bold()));
  T::check("<foo><b>bold</b>", T::leaf("<foo>") + T::leaf("bold", bold()));
}

TYPED_TEST(Tagged, AbsoluteScopes) {
  using T = TestFixture;
  const auto defaults = absolute(text_style{});
  T::check("<absolute>x</absolute>", T::leaf("x", defaults));
  T::check("<absolute>x</>", T::leaf("x", defaults));
  const auto nested_color = T::parse("<absolute><blue>x</></absolute>");
  EXPECT_EQ(nested_color.plain_text(), T::ascii("x"));
  EXPECT_EQ(T::render(nested_color),
            T::ascii("\x1b[0m") + T::render(T::leaf("x", fg(rgb::blue))));
  T::check("<absolute bold>x</>", T::leaf("x", absolute(bold())));
  T::check("<emphasis=bold | absolute>x</emphasis>", T::leaf("x", absolute(bold())));

  const auto blue_bold = absolute(bold(fg(rgb::blue)));
  T::check("<absolute blue bold>x</>", T::leaf("x", blue_bold));
  T::check("<bold blue absolute>x</>", T::leaf("x", blue_bold));
  T::check("<color=blue absolute bold>x</color>", T::leaf("x", blue_bold));
  const auto on_brown = absolute(bg(rgb::brown));
  T::check("<on absolute brown>x</>", T::leaf("x", on_brown));

  auto nested = T::leaf("before ") + T::leaf("reset", defaults)
              + T::leaf(" blue", absolute(fg(rgb::blue))) + T::leaf(" after");
  nested.style(bold(text_style{rgb::green, rgb::brown}));
  T::check("<bold green on brown>before <absolute>reset</absolute>"
           "<absolute blue> blue</> after</>", nested);
  T::check("<absolute blue on>x</>", T::leaf("<absolute blue on>x</>"));
  T::check("<absolute>x", T::leaf("<absolute>x"));
}

TYPED_TEST(Tagged, UnicodeEscapesAndBoundaries) {
  using T = TestFixture;
  using Char = TypeParam;
  EXPECT_EQ(T::parse(R"(10\ kg 10\u00a0kg \u002A \U0001f642 a\-b)").plain_text(),
    T::unicode(u8"10\u00a0kg 10\u00a0kg * \U0001f642 a\u00adb",
               L"10\u00a0kg 10\u00a0kg * \U0001f642 a\u00adb"));
  for (const auto& literal : {
    T::unicode(u8"\u6771\u4eac*\u3067\u3059*", L"\u6771\u4eac*\u3067\u3059*"),
    T::unicode(u8"*x*\u0301", L"*x*\u0301"),
    T::unicode(u8"\U00020000*x*", L"\U00020000*x*")})
    EXPECT_EQ(T::render(tagged<Char>(literal)), literal);
  const auto punctuated = T::unicode(u8"\u6771\u4eac\uff1a*x*",
                                     L"\u6771\u4eac\uff1a*x*");
  const auto expected = typename T::text{
    T::unicode(u8"\u6771\u4eac\uff1a", L"\u6771\u4eac\uff1a")}
    + T::leaf("x", italic());
  EXPECT_EQ(T::render(tagged<Char>(punctuated)), T::render(expected));

  const auto soft = word_wrap(T::parse(R"(super\-califragilistic\-expiali\-docious)"), 16);
  ASSERT_EQ(soft.size(), 3u);
  EXPECT_EQ(soft[0].plain_text(), T::ascii("super-"));
  EXPECT_EQ(soft[1].plain_text(), T::ascii("califragilistic-"));
  EXPECT_EQ(soft[2].plain_text(), T::ascii("expialidocious"));
  const auto no_break = word_wrap(T::parse(R"(10\ kg)"), 4);
  ASSERT_EQ(no_break.size(), 2u);
  EXPECT_EQ(no_break[0].plain_text(), T::ascii("10"));
  EXPECT_EQ(no_break[1].plain_text(), T::ascii("kg"));
}

TEST(TaggedOverloads, StringLiteralsAndStrings) {
  const auto narrow = styled_text{"text", bold()};
  const auto wide = wstyled_text{L"text", bold()};
  EXPECT_EQ(tagged("<b>text</b>"), narrow);
  EXPECT_EQ(tagged(L"<b>text</b>"), wide);
  EXPECT_EQ(tagged(std::string{"<b>text</b>"}), narrow);
  EXPECT_EQ(tagged(std::wstring{L"<b>text</b>"}), wide);
}

TEST(TaggedNarrow, WrappedProse) {
  const auto text = tagged(std::string_view{"<b>one two three<br><br>four five</b>"});
  const auto result = std::format("{:7}", wrapped(text));
  EXPECT_EQ(tjg::strip_ansi<char>(result), "one two\nthree\n\nfour\nfive");
}

} // namespace
