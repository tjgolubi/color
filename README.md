# Color coordination

Updated November 19, 2026.

These documents provide continuity between conversations about
[`tjgolubi/color`](https://github.com/tjgolubi/color). Keep them current as
handoff documents rather than appending an event log.

## Project baseline

{color} is a standalone C++23 header library for terminal colors and text
styles. It uses standard formatting and printing, with its color API in
namespace `tjg::color`. The main entry point is `<tjg/color.hpp>`.

The repository is a fresh start. Its existing implementation defines the
current design. Describe what the code implements and record any uncertainty
as a question.

The source checkout's `README.md` provides the library overview, header map,
build instructions, and documentation links. `doc/` contains the user guide,
`include/tjg/` the implementation, `test/` the regression tests, and `demo/`
the examples and comparison programs. External-library comparisons belong in
the demo context. The user guide covers styled text; do not create a separate
`StyledText.md`.

## Current handoff

The integration baseline is pushed on `dev` at
`15cf6cee9c1ea49f199ce2bca236c7378cd2602f`. The squash of `fix/DarkGray`
matches the source, guide, and tests at feature tip `4141518`.

The library provides constexpr normalized RGB and grayscale `color(...)`
overloads, the indexed `cube` and `gray` types, and `term_color::gray` for
terminal palette slot 8. The user guide explains styling
with nested groups, uses shorter styling expressions, and includes an SGR
format-and-parse walkthrough. The seven demos use the current names and source
files. `build.bash` runs the regression suite and builds the HTML guide.

The GitHub Pages guide and public marketing site are current. The marketing
site is at version 13 and its demo downloads and comparisons match `dev`.
See [BuildAndTest.md](BuildAndTest.md) for checks and [Website.md](Website.md)
for deployment provenance.

## Coordination documents

This README, `Workflow.md`, `BuildAndTest.md`, and `Website.md` are the current
coordination documents for Color.

| Document                           | Purpose                                                              |
| ---------------------------------- | -------------------------------------------------------------------- |
| [BuildAndTest.md](BuildAndTest.md) | Record build requirements, test procedures, and verified results.    |
| [Website.md](Website.md)           | Record website content, publication state, and maintenance guidance. |
| [Workflow.md](Workflow.md)         | Record working rules and repository procedures.                      |

The source code and user guide define Color's current design. A separate
`CppDesign.md` is retired from the coordination plan. Useful rationale belongs
near the relevant implementation or in the guide, after verification against
the current code. Any reference material consulted later must be checked
against this repository and current instructions before being carried forward.

## Working rules

Change project files only when Terry gives an imperative instruction.
Questions, observations, and discussion of possibilities do not authorize
edits. Newer explicit instructions take precedence over older documentation.

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
