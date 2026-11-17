# Build and test

[Document map](README.md) · [Workflow](Workflow.md)

Updated November 17, 2026.

## Requirements and standard build

Build and test Color in C++23 mode. Use a compiler and standard library with
working `<format>`, `std::formattable`, and `<print>`. CMake checks these
facilities when tests are enabled. CMake 3.20 or later and a supported build
tool are required; Google Test is vendored in `ext/gtest/`.

From the library repository root, run:

```sh
./build.bash
```

The script configures `build/` with GCC (`g++`), Debug, C++23 required,
`TJG_TEST=ON`, and `TJG_WERROR=ON`; builds with four parallel jobs; and runs
CTest with failure output enabled. Warnings are treated as errors for the
project's test targets.

For another compiler or build configuration, use a separate build directory:

```sh
cmake -S . -B build/custom -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=23 \
  -DCMAKE_CXX_STANDARD_REQUIRED=ON -DTJG_TEST=ON -DTJG_WERROR=ON
cmake --build build/custom --parallel 4
ctest --test-dir build/custom --output-on-failure
```

The selected compiler must use a standard library providing the required
C++23 facilities; choosing a compiler executable alone does not ensure this.

Keep CMake build directories separate by platform, compiler, standard library,
build type, and sanitizer configuration. Inspect the cache and source checkout
before reusing a directory; stale settings or binaries do not validate the
current source. Keep documentation virtual environments specific to their
Python installation and platform, and recreate them if that installation
changes incompatibly.

## Focused checks and result reporting

For a focused color change, build and run the registered color target from
the library checkout root:

```sh
cmake --build build --target color-test --parallel 4
ctest --test-dir build -R '^color-test$' --output-on-failure
```

Use the build directory configured for the intended toolchain. Include related
wide-character, formatting, stream, ownership, or package checks when affected.
A focused pass establishes only that scope, not a full-suite pass. Broaden or
repeat checks when a change, failure, or unresolved concern justifies it.

Record the branch and full SHA, toolchain and standard library, build type,
options, commands, results, and individual skips. A successful CTest entry or
CI job can contain skipped Google Test cases. Inspect detailed output when
coverage is uncertain, and distinguish tests that passed from tests that
could not build or did not run. Distinguish observed results from reports by
others. CTest's `Testing/Temporary/LastTest.log` contains test output;
compiler diagnostics belong to the build output.

## Documentation checks

Python 3 and Doxygen must be available when configuring the documentation
target. From the library checkout root, use the documented commands:

```sh
cmake -S . -B build
cmake --build build --target doc
```

The target creates `build/doc-venv`, installs the hash-pinned packages from
`support/doc-requirements.txt`, and builds `build/doc-html/index.html` using
`support/mkdocs-pages.yml`. Reuse a compatible environment and reinstall from
the pinned requirements when dependency inputs change. Do not invoke release
or publication tooling merely to build the guide.

Build the guide after changes to API comments, Markdown, or reference rendering.
Library tests alone do not verify generated documentation. Doxygen can interpret
comment wrapping as list syntax; verify affected declarations and examples in
the generated HTML. The `::: name` reference blocks and `!!! note` blocks are
MkDocs syntax, so their appearance in raw GitHub Markdown does not establish
whether they render correctly. A successful guide build establishes generation,
not visual review or deployment; record those checks separately.

## Current local validation

Verified November 17, 2026, on `dev` at
`c576f5df6b4b7d2ba8fa59a2ac9acf9239a6d687`.

`./build.bash` completed successfully on Debian 13 with GCC 14.2.0 and CMake
4.4.5. All 22 CTest entries passed, including the no-exceptions configuration,
standalone API checks, and installed-package relocation test. The tracked
library working tree remained clean.

CMake is installed locally in this cloud workspace. Repeat the build here with:

```sh
cd /workspace/color
PATH=/workspace/.build-tools/cmake/data/bin:$PATH ./build.bash
```

That local full-suite result covers the initial snapshot's Debug configuration;
it is not a fresh full-suite run of later commits.

The current guide configuration built locally with the pinned Python packages
and Doxygen 1.9.8. All eight generated pages use `{color}` in their titles.
Canonical and repository links, the configured `dev` edit links, API rendering,
and both `tjg` and `tjg::color` documentation lookups passed checks. C++
identifiers such as the `Color` concept remain unchanged.

Doxygen is installed locally under `/workspace/.build-tools/doxygen`. This
workspace's executable needs
`LD_LIBRARY_PATH=/workspace/.build-tools/doxygen/usr/lib/x86_64-linux-gnu`.
The documentation virtual environment is `build/doc-venv`; use
`TJG_DOXYGEN=/workspace/.build-tools/doxygen/usr/bin/doxygen` and
`PYTHONPATH=support/python` for a direct MkDocs invocation. These paths are
workspace-specific, not additional project dependencies.

## Current GitHub CI validation

Verified November 17, 2026: all 11 jobs passed for `dev` at
`c17e87a881477ac3adea00f68cde8eacfb1c1a2e`.

| Workflow                                                                  | Configurations                                                        | Jobs | Result |
| ------------------------------------------------------------------------- | --------------------------------------------------------------------- | ---: | ------ |
| [Linux](https://github.com/tjgolubi/color/actions/runs/44025326570)       | GCC 14 and Clang 20/libc++ Debug and Release; GCC 14 Debug ASan/UBSan | 5    | Passed |
| [macOS](https://github.com/tjgolubi/color/actions/runs/44025326564)       | LLVM 20/libc++ Debug and Release                                      | 2    | Passed |
| [Windows](https://github.com/tjgolubi/color/actions/runs/44025326514)     | MSVC v143 x64 Debug and Release                                       | 2    | Passed |
| [Color guide](https://github.com/tjgolubi/color/actions/runs/44025326520) | Build and GitHub Pages publication                                    | 2    | Passed |

The nine platform jobs configure, build, and run the TJG regression suite in
C++23 mode with test warnings treated as errors. Matrix fail-fast is disabled.
CI evidence applies to the exact tested SHA, not later source or uncommitted
changes.

## Demo alignment candidate

`fix/Demos` is pushed at `acd98bddd545fe86b1e86637dff28302fd5d1b3b`, based on
`dev` at `c17e87a`. It updates only `demo/Cpp23Demo.cpp` and
`demo/FmtColorDemo0.cpp`: matching style and note names, corresponding comments,
modest section spacing, and a named `bold_underline` constant for the C++23
heading. The Color demo, displayed strings, and library headers are unchanged.
The candidate awaits Terry's review and is not integrated or published to Sites.

Both revised demos compile with GCC 14.2 in C++23 mode using
`-Wall -Wextra -Wpedantic -Werror`. The {fmt} comparison uses external upstream
{fmt} 10.2.1, header-only, from `/workspace/.build-tools/fmt-comparison`.
Captured output matches each original byte for byte: C++23 1,717 bytes,
{fmt} 1,916 bytes. All three demos have identical ordered dashboard-row comments.
Artifacts are in `build/demo-alignment/`. These are focused demo checks;
the full local regression suite was not rerun for this documentation-oriented
change. The comparisons are intended to show clear, idiomatic alternatives,
not make C++23 or {fmt} look artificially cumbersome.

All four workflows passed for this exact candidate SHA: all 10 executed jobs
passed. The Pages deployment job was correctly skipped because
this is not `dev`:

| Workflow    | Evidence                                                   |
| ----------- | ---------------------------------------------------------- |
| Linux       | https://github.com/tjgolubi/color/actions/runs/44026165378 |
| macOS       | https://github.com/tjgolubi/color/actions/runs/44026165359 |
| Windows     | https://github.com/tjgolubi/color/actions/runs/44026165424 |
| Guide build | https://github.com/tjgolubi/color/actions/runs/44026165367 |

CI success does not authorize integration. Terry is reviewing this branch.

## User-guide publication

The repository's Pages source is now GitHub Actions. The `github-pages`
environment permits `dev`. `.github/workflows/doc.yml` builds on pushes and
pull requests, uploads the guide artifact only for pushes to `dev`, and runs
a dependent Pages deployment job under the same condition. Deployments are
serialized without cancelling an active publication. Other branches, including
`docs/Coord` and feature branches, do not publish.

The live guide at https://tjgolubi.github.io/color/ returned HTTP 200 and
its title is `{color}` after the `c17e87a` deployment. The overview, Colors,
and Styled Arguments pages were also checked after initial publication.
Support configuration now uses this repository and `dev` edit links, and
publication instructions are in library `support/color-pages.md`.

The Pages upload action currently brings a nonfatal warning about its nested
`actions/upload-artifact` Node.js 20 runtime being forced onto Node.js 24.
Build and deployment still pass; this is not a deployment failure.

## Other workflow coverage

### Inherited workflow configuration

CodeQL and supply-chain workflows are enabled but their push triggers target
`main`, so they did not run for this `dev` push. Lint runs only on pull
requests. Recent Dependabot pull requests show failures in both the clang-format
and cmake-format jobs; those are separate from the successful `dev` push runs.
Dependabot and lint are inherited configuration that Terry has not adopted.
No adoption or repair of those inherited checks has been requested.

## Maintaining this document

Keep the current build procedure, verified baseline, and relevant limitations
here. When a failure is investigated, retain the actionable cause, remedy, and
reason where they remain useful. Replace superseded results rather than
accumulating a chronological history. Match local, GitHub, and workflow full
SHAs before citing CI; inspect every applicable job and record intentional
coverage gaps. Check CI on demand.
