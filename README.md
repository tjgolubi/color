# Color coordination

Updated November 20, 2026.

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

The integration baseline remains `dev` at
`15cf6cee9c1ea49f199ce2bca236c7378cd2602f`. The squash of `fix/DarkGray`
matches the source, guide, and tests at feature tip `4141518`.

The active library checkout is `feat/Wrap` at
`e5c1cd09f9bd8614ddfa2b05d41a90703ed6744d`. This runtime-library refactor
is also the inspected `origin/ref/RuntimeCpp` tip; Terry reported pushing it.
There are no tracked library edits. `ViewWeb.bash` remains untracked.

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
format-and-parse walkthrough. The seven demos use the current names and source
files. `build.bash` runs the regression suite and builds the HTML guide.

The last recorded marketing publication is version 13, with demo downloads
and comparisons matching `dev`. The API reference changes on `feat/CppRef`
have not been published to GitHub Pages.
See [BuildAndTest.md](BuildAndTest.md) for checks and [Website.md](Website.md)
for deployment provenance.

## API reference baseline

The plain-Markdown API reference is on `feat/CppRef` at
`0bdfa029668fb4650d619d88870784b86e3e49e3`, matching the local
`origin/feat/CppRef` tracking ref at this inspection. Start at
[doc/ref/index.md](https://github.com/tjgolubi/color/blob/feat/CppRef/doc/ref/index.md).
The reference has topic and public-header indexes, dedicated API pages, and
class folders with member pages. The existing user guide remains in `doc/`.
The review changes are implemented: consistent sections and overload
descriptions, linked member tables, Xterm palette guidance, public `style`
parameter names, and reduced implementation prose. Declaration-page titles
link to GitHub source permalinks; topic titles remain plain. The source-link
generator and usage instructions live in `support/`.

The runtime-library refactor builds on this reference baseline. Existing
source-title links still target their recorded source revision; do not
refresh them against mismatched XML or an uncommitted source tree.
User-guide simplification remains pending Terry's review and instructions.

## Wrap handoff

The earlier `wrap()` implementation was removed at Terry's instruction.
The replacement's behavior is now agreed and recorded in
[WrapDesign.md](WrapDesign.md), including both character types, display widths,
whitespace/control filtering, punctuation, hyphenation, and style preservation.
No blocking design questions remain. No wrap implementation or wrap-specific
tests are present. Read the design before work and wait for an imperative
implementation instruction; design agreement and document updates do not
authorize coding. Terry wants wrapping in its own commit.

## Coordination documents

These coordination documents live on `docs/Coord` and are committed separately
from the library. Updating documents does not authorize committing or pushing
them; those operations need Terry's instructions.

| Document                           | Purpose                                               |
| ---------------------------------- | ----------------------------------------------------- |
| [BuildAndTest.md](BuildAndTest.md) | Build requirements, procedures, and verified results. |
| [Website.md](Website.md)           | Website content, publication state, and maintenance.  |
| [Workflow.md](Workflow.md)         | Working rules and repository procedures.              |
| [WrapDesign.md](WrapDesign.md)     | Agreed wrap behavior and implementation lessons.      |

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
