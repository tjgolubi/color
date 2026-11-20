#include <tjg/color.hpp>

#include <print>
#include <string_view>
#include <array>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <utility>

#include <cstddef>

namespace {
using tjg::color::rgb;
using tjg::color::styled_text;

enum class alignment { left, center, right };

struct column {
  const char* heading;
  int width;
  alignment align;
  rgb background;

  constexpr auto header_background() const noexcept -> rgb {
    // Multiply by 2.5, rounding half channels up and saturating at 255.
    const auto brighten = [](int channel) {
      return std::min(255, (5 * channel + 1) / 2);
    };
    return {brighten(background.r), brighten(background.g),
            brighten(background.b)};
  }
};

// Fixed column counts catch missing cells at compile time. Widths and
// alignment belong to the table; cell contents carry their own styles.
template<std::size_t N>
class table {
  std::array<column, N> _columns;

public:
  using row = std::array<styled_text, N>;

  explicit table(std::array<column, N> columns)
    : _columns{std::move(columns)}
  {
    for (const auto& col : _columns) {
      if (col.width < 16)
        throw std::invalid_argument{"table columns must be at least 16 wide"};
    }
  }

  void print_rule(std::string_view left, std::string_view joint,
                  std::string_view right) const
  {
    for (std::size_t i = 0; i < N; ++i) {
      const auto width = static_cast<std::size_t>(_columns[i].width) + 2;
      std::print("{}{:─<{}}", (i == 0) ? left : joint, "", width);
    }
    std::println("{}", right);
  }

  void print_header() const {
    auto headings = row{};
    for (std::size_t i = 0; i < N; ++i)
      headings[i] = tjg::color::bold(_columns[i].heading);
    print_rule("┌", "┬", "┐");
    print_row(headings, /*header=*/true);
    print_rule("├", "┼", "┤");
  }

  void print_row(const row& cells, bool header = false) const {
    auto wrapped = std::array<std::vector<styled_text>, N>{};
    auto height = std::size_t{1}; // Even an entirely empty row has a line.
    for (std::size_t i = 0; i < N; ++i) {
      wrapped[i] = tjg::color::word_wrap(cells[i], _columns[i].width);
      height = std::max(height, wrapped[i].size());
    }

    const auto blank = styled_text{};
    for (std::size_t line = 0; line < height; ++line) {
      std::print("│");
      for (std::size_t i = 0; i < N; ++i) {
        const auto& value = (line < wrapped[i].size())
                          ? wrapped[i][line] : blank;
        const auto& col = _columns[i];
        const auto background = header ? col.header_background()
                                       : col.background;
        const auto foreground = header ? rgb::white : rgb::gainsboro;
        const auto style = bg(background).fg(foreground);
        // Format the styled line itself: plain_text().size() would count
        // bytes, and formatting a rendered ANSI string would count escapes.
        switch (col.align) {
          case alignment::left:
            tjg::color::print(style, " {:<{}} ", value, col.width);
            break;
          case alignment::center:
            tjg::color::print(style, " {:^{}} ", value, col.width);
            break;
          case alignment::right:
            tjg::color::print(style, " {:>{}} ", value, col.width);
            break;
        }
        std::print("│");
      }
      std::println();
    }
  } // print_row

}; // table

} // local

int main() {
  using namespace tjg::color;
  using enum term_color;

  const auto work = table<3>{{{
    {"Work item / handoff notes", 40, alignment::left,   rgb{30, 42, 54}},
    {"Status",                    18, alignment::center, rgb{31, 46, 39}},
    {"Est. effort",               16, alignment::right,  rgb{49, 40, 49}},
  }}};

  std::println("PLATFORM MAINTENANCE — weekly work queue\n");
  work.print_header();

  work.print_row({
    underline(bold("Rotate production credentials"))
      + "\nUpdate the API workers first, then verify that scheduled exports "
        "can still read the reporting database.",
    "Ready\nApproved by security",
    "3.5 h\n2 engineers",
  });
  work.print_rule("├", "┼", "┤");

  work.print_row({
    underline(bold("Restore rehearsal — 東京"))
      + "\nRecover last night's backup into an isolated instance. "
        "Compare row counts before deleting the rehearsal environment.",
    styled_text{"Blocked", fg(yellow).reverse()}
      + "\nWaiting for temporary storage allocation",
    "6.0 h\n1 engineer",
  });
  work.print_rule("├", "┼", "┤");

  work.print_row({
    underline(bold("Café office network"))
      + "\nReplace the " + styled_text{"lobby", fg(bright_magenta)}
      + " access point after closing. "
        "Keep the guest network available during the change.",
    "Scheduled\nAfter 18:00",
    "1.5 h",
  });
  work.print_rule("├", "┼", "┤");

  work.print_row({
    underline(bold("Retire the legacy export job"))
      + "\nFinance has confirmed the new reports. "
        "Keep the old configuration for one billing cycle.",
    styled_text{"Complete", fg(green)},
    "2.0 h",
  });
  work.print_rule("└", "┴", "┘");

  std::println("\nEffort estimates are person-hours; descriptions and status "
               "notes wrap independently.");
} // main
