# Color coordination

Updated November 17, 2026.

These documents provide continuity between conversations about
[`tjgolubi/color`](https://github.com/tjgolubi/color). Keep them current as
handoff documents rather than appending an event log.

## Project baseline

{color} is a standalone C++23 header library for terminal colors and text
styles. It uses standard formatting and printing, with its color API in
namespace `tjg::color`. The main entry point is `<tjg/color.hpp>`.

The repository is a fresh start. Its existing implementation defines the
current design. There is no planned redesign or new feature work at present.
Describe what the code implements; record any uncertainty as a question rather
than inferring an intended change.

The source checkout's `README.md` provides the library overview, header map,
build instructions, and documentation links. `doc/` contains the user guide,
`include/tjg/` the implementation, `test/` the regression tests, and `demo/`
the examples and comparison programs. External-library comparisons belong in
the demo context.

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
available while library work moves between branches. In this cloud workspace,
the library checkout is `/workspace/color` and the coordination worktree is
`/workspace/color-coord`. These paths describe this workspace only.

## Build and tests

See [BuildAndTest.md](BuildAndTest.md) for build requirements, procedures,
current local and GitHub CI results, and coverage limitations.

## Project references

- [Repository](https://github.com/tjgolubi/color)
- [User guide](https://tjgolubi.github.io/color/)
- [New website, private review](https://color-kit-cpp23.tjgolubi.chatgpt.site)

See [Website.md](Website.md) for deployment details, the outstanding guide
publication issue, and the different website address still in the library README.
