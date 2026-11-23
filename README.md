# {color}

{color} is a standalone C++23 library for terminal colors and text
styles. It uses `std::format` and `std::print`, with APIs in namespace `tjg::color`.

## Quick start

Build the static library and link your application to it using the
[CMake instructions](#cmake) below. Use a C++23 compiler and standard library
with `<format>` and `<print>`.

```cpp
#include <tjg/color.hpp>

int main() {
  const auto green = tjg::color::fg(tjg::color::term_color::green);
  tjg::color::println(tjg::color::bold(), "Build {}", tjg::color::styled("passed", green));
}
```

The whole line is bold, and `passed` is green. Styled arguments inherit and
restore their enclosing style. An ANSI-capable terminal displays the colors.

Run `make -C demo StyledDemo` and then `./demo/StyledDemo` to try the
[styled formatting demo](demo/StyledDemo.cpp). See the [demo README](demo/README.md)
for the full set of examples and the {fmt} comparison builds.

## Headers

| Header                        | Provides                                                             |
| ----------------------------- | -------------------------------------------------------------------- |
| `<tjg/color.hpp>`             | Full library, including formatting, printing, streams, and SGR tools |
| `<tjg/color/colors.hpp>`      | Named RGB colors, `term_color`, `cube`, `gray`, and `color_t`         |
| `<tjg/color/text_style.hpp>`  | Color values, emphasis, `text_style`, and style composition          |
| `<tjg/color/styled_text.hpp>` | Nested groups of styled text and their composition                       |
| `<tjg/backslash.hpp>`         | Backslash escaping and unescaping                                    |
| `<tjg/strip_ansi.hpp>`        | ANSI escape sequence removal from strings                            |

Use `<tjg/color.hpp>` for formatted output, SGR generation and parsing, or ANSI
stripping on nested groups of styled text. The narrower headers support code
that only needs the value types or string utilities. Headers in
`tjg/color/bits/` are implementation headers.

## CMake

Use CMake 3.31 or later. Configure and build the project from the repository
root, then install the headers, static archive, and `tjg::tjg` CMake target.

```sh
cmake -S . -B build/color-install -DCMAKE_BUILD_TYPE=Release
cmake --build build/color-install --config Release
cmake --install build/color-install --config Release --prefix /path/to/install
```

In your application, point `CMAKE_PREFIX_PATH` at the install prefix and add
the following to its CMake file.

```cmake
find_package(tjg CONFIG REQUIRED)
target_link_libraries(my_app PRIVATE tjg::tjg)
```

The target supplies the headers, C++23 requirement, and archive automatically.
CMake uses the platform's standard static-library name: `libcolor.a` on
Unix and MSYS2, or `color.lib` with MSVC. For a multi-configuration generator,
use the same `--config Release` when installing as when building.

For a direct GCC build, add the installed `include/` and `lib/` directories
and link with `-lcolor` after your application's objects. Compile-time color
and style operations and iterator-dependent formatting remain defined in
headers. Runtime functions, text parsing, and private Unicode data are
implemented in the archive. Policy macros must have consistent definitions
when building the library and its consumers.

## Regression tests

From the repository root, initialize the Google Test submodule:

```sh
git submodule update --init -- ext/gtest
```

Run `./build.bash` to configure, build, and run the TJG suite with GCC and
warnings treated as errors. To use a different compiler, configure the
standalone project with `-DTJG_TEST=ON`. Test sources live in `test/`. The
suite also checks that the installed package works after relocation.

## Documentation and licenses

With Python 3 and Doxygen available, configure CMake and build the guide from
the repository root.

```sh
cmake -S . -B build
cmake --build build --target doc
```

Open `build/doc-html/index.html`. The first documentation build installs the
pinned Python packages into a virtual environment under `build/`.

For a local server that refreshes as you edit, see the
[preview-server instructions](support/color-pages.md#local-preview-server).

- [Color user guide](https://tjgolubi.github.io/color/)
- [Color user guide source](doc/index.md)
- [Change log](CHANGELOG.md)
- [Project website and design rationale](https://color-kit-cpp23.tjgolubi.chatgpt.site)
- [License](LICENSE) and [Boost Software License](https://www.boost.org/LICENSE_1_0.txt)
