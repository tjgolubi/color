/**
 * @file
 * Wraps styled text in a table with independently aligned columns.
 *
 * The demo defines its own table layout, including column widths, alignment,
 * borders, and row height. {color} wraps styled cell contents to their
 * estimated Unicode display width and formats each resulting line with the
 * requested alignment. The cell's styles are preserved during both steps.
 */
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
using tjg::color::text_style;

/// Where to place a cell's text within its column width.
enum class alignment {
  left,   ///< Place any unused space after the text.
  center, ///< Distribute unused space on both sides of the text.
  right   ///< Place any unused space before the text.
};

/// Layout and default background for one table column.
struct column {
  const char* heading; ///< Heading text displayed in the header row.
  std::size_t width;   ///< Content width in display columns, excluding gutters.
  alignment align;     ///< Alignment of the heading and each wrapped cell line.
  rgb background;      ///< Default background for body text and padding.

  /// Returns the column background brightened for the header.
  /// Each RGB channel is multiplied by 2.5, rounded half up, and capped at 255.
  constexpr auto header_background() const noexcept -> rgb {
    const auto brighten = [](int channel) {
      return std::min(255, (5 * channel + 1) / 2);
    };
    return {brighten(background.r), brighten(background.g),
            brighten(background.b)};
  }
}; // column

/**
 * Prints a table of styled cells to standard output.
 * @tparam N Number of columns, fixed at compile time.
 *
 * Each row stores one styled value per column. Column settings control width,
 * alignment, and default colors. Individual text spans can supply their own
 * styling. The caller chooses where to print rules between body rows.
 */
template<std::size_t N>
class table {
  std::array<column, N> _columns; ///< Settings in left-to-right display order.

public:
  /// One styled text value per column, in display order.
  using row = std::array<styled_text, N>;

  /**
   * Sets the layout and default colors for all columns.
   * @param columns Settings in left-to-right display order.
   * @throws std::invalid_argument A column is narrower than 4 display columns,
   * the minimum supported by `tjg::color::word_wrap()`.
   */
  explicit table(std::array<column, N> columns) : _columns{std::move(columns)} {
    for (const auto& col : _columns) {
      if (col.width < 4)
        throw std::invalid_argument{"table columns must be at least 4 wide"};
    }
  }

  /**
   * Prints a horizontal border across the table.
   * @param left Glyph at the left edge.
   * @param joint Glyph between adjacent columns.
   * @param right Glyph at the right edge.
   *
   * The horizontal fill spans each content width plus one gutter space on
   * either side. Use different edge and joint glyphs for the top, middle,
   * and bottom rules.
   */
  void print_rule(std::string_view left, std::string_view joint,
                  std::string_view right, bool inner=true) const
  {
    for (std::size_t i = 0; i < N; ++i) {
      const auto width = _columns[i].width + 2;
      auto style = inner ? bg(_columns[i].background) : text_style{};
      std::print("{}{:─<{}}", (i == 0) ? left : joint, styled("", style), width);
    }
    std::println("{}", right);
  } // print_rule

  /// Prints the top rule, bold column headings, and the rule below them.
  /// Headings use the same wrapping and alignment as body cells.
  void print_header() const {
    auto headings = row{};
    for (std::size_t i = 0; i < N; ++i)
      headings[i] = tjg::color::bold(_columns[i].heading);
    print_rule("┌", "┬", "┐", false);
    print_row(headings, /*header=*/true);
    print_rule("├", "┼", "┤");
  } // print_header

  /**
   * Prints one logical row as one or more physical lines.
   * @param cells Styled cell contents in left-to-right column order.
   * @param header Use white text and brighter column backgrounds for headings.
   *
   * Wrap each cell independently at its column width. The tallest cell sets
   * the row height, with at least one physical line even for an empty row.
   * On each line, use a blank styled value for any cell that has run out of
   * text, so its padding and borders still line up with the rest of the row.
   *
   * Pass each line directly to the styled-text formatter. Its field width
   * aligns the text in display columns, and the enclosing style supplies
   * default colors for the cell and its padding. Explicit span colors can
   * override those defaults. The demo prints the gutters and vertical borders.
   */
  void print_row(const row& cells, bool header = false) const {
    auto wrapped = std::array<std::vector<styled_text>, N>{};
    auto height = std::size_t{1}; // Even an entirely empty row has a line.
    for (std::size_t i = 0; i < N; ++i) {
      auto indent = (i == 0) ? 4 : 0;
      wrapped[i] = tjg::color::word_wrap(cells[i], _columns[i].width, indent);
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
        const auto style = fg(foreground).bg(background);
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

/**
 * Prints a sample work queue with three differently aligned columns.
 *
 * The rows demonstrate explicit newlines, UTF-8 text such as `東京` and
 * `Café`, and styling within a cell. Underlined titles, a reversed status,
 * and a highlighted word retain their styles when the cells wrap.
 */
int main() {
  using namespace tjg::color;
  using enum term_color;

  const auto work = table<3>{{{
    {"Work item / handoff notes", 40, alignment::left,   rgb{30, 42, 54}},
    {"Status",                    18, alignment::center, rgb{31, 46, 39}},
    {"Est. effort",               12, alignment::right,  rgb{49, 40, 49}},
  }}};

  using em = tjg::color::emphasis;
  println(em::bold | em::reverse, "{:^80}\n",
          "PLATFORM MAINTENANCE — weekly work queue");

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
  work.print_rule("└", "┴", "┘", false);

  std::println("{}\n", wrapped(tagged(
      "Effort estimates are _person_-hours; descriptions and status notes wrap "
      "independently.")));
} // main
