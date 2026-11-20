# {color} demos

From this directory, run `make run` using GNU make, a C++23-capable compiler,
and a built copy of {fmt} for the comparison demos. From the repository root,
run `make -C demo run`.

The {color} demos include `<tjg/color.hpp>`. The Makefile adds
`$(TJG_ROOT)/include` to the compiler's include path and links `libcolor.a`,
building it with CMake when needed. `TJG_ROOT=..` and
`TJG_BUILD=$(TJG_ROOT)/build` by default. Use a matching compiler and standard
library for the archive and demos. To build a single demo using only {color}
and the C++ standard library,
run `make StyledDemo` and then `./StyledDemo`.

`Result42Compare` and `TableDemoFmt` use {fmt}. `FMT_ROOT` defaults to
`$HOME/App/fmt` and `FMT_LIB` defaults to `$FMT_ROOT/build/libfmtd.a`.
For a different {fmt} build, set both paths, for example:

```sh
make run FMT_ROOT=/path/to/fmt FMT_LIB=/path/to/fmt/build/libfmt.a
```

Run `make clean` before changing the header paths, compiler, or build flags.

Use an ANSI-capable terminal to see the styling.

| Demo                                     | Shows                                                             |
| ---------------------------------------- | ----------------------------------------------------------------- |
| [Result42Compare](Result42Compare.cpp)   | The same result message styled with raw SGR, {fmt}, and {color}.  |
| [StyledDemo](StyledDemo.cpp)             | Formatting individual values with `styled()`.                     |
| [StyledTextDemo](StyledTextDemo.cpp)     | Composing styled text and applying underlay and overlay.          |
| [TableDemo](TableDemo.cpp)               | The dashboard with {color} formatting.                            |
| [TableDemoCpp](TableDemoCpp.cpp)         | The dashboard with standard C++23 and raw SGR sequences.          |
| [TableDemoFmt](TableDemoFmt.cpp)         | The dashboard with {fmt}.                                         |
| [TableDemoOstream](TableDemoOstream.cpp) | The dashboard with {color} and stream insertion.                  |

`StyledTextDemo` prints the same styled line with underlay first and overlay
second, using a white foreground, `term_color::gray` background, and
strikethrough. Underlay supplies defaults while preserving explicit colors.
Overlay replaces the affected colors throughout relative text. Both preserve
the absolute underline-only span.
