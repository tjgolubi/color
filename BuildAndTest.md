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

Demos and a local documentation build have not been verified in this
conversation. This local result covers the script's Debug configuration.

## Current GitHub CI validation

The four push workflows completed successfully for the same full SHA above
on `dev`. All ten jobs passed:

| Workflow                                                                  | Configurations                                                                                     | Jobs | Result |
| ------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------- | ---: | ------ |
| [Linux](https://github.com/tjgolubi/color/actions/runs/44007727703)       | GCC 14 Debug and Release; Clang 20 with libc++ Debug and Release; GCC 14 Debug with ASan and UBSan | 5    | Passed |
| [macOS](https://github.com/tjgolubi/color/actions/runs/44007727806)       | LLVM 20 with libc++, Debug and Release                                                             | 2    | Passed |
| [Windows](https://github.com/tjgolubi/color/actions/runs/44007727657)     | MSVC v143, x64, Debug and Release                                                                  | 2    | Passed |
| [Color guide](https://github.com/tjgolubi/color/actions/runs/44007727728) | User-guide build                                                                                   | 1    | Passed |

The nine platform jobs configure, build, and run the TJG regression suite in
C++23 mode with test warnings treated as errors. Matrix fail-fast is disabled.
The guide workflow builds the documentation; it does not deploy it.

These workflows trigger on pushes and pull requests. CI evidence applies to
the exact tested SHA, not later source or uncommitted changes.

## Other workflow coverage

### Outstanding: publish the user guide

The `dev` guide workflow passes its build but has no GitHub Pages deployment
step. `https://tjgolubi.github.io/color/` returned HTTP 404 when checked on
November 17, 2026. A successful documentation build does not publish the guide.

Terry wants guide publication repaired. The workflow and Pages configuration
still need inspection and an authorized update, followed by verification of
both deployment and the live guide. No deployment repair has been made.
See [Website.md](Website.md) for the marketing site's guide links and fallback.

### Inherited workflow configuration

CodeQL and supply-chain workflows are enabled but their push triggers target
`main`, so they did not run for this `dev` push. Lint runs only on pull
requests. Recent Dependabot pull requests show failures in both the clang-format
and cmake-format jobs; those are separate from the successful `dev` push runs.
Dependabot and lint are inherited configuration that Terry has not adopted.
No configuration changes or fixes have been authorized.

## Maintaining this document

Keep the current build procedure, verified baseline, and relevant limitations
here. When a failure is investigated, retain the actionable cause, remedy, and
reason where they remain useful. Replace superseded results rather than
accumulating a chronological history. Match local, GitHub, and workflow full
SHAs before citing CI; inspect every applicable job and record intentional
coverage gaps. Check CI on demand.
