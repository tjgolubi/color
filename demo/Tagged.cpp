/// Prints a styled release note at different widths and alignments.
#include <tjg/color.hpp>

#include <print>
#include <string_view>

int main() {
  namespace clr = tjg::color;
  using em = clr::emphasis;
  using namespace clr;

  constexpr std::string_view prose =
    "<bold white on dark_blue>Release highlights</>\n\n"
    "<cyan>Task reports now wrap <yellow>**long descriptions and notes**</> "
    "to fit the report. The full note _stays visible_ in a narrow column.</>\n"
    "\n"
    "**👉 Tip 👈** Open a task to read its full history. 🙂";

  const auto note = tagged(prose);

  auto heading_emphasis = em::reverse | em::bold;

  clr::println("{:^80}\n\n{:<40}\n",
               styled(">>> 40 columns, left aligned <<<", heading_emphasis),
               wrapped(note));

  clr::println("{:^80}\n\n{:>40}\n",
               styled(">>> 40 columns, right aligned <<<", heading_emphasis),
               wrapped(note));

  clr::println("{:^80}\n\n{:<64}\n",
               styled(">>> 64 columns, left aligned <<<", heading_emphasis),
               wrapped(note));
} // main
