#include <algorithm>
#include <format>
#include <initializer_list>
#include <print>
#include <string>
#include <string_view>

namespace {

// Each column has a distinct background color.
constexpr auto service_color = std::string_view{"37;48;2;0;0;139"};
constexpr auto status_color  = std::string_view{"37;48;2;0;100;0"};
constexpr auto latency_color = std::string_view{"37;48;2;184;134;11"};
constexpr auto notes_color   = std::string_view{"37;48;2;75;0;130"};

// A leading reset replaces inherited styling for the warning.
constexpr auto critical_style =
    std::string_view{"0;1;5;38;2;255;0;0;48;2;255;255;255"};

struct span {
  std::string_view text;
  std::string_view sgr{};
};

using cell = std::initializer_list<span>;

enum class alignment { left, center, right };

void append_sgr(std::string& out, std::string_view params) {
  out += "\x1b[";
  out += params;
  out += 'm';
}

// Lay out the styled cell and restore column defaults between fragments.
auto render_cell(cell parts, int width, alignment align,
                 std::string_view colors, std::string_view row) -> std::string
{
  // Lay out the plain text before inserting escape sequences.
  auto plain = std::string{};
  for (auto part : parts) plain += part.text;
  const auto clipped = std::format("{:.{}}", plain, width);

  auto padded = std::string{};
  switch (align) {
  case alignment::left:   padded = std::format("{:<{}}", clipped, width); break;
  case alignment::center: padded = std::format("{:^{}}", clipped, width); break;
  case alignment::right:  padded = std::format("{:>{}}", clipped, width); break;
  }
  const auto padding = padded.size() - clipped.size();
  const auto leading = (align == alignment::left)   ? 0
                     : (align == alignment::center) ? padding / 2 : padding;

  auto out = std::string{};
  auto set_column_style = [&] {
    append_sgr(out, colors);
    if (!row.empty()) append_sgr(out, row);
  };

  set_column_style();
  out.append(padded, 0, leading);
  auto remaining = clipped.size();
  for (auto part : parts) {
    if (remaining == 0) break;
    const auto count = std::min(remaining, part.text.size());
    if (count == 0) continue;
    if (!part.sgr.empty()) append_sgr(out, part.sgr);
    out += part.text.substr(0, count);
    remaining -= count;
    if (!part.sgr.empty()) {
      append_sgr(out, "0");
      set_column_style();
    }
  }
  out.append(padded, leading + clipped.size(), padding - leading);
  append_sgr(out, "0");
  if (!row.empty()) append_sgr(out, row);
  return out;
}

// Each field has equal width and precision.
// Long content is truncated; short content is padded.
void print_row(cell service,
               cell status,
               cell latency,
               cell notes,
               std::string_view row = {})
{
  using enum alignment;
  std::println("{} {} {} {}\x1b[0m",
               render_cell(service, 16, left,   service_color, row),
               render_cell(status,  12, center, status_color,  row),
               render_cell(latency, 12, right,  latency_color, row),
               render_cell(notes,   30, left,   notes_color,   row));
}

} // local

int main() {
  std::println("SYSTEM HEALTH DASHBOARD\n");

  // Column headings inherit bold and underline from the row.
  constexpr auto bold_underline = std::string_view{"1;4"};
  print_row({{"Service"}}, {{"Status"}}, {{"Latency"}}, {{"Notes"}}, bold_underline);

  // Normal row.
  const auto ok = cell{{"OK", "92"}};
  const auto nas_note = cell{{"All", "31;46"}, {" volumes "}, {"healthy", "32"}};
  print_row({{"NAS"}}, ok, {{"12 ms"}}, nas_note);

  // UTF-8 display widths: "東京" is 6 bytes but 4 terminal columns.
  // "Café" is 5 bytes but 4 terminal columns.
  print_row({{"東京 NAS"}}, ok, {{"9 ms"}}, {{"Café 東京: all systems normal"}});

  // Two fragments with different foreground colors.
  const auto vpn_note = cell{{"Encrypted "}, {"connection", "38;2;127;255;212"}};
  print_row({{"VPN"}}, ok, {{"38 ms"}}, vpn_note);

  // Bold row with an independently colored warning.
  const auto warn = cell{{"WARN", "33"}};
  const auto backup_note = cell{{"Slow", "38;2;255;255;0"}, {" - retry scheduled"}};
  print_row({{"Backup"}}, warn, {{"215 ms"}}, backup_note, "1");

  // An absolute red-on-white fragment within the Notes column.
  const auto fail = cell{{"FAIL", "91"}};
  const auto db_note = cell{{"Connection refused: "},
                           {"CRITICAL!", critical_style},
                           {" Database service is unavailable"}};
  print_row({{"Database"}}, fail, {{"--"}}, db_note, "1");

  // Faint row emphasis, retaining the column backgrounds.
  print_row({{"Old server"}}, {{"OFFLINE"}}, {{"--"}}, {{"Maintenance mode"}}, "2");

  // Style only the hexadecimal ID; the suffix uses the surrounding style.
  std::println("\nRequest ID: \x1b[96m{:04x}\x1b[0m — completed", 42);
} // main
