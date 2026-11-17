#include <fmt/color.h>
#include <fmt/format.h>

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <string>
#include <string_view>

using fmt::text_style;
using fmt::fg;
using fmt::bg;
using fmt::styled;
using tc = fmt::terminal_color;
using rgb = fmt::color;
using emphasis = fmt::emphasis;

namespace {

// Each column has a distinct background color.
constexpr auto service_color = fg(tc::white) | bg(rgb::dark_blue);
constexpr auto status_color  = fg(tc::white) | bg(rgb::dark_green);
constexpr auto latency_color = fg(tc::white) | bg(rgb::dark_golden_rod);
constexpr auto notes_color   = fg(tc::white) | bg(rgb::indigo);

// An absolute fragment uses this style without the enclosing row emphasis.
constexpr auto critical_style =
    fg(rgb::red) | bg(rgb::white) | emphasis::bold | emphasis::blink;

// Reuse column backgrounds when supplying a different foreground.
constexpr auto status_background = bg(status_color.get_background());
constexpr auto notes_background  = bg( notes_color.get_background());

struct fragment {
  std::string_view text;
  std::optional<text_style> style{};
  bool absolute = false;
};

using note = std::initializer_list<fragment>;

// Format the Notes cell, preserving each fragment's explicit style.
auto format_note(note parts, text_style row) -> std::string {
  // The 30-column limit applies to the whole cell.
  auto plain = std::string{};
  for (const auto& part : parts)
    plain += part.text;
  const auto clipped = fmt::format("{:.30}", plain);
  const auto padded  = fmt::format("{:<30}", clipped);
  const auto padding = std::string_view{padded}.substr(clipped.size());

  auto result = std::string{};
  auto out = std::back_inserter(result);
  auto remaining = clipped.size();
  for (const auto& part : parts) {
    if (remaining == 0) break;
    const auto count = std::min(remaining, part.text.size());
    if (count == 0) continue;

    // Each styled fragment ends with a reset. Give the next one its full style.
    auto style = part.style.value_or(notes_color);
    if (!part.absolute) style |= row;
    out = fmt::format_to(out, "{}", styled(part.text.substr(0, count), style));
    remaining -= count;
  }
  if (!padding.empty())
    fmt::format_to(out, "{}", styled(padding, notes_color | row));
  return result;
}

// Each field has equal width and precision.
// Long content is truncated; short content is padded.
void print_row(std::string_view service,
               std::string_view status,
               std::string_view latency,
               note notes,
               text_style status_foreground = fg(tc::white),
               text_style row = {})
{
  // Argument 1 is the separator, which also inherits the row emphasis.
  fmt::println("{0:<16.16}{1}{2:^12.12}{1}{3:>12.12}{1}{4}",
               styled(service, service_color     | row), styled(" ", row),
               styled(status,  status_foreground | status_background | row),
               styled(latency, latency_color     | row), format_note(notes, row));
}

} // local

int main() {
  fmt::println("SYSTEM HEALTH DASHBOARD\n");

  // Column headings inherit bold and underline from the row.
  print_row("Service", "Status", "Latency", {{"Notes"}}, fg(tc::white),
            emphasis::bold | emphasis::underline);

  // Normal row.
  const auto ok = fg(tc::bright_green);
  const auto nas_note = note{{"All", fg(tc::red) | bg(tc::cyan)}, {" volumes "},
                            {"healthy", fg(tc::green) | notes_background}};
  print_row("NAS", "OK", "12 ms", nas_note, ok);

  // UTF-8 display widths: "東京" is 6 bytes but 4 terminal columns.
  // "Café" is 5 bytes but 4 terminal columns.
  print_row("東京 NAS", "OK", "9 ms", {{"Café 東京: all systems normal"}}, ok);

  // Two fragments with different foreground colors.
  const auto vpn_note = note{{"Encrypted "},
                            {"connection", fg(rgb::aquamarine) | notes_background}};
  print_row("VPN", "OK", "38 ms", vpn_note, ok);

  // Bold row with an independently colored warning.
  const auto warn = fg(tc::yellow);
  const auto backup_note = note{{"Slow", fg(rgb::yellow) | notes_background},
                               {" - retry scheduled"}};
  print_row("Backup", "WARN", "215 ms", backup_note, warn, emphasis::bold);

  // An absolute red-on-white fragment within the Notes column.
  const auto fail = fg(tc::bright_red);
  const auto db_note = note{{"Connection refused: "},
                           {"CRITICAL!", critical_style, true},
                           {" Database service is unavailable"}};
  print_row("Database", "FAIL", "--", db_note, fail, emphasis::bold);

  // Faint row emphasis, retaining the column backgrounds.
  print_row("Old server", "OFFLINE", "--", {{"Maintenance mode"}},
            fg(tc::white), emphasis::faint);

  // Style only the hexadecimal ID; the suffix uses the surrounding style.
  fmt::println("\nRequest ID: {:04x} — completed",
               styled(42, fg(tc::bright_cyan)));
} // main
