# Color coordination

Updated November 21, 2026.

These documents provide continuity between conversations about
[`tjgolubi/color`](https://github.com/tjgolubi/color). Keep them current as
handoff documents rather than appending an event log.

## Project baseline

{color} is a standalone C++23 library for terminal colors and text
styles. It uses standard formatting and printing, with its color API in
namespace `tjg::color`. The main entry point is `<tjg/color.hpp>`.

The repository is a fresh start. Its existing implementation defines the
current design. Describe what the code implements and record any uncertainty
as a question.

The source checkout's `README.md` provides the library overview, header map,
build instructions, and documentation links. `doc/` contains the user guide,
`include/tjg/` the public headers and constexpr/template definitions, `src/`
the compiled implementation, `test/` the regression tests, and `demo/`
the examples and comparison programs. External-library comparisons belong in
the demo context. The user guide covers styled text; do not create a separate
`StyledText.md`.

## Current handoff

The local and pushed `dev` tips match at
`cbc6c9ab26b5a1a7635bdade5d902966876d30ac`. The checkout is clean. The
three squash commits on `dev`, in integration order, are:

1. `1175ed1` (`ref/XtermColors`) renames fixed palette RGB constants to
   `rgb::xterm_*`. Terminal palette slots still use `term_color`.
2. `1b3c596` (`feat/SoftHyphen`) adds soft-hyphen, ideographic, and no-break
   space handling to `word_wrap()`.
3. `cbc6c9a` (`feat/Wrapped`) adds `wrapped()` and includes the WrapTable
   inner border styling.

`feat/Tagged` still points to `ea73549`. The current `dev` contains its fixed
Xterm RGB names and enhanced wrapping prerequisites. Start Tagged from this
baseline when Terry authorizes the branch update. See
[TaggedRequirements.md](TaggedRequirements.md) for the parser design.

The project builds a static color archive using standard platform names:
`libcolor.a` on Unix/MSYS2 and `color.lib` with MSVC. Consumers still use
`find_package(tjg CONFIG REQUIRED)` and link `tjg::tjg`. See
[BuildAndTest.md](BuildAndTest.md) for build, install, and validation details.
Preserve constexpr support and speed ahead of reducing header content.
Iterator-dependent rendering remains in headers; the per-character erased
output bridge was removed.

The library provides constexpr normalized RGB and grayscale `color(...)`
overloads, the indexed `cube` and `gray` types, and `term_color::gray` for
terminal palette slot 8. The user guide explains styling
with nested groups, uses shorter styling expressions, and includes an SGR
format-and-parse walkthrough. The repository includes eight demos.
`build.bash` runs the regression suite and builds the HTML guide.

Marketing site version 18 uses the current `dev` snapshot for its demo
downloads and source links. The user guide and API reference are live on
GitHub Pages.
See [BuildAndTest.md](BuildAndTest.md) for checks and [Website.md](Website.md)
for deployment provenance.

## API reference baseline

The [API reference](https://tjgolubi.github.io/color/ref/index.html) is
maintained in `doc/ref/` on `dev` and published with the user guide.
The reference has topic and public-header indexes, dedicated API pages, and
class folders with member pages. The existing user guide remains in `doc/`.
The review changes are implemented: consistent sections and overload
descriptions, linked member tables, Xterm palette guidance, public `style`
parameter names, and reduced implementation prose. Declaration-page titles
link to GitHub source permalinks; topic titles remain plain. The source-link
generator and usage instructions live in `support/`.

Preserve source-title permalinks until the Doxygen XML and the committed source
revision are ready for a coordinated refresh.
User-guide simplification remains pending Terry's review and instructions.

## Wrap handoff

`word_wrap()` returns unpadded lines of narrow or wide styled text. It takes a
`std::size_t` width of at least four display columns. Soft hyphens mark
preferred breaks, adjacent ideographs can split without a hyphen, and U+00A0
keeps adjacent text together when it fits a full line. `demo/WrapTable.cpp`
shows how to align the returned lines in colored table cells.

`wrapped()` formats or streams narrow styled prose using `word_wrap()`. It
takes its width from the format field or `std::setw`, defaults to 80 columns,
and separates lines without a trailing newline. See the
[`word_wrap()` reference](https://tjgolubi.github.io/color/ref/color/styled_text/word_wrap.html),
[`wrapped()` reference](https://tjgolubi.github.io/color/ref/color/wrapped.html),
and [WrapTable walkthrough](https://tjgolubi.github.io/color/wrap-table.html).
The Unicode License V3 is recorded in `THIRD-PARTY-NOTICES`.

## Coordination documents

These coordination documents live on `docs/Coord` and are committed separately
from the library. Updating documents does not authorize committing or pushing
them; those operations need Terry's instructions.

| Document                                       | Purpose                                               |
| ---------------------------------------------- | ----------------------------------------------------- |
| [BuildAndTest.md](BuildAndTest.md)             | Build requirements, procedures, and verified results. |
| [TaggedRequirements.md](TaggedRequirements.md) | Draft parser behavior and acceptance examples.        |
| [Website.md](Website.md)                       | Website content, publication state, and maintenance.  |
| [Workflow.md](Workflow.md)                     | Working rules and repository procedures.              |

A design overview belongs with the coordination documents. It will record
the library's vision, design decisions, and rationale. See
[Workflow.md](Workflow.md#documentation) for the roles of the user guide,
API reference, and design overview.

## Working rules

Change project files only when Terry gives an imperative instruction.
Questions, observations, and discussion of possibilities do not authorize
edits. Answer questions without changing project files; temporary scratch
files for experiments are allowed. Newer explicit instructions take
precedence over older documentation.

Keep coordination documents on the separate `docs/Coord` branch so they remain
available while library work moves between branches. Use `git worktree list` to locate the library and coordination checkouts.

## Build and tests

See [BuildAndTest.md](BuildAndTest.md) for build requirements, procedures,
current local and GitHub CI results, and coverage limitations.

## Project references

- [Repository](https://github.com/tjgolubi/color)
- [User guide](https://tjgolubi.github.io/color/)
- [Project website](https://color-kit-cpp23.tjgolubi.chatgpt.site)

See [Website.md](Website.md) for deployment details. The library README links
to the current public site.
