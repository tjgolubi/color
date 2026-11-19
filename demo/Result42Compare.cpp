#include <fmt/color.h>
#include <tjg/color.hpp>

#include <print>

int main() {
  auto result = 42;

  // C++23 with raw SGR sequences.
  {
    std::println("\x1b[4mThe result is \x1b[31m{}\x1b[39m bytes.\x1b[0m",
                 result);
  }

  // C++23 with named SGR sequences.
  {
    constexpr char Underline[] = "\x1b[4m";
    constexpr char Red[]       = "\x1b[31m";
    constexpr char Reset[]     = "\x1b[0m";

    std::println("{}The result is {}{}{}{} bytes.{}",
                 Underline, Red, result, Reset, Underline, Reset);
  }

  // {fmt}: the red argument resets the underline before the suffix.
  {
    using namespace fmt;
    const auto line = emphasis::underline;
    print(line, "The result is {} bytes.\n",
                styled(result, fg(terminal_color::red)));
  }

  // {fmt}: explicitly reapply the underline to the suffix.
  {
    using namespace fmt;
    const auto line = emphasis::underline;
    print(line, "The result is {}{}\n",
                styled(result, fg(terminal_color::red)),
                styled(" bytes.", line));
  }

  // {color}: the enclosing underline resumes after the red argument.
  {
    using namespace tjg::color;
    println(underline(), "The result is {} bytes.",
                         styled(result, fg(term_color::red)));
  }
} // main
