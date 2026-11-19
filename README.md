# Color coordination

Updated November 18, 2026.

These documents provide continuity between conversations about
[`tjgolubi/color`](https://github.com/tjgolubi/color). Keep them current as
handoff documents rather than appending an event log.

## Project baseline

{color} is a standalone C++23 header library for terminal colors and text
styles. It uses standard formatting and printing, with its color API in
namespace `tjg::color`. The main entry point is `<tjg/color.hpp>`.

The repository is a fresh start. Its existing implementation defines the
current design. The normalized RGB helpers are under review on a feature branch.
Describe what the code implements; record any uncertainty as a question rather
than inferring an intended change.

The source checkout's `README.md` provides the library overview, header map,
build instructions, and documentation links. `doc/` contains the user guide,
`include/tjg/` the implementation, `test/` the regression tests, and `demo/`
the examples and comparison programs. External-library comparisons belong in
the demo context. The user guide covers styled text; do not create a separate
`StyledText.md`.

## Current handoff

`dev` is pushed at `084b241518cd93f9957c71c023e3cd028a5e0e50` and remains the
integration baseline. Its latest commit restores the tracked demo Makefile. Terry authorized
squash-merging all of `fix/Demos` into `dev` as `e4b2730`. That integration tree
matches the feature tip
`4ca3a80acea98785175a7f74887e55c86713d69e`. Both branches remain on the remote.
The demo alignment, ostream comparison, Request ID restoration examples,
cropped screenshot, and initial-release guide cleanup are integrated.

`REF/user-guide` is pushed at `9f43e9bfab316965346d5812e871ac9adbfe4af7`.
This documentation-only revision replaces implementation terms such as tree, node, and leaf with text
and nested groups of styled text. It updates the library README and guide
pages `index.md`, `styled.md`, `print.md`, and `text-style.md`. No library code
or API changes are included. The revision is pushed for Terry's review; it
has not been integrated into `dev` or published to the Pages user guide.

Corner cases and existing explanations are retained for Terry to evaluate.
The revision uses "text span" in places; subsequent discussion identified
"text" or "styled text" as usually sufficient. No follow-up replacement has
been implemented or explicitly requested. See [Workflow.md](Workflow.md) for
the agreed reader-facing model and [BuildAndTest.md](BuildAndTest.md) for
verification and remaining checks.

Two topic branches are pushed and awaiting integration into `dev`:

- `ref/ShortNames` at `fc3ec5b3d3e7ef5509964557d9b32c2511861462` renames
  `cube_color` and `gray_color` to `cube` and `gray` across the library, guide,
  tests, and demos.
- `feat/FloatColors` at `8164ae56e060469b3fd94b4cdfff14fd553d8216` adds
  `color(red, green, blue)` and `color(grayscale)` for custom RGB colors on
  a 0-to-1 scale, plus the named RGB grays `gray_25`, `gray_50`, and
  `gray_75`. The one-argument overload supersedes the earlier `gray(double)`
  factory and frees `gray` for the palette type.

The two branches have separate histories. See [Workflow.md](Workflow.md) for
how the guide should introduce color choices and [BuildAndTest.md](BuildAndTest.md)
for verification.

The public marketing website is current at version 8, with the small example
and three table comparison pages, pinned screenshots, SGR explanations, and
{fmt} acknowledgment. Its copied demos and screenshot match `dev`; no website
refresh is needed after the squash. See [Website.md](Website.md) for publication
state and [BuildAndTest.md](BuildAndTest.md) for validation results.

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
