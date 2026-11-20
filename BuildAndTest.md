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

The CMake target `tjg` now builds a static archive from the six `.cpp` files
in `src/`. Its output name is `color`: `build/libcolor.a` in the MSYS2 build,
or `color.lib` with MSVC. `TJG_WERROR` covers both library and test warnings.
Build only the archive with `cmake --build build --target tjg`.

The installed package contains the archive, headers, and `tjg::tjg` target.
Consumers use `find_package(tjg CONFIG REQUIRED)` and link that target to
obtain the archive, include path, and C++23 requirement. An include path alone
does not supply compiled runtime functions. Example build and install:

```sh
cmake -S . -B build/install -DCMAKE_BUILD_TYPE=Release -DTJG_TEST=OFF
cmake --build build/install --config Release
cmake --install build/install --config Release --prefix /path/to/install
```

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
user guide at `build/doc-html/index.html`, including the API reference at
`build/doc-html/ref/index.html` on the current feature branches. Reuse a
compatible environment and reinstall from
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

## Integration-baseline GitHub CI validation

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

## Runtime-library validation and active wrap baseline

The active `feat/Wrap` checkout is at
`e5c1cd09f9bd8614ddfa2b05d41a90703ed6744d`, also the inspected
`origin/ref/RuntimeCpp` tip. Terry reported pushing that refactor. `wrap()`
is not implemented; see [WrapDesign.md](WrapDesign.md) for its agreed behavior.

On November 20, 2026, the runtime-refactor working tree passed the full build
and all 22 registered CTest entries after removal of `detail::output`.
The build used MSYS2 GCC 16.2.0/libstdc++, Debug, C++23, `TJG_TEST=ON`, and
`TJG_WERROR=ON`. These checks ran before the refactor commit; no new tests
were run merely to update these coordination documents.

The installed-package test built the archive separately, installed and
relocated it, then built and ran a consumer using `find_package(tjg)`.
It verified a static imported target, C++23 propagation, and narrow/wide
formatting, parsing, and stream linkage. The allocation-policy tests also
cover noexcept guarantees and constant initialization of default narrow
and wide styled-text objects.

The strict documentation build passed with the restored iterator-based
rendering and quoting templates. A separate library build with
`-fno-exceptions -DTJG_NOEXCEPT_UNLESS_BAD_ALLOC=noexcept` passed and linked
and ran `test/noexception-test.cc` as a smoke test. Use matching flags for
the library and consumer; compiling only a consumer without exceptions does
not establish that the archive itself supports that configuration.

The five standalone demos built and ran during the archive refactor, before
the erased output bridge was removed. They were not rerun after its removal.
The full CTest and package checks above are the later validation. No speed
benchmark or cross-platform CI result was established for this refactor.
Earlier `dev` CI results do not validate this SHA. Build logs under `build/`
are temporary and some were subsequently removed; the recorded results here
describe observed runs, not a promise that those log files still exist.

## API reference baseline and source links

The preceding API reference baseline on `feat/CppRef` is
`0bdfa029668fb4650d619d88870784b86e3e49e3`, matching the inspected local
remote-tracking ref. The runtime-library refactor builds on that baseline.

The strict MkDocs builds use the following command from the MSYS2 shell
with `/usr/bin` on PATH:

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

At the API reference baseline, the source-title check passed for 173 linked
declaration titles, with four topic titles unchanged and no updates needed:

```sh
python support/reference-source-links.py \
  --revision 92039b88e7f226935de41ed533b8601ddeff5517 --check
```

That SHA is the committed source revision used by the existing permalinks,
not the current runtime-library commit. This is a recorded baseline check;
do not use that command with XML generated from the refactored source as
proof that the older revision matches. Do not regenerate the links against
a new revision without refreshing and matching the Doxygen XML first.
The earlier temporary generated-HTML audit script is no longer present;
the final pre-commit check established source-title mappings and strict
generation, not a fresh exhaustive HTML-link or visual review.

To preview locally, use the same handler environment and replace the MkDocs
`build` command with `serve --config-file support/mkdocs-pages.yml`. Follow
the URL printed by MkDocs.

GitHub CI has not been inspected for the active runtime/wrap baseline. Earlier
runs do not establish its result. No reference publication or deployment was
performed in this session; guide publication remains restricted to `dev`.

## Demo comparisons

`make -C demo run` builds and runs all seven demos. `Result42Compare` and
`TableDemoFmt` require a built copy of {fmt}. The Makefile builds and links the
color archive, using `TJG_BUILD=../build` and `TJG_LIB=$(TJG_BUILD)/libcolor.a`
by default. Use a matching compiler and standard library for archive and demos.
The individual standalone targets use the C++ standard library, with {color}
where applicable. The dashboard examples include the final cyan Request ID
and plain suffix, and the original
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
