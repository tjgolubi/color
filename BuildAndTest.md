# Build and test

[Document map](README.md) · [Workflow](Workflow.md)

Updated November 20, 2026.

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
`TJG_TEST=ON`, and `TJG_WERROR=ON`. It builds with four parallel jobs, runs
CTest with failure output enabled, then builds the guide with the `doc` target.
The full script requires Python 3 and Doxygen as well as the C++ toolchain.
Use the configure, build, and CTest commands below for a tests-only run.

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
`support/doc-requirements.txt`, and uses `support/mkdocs-pages.yml` to build the
user guide at `build/doc-html/index.html`. On `feat/CppRef` it also builds the
API reference at `build/doc-html/ref/index.html`. Reuse a compatible environment and reinstall from
the pinned requirements when dependency inputs change. Do not invoke release
or publication tooling merely to build the guide.

Build the guide after changes to API comments, Markdown, or reference rendering.
Library tests alone do not verify generated documentation. Doxygen can interpret
comment wrapping as list syntax; verify affected declarations and examples in
the generated HTML. The `::: name` reference blocks and `!!! note` blocks are
MkDocs syntax, so their appearance in raw GitHub Markdown does not establish
whether they render correctly. A successful guide build establishes generation,
not visual review or deployment; record those checks separately.

## Integration-baseline local validation

On November 19, 2026, the focused `color-test` CTest entry passed for the
`fix/DarkGray` working tree committed as
`41415189bf96a6d4084c1cb9338c48c69370548b`, whose contents match current
`dev`. The build used GCC 14.2.0 with libstdc++, CMake 4.4.5, Debug, C++23,
`TJG_TEST=ON`, and `TJG_WERROR=ON`. The normalized grayscale case ran and
passed. The MkDocs guide build succeeded with Doxygen 1.9.8 and the pinned
Python dependencies. The generated HTML was checked for the five gray
swatches and the updated styled-output samples.

## Current GitHub CI validation

Verified November 19, 2026, for `dev` at
`15cf6cee9c1ea49f199ce2bca236c7378cd2602f`. All nine platform jobs and both
documentation jobs passed.

| Workflow                                                                  | Configurations                                                             | Jobs | Result |
| ------------------------------------------------------------------------- | -------------------------------------------------------------------------- | ---: | ------ |
| [Linux](https://github.com/tjgolubi/color/actions/runs/44628242613)       | GCC 14 and Clang 20/libc++ Debug and Release, plus GCC 14 Debug ASan/UBSan |    5 | Passed |
| [macOS](https://github.com/tjgolubi/color/actions/runs/44628242555)       | LLVM 20/libc++ Debug and Release                                           |    2 | Passed |
| [Windows](https://github.com/tjgolubi/color/actions/runs/44628242835)     | MSVC v143 x64 Debug and Release                                            |    2 | Passed |
| [Color guide](https://github.com/tjgolubi/color/actions/runs/44628242552) | Build and GitHub Pages publication                                         |    2 | Passed |

The nine platform jobs configure, build, and run the TJG suite in C++23 mode
with warnings treated as errors. Matrix fail-fast is disabled. The results
apply to this exact commit.

The normalized RGB regression test exposed a constant-evaluation failure on
Clang/libc++ and MSVC when the implementation used `std::floor`. The guarded
positive-range cast preserves the quantization and supports constant evaluation
on all tested toolchains. Keep the compile-time regression check.

## API reference candidate

The current `feat/CppRef` candidate is
`0bdfa029668fb4650d619d88870784b86e3e49e3`, matching the inspected local
remote-tracking ref. Its tree is identical to the initially created local
commit `5b9d20c`; use the current full SHA for subsequent CI checks.

On November 20, 2026, after removing the experimental `wrap()` feature,
configuration, the full build, and all 22 registered CTest entries passed in
the MSYS2 GCC/libstdc++ environment. The configured compiler is
`/usr/bin/g++.exe`, with Debug, C++23, `TJG_TEST=ON`, and `TJG_WERROR=ON`.
No failed or skipped Google Test markers were found in the retained
`build/Testing/Temporary/LastTest.log`. These checks ran on the working tree
subsequently committed with the reference changes; they were not rerun after
the commit. No wrap tests or implementation remain.

Immediately before committing, the strict MkDocs build passed again using
the following command from the MSYS2 shell with `/usr/bin` on PATH:

```sh
PYTHONPATH="$PWD/support/python" \
TJG_DOXYGEN="$(command -v doxygen)" \
TJG_DOXYXML="$PWD/build/doxyxml" \
build/doc-venv/bin/python -m mkdocs build --strict \
  --config-file support/mkdocs-pages.yml \
  --site-dir "$PWD/build/doc-html" --no-directory-urls
```

`PYTHONPATH` supplies the repository's custom C++ mkdocstrings handler.
Installing base `mkdocstrings` alone does not supply that handler. Use the
pinned documentation environment and the configured build target or the
environment above; see `support/color-pages.md` for troubleshooting.

The source-title check passed for 173 linked declaration titles, with four
topic titles unchanged and no updates needed:

```sh
python support/reference-source-links.py \
  --revision 92039b88e7f226935de41ed533b8601ddeff5517 --check
```

That SHA is the committed source revision used by the existing permalinks,
not the current documentation commit. Do not regenerate the links against
a new revision without refreshing and matching the Doxygen XML first.
The earlier temporary generated-HTML audit script is no longer present;
the final pre-commit check established source-title mappings and strict
generation, not a fresh exhaustive HTML-link or visual review.

To preview locally, use the same handler environment and replace the MkDocs
`build` command with `serve --config-file support/mkdocs-pages.yml`. Follow
the URL printed by MkDocs.

GitHub CI has not been inspected for this exact candidate. Earlier candidate
runs do not establish its result. No reference publication or deployment was
performed in this session; guide publication remains restricted to `dev`.

## Demo comparisons

`make -C demo run` builds and runs all seven demos. `Result42Compare` and
`TableDemoFmt` require a built copy of {fmt}. The individual standalone targets
use the C++ standard library, with {color} where applicable. The dashboard
examples include the final cyan Request ID and plain suffix, and the original
cropped screenshot is `demo/TableDemo.png` (1480 × 440). Keep comparisons clear
and idiomatic, with corresponding style names and sections where appropriate.

## User-guide publication

The GitHub Pages guide is published by `.github/workflows/doc.yml`. The
workflow builds on pushes and pull requests. Pushes to `dev` also upload the
guide artifact and run the dependent Pages deployment. Deployments are
serialized without cancelling an active publication.

Both jobs passed for the current `dev` commit. The live
[Named Colors page](https://tjgolubi.github.io/color/named-colors.html#neutral)
returned HTTP 200 and included the `rgb::dark_gray` swatch. Publication
instructions are in the library's `support/color-pages.md`.

## Other workflow coverage

### Inherited workflow configuration

CodeQL and the supply-chain workflow have push triggers for `main`. Lint
runs on pull requests. Those checks were outside the current `dev` push
matrix. Dependabot and lint remain inherited configuration.

## Maintaining this document

Keep the current build procedure, verified baseline, and relevant limitations
here. When a failure is investigated, retain the actionable cause, remedy, and
reason where they remain useful. Replace superseded results rather than
accumulating a chronological history. Match local, GitHub, and workflow full
SHAs before citing CI; inspect every applicable job and record intentional
coverage gaps. Check CI on demand.
