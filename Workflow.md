# Workflow

[Document map](README.md)

Updated November 23, 2026.

## Authorization and scope

Modify project files only when Terry instructs us in the imperative mood.
Questions, observations, and statements of intent are discussion, not edit
authorization. Read-only inspection and CI checks needed to answer a prompt
are allowed.

Generally, if a prompt is a question, just answer the question without
modifying project files. Temporary scratch files for coding experiments or
verification needed to answer it are allowed. Keep them separate from the
project's source, tests, build configuration, and documentation; do not
integrate them into the project without an imperative instruction.

This is the prime directive. Apply it before every edit, including when a
design discussion seems complete or implementation seems like the natural
next step. "Can you do it now?" and "Can you implement that now?" are questions;
answer them without starting implementation. "Implement it now" and "Please
update the workflow document" authorize edits within their stated scope.
Words such as "now" do not turn a question into an imperative instruction.
Do not infer edit authorization from enthusiasm, agreement on a design, or
the absence of objections.

Before writing, identify the specific imperative instruction that authorizes
the edit and its scope. If none exists, answer the question using read-only
investigation or temporary scratch files as needed, and wait for an
instruction before changing the project. Do not create or integrate a new
file as a way around the restriction on modifying existing files. Permission
to draft a standalone file does not authorize changing headers, build files,
tests, or documentation to integrate it. An imperative instruction already
given remains sufficient for the work it authorizes; do not repeatedly ask
for confirmation within that scope.

Explain proposed changes before editing. An instruction authorizes the work
needed within its scope, not unrelated maintenance. Preserve explicit stopping
points such as "stop before committing." Discuss a change, implement it,
verify it, and review it before moving on.

Library and coordination commits, pushes, merges, branch switches, rebases,
deletions, and stashes require authorization for the relevant operation.
Terry normally performs the final commit and push. Authorization to edit or
prepare a squash does not authorize committing or pushing. Website publication
and issue updates also require instructions for those actions.

Before edits or branch changes, inspect the actual branch, commit, working
tree, and affected files. Resolve unrelated tracked changes with Terry rather
than discarding or stashing them automatically. Preserve concurrent edits and
re-read a file if it changes while preparing an update. A vi swap file can
indicate an active editing session. Coordinate with Terry before writing a
file he has open with unsaved changes.

When authorized work touches files with uncommitted changes, inspect and
record the relevant existing diffs before editing so the new work can be
reviewed or removed independently. Keep changes limited to the authorized
task. If asked to undo the assistant's work, reverse only its changes and
preserve Terry's earlier and concurrent edits. Do not use whole-file restores,
resets, or automatic stashes to recover from an authorization mistake.

Preserve untracked convenience scripts, archives, logs, and demo binaries.
Mention them when they affect the task, could be included accidentally, or
could conflict with a branch switch. Do not include them in commits or stashes
automatically.

## Project and coding guidance

Color is a standalone C++23 library with a compiled static archive, using
standard formatting and printing. Public headers retain constexpr operations
and templates that depend on caller types. Runtime implementations live in
`src/`; consumers link the existing `tjg::tjg` CMake target. Verify descriptions
of current behavior against the source and tests. Record uncertainty as a
question. External-library comparisons belong
in the demo context. The marketing homepage also credits
{fmt}'s inspiration and recommends it for visitors who cannot use C++23.
The user guide describes this initial release in the present tense: do not
include old API behavior, migration notes, or an upstream-extension narrative.
Keep required source attribution intact.

Constexpr support and speed take priority over reducing header content.
Before moving a function into a `.cpp` file, check whether it can be constexpr
or needs its caller's concrete types for efficient code generation. Ordinary
`char` and `wchar_t` runtime overloads can share private implementation code.
Keep `backslash.hpp` and the string `strip_ansi.hpp` algorithms in headers to
preserve their tested constexpr behavior.

Do not reintroduce `detail::output` or an equivalent erased callback per
output code unit. That bridge was removed because it added indirect calls
to iterator-dependent rendering. Keep those paths templated in headers;
discuss and measure performance tradeoffs before replacing them.

Mark non-throwing operations `noexcept`. Use the existing
`TJG_NOEXCEPT_UNLESS_BAD_ALLOC` policy where allocation failure is the sole
intended escaping exception. Do not suppress validation or formatting errors
with unconditional noexcept. Apply policy macros consistently to the compiled
library and its consumers.

Read the library README and relevant coordination documents before work.
State when needed material is missing or stale. Newer explicit instructions
from Terry take precedence over older documentation.

Keep edits minimal and follow the existing source style. Avoid unrelated
cleanup, declaration changes, or broad toolchain changes. Preserve existing
line endings and create new text files with LF; inspect Git attributes and
configuration before assuming checkout behavior.

For authored styling code, Terry prefers leading underscores on private member
variables and brace initialization. Prefer signed types unless an unsigned
type has a specific purpose. Treat size interfaces and packed representations
deliberately rather than changing them mechanically. Retain parentheses when
narrowing rules or initializer-list overload selection require them.

Order includes to expose missing direct dependencies:

1. The source file's corresponding header, when applicable.
2. Project headers, from most specific to most general.
3. Third-party headers.
4. Higher-level C++ standard facilities, then containers and general
   facilities, then foundational utilities.
5. C compatibility headers such as `<cstdio>`, `<cstdlib>`, `<cstdint>`, and
   `<cstddef>`, and platform C headers, last.

Use this order when adding or touching includes, following the existing
`.clang-format` categories. Discuss configuration changes before making them.

Terry prefers an 80-column limit. Keep a trailing return type and opening
brace on the signature line when they fit. If a trailing return type would
overflow, first move qualifiers before `auto` to a preceding line, preserving
them so `auto` becomes the first keyword on the signature line. If the return
type still does not fit, place `-> return_type` alone on the next line,
indented two spaces relative to the signature:

```cpp
[[nodiscard]] constexpr
auto function(arguments)
  -> return_type
{
```

This conditional layout preference is not fully expressed by the current
formatter configuration. Do not add noisy `clang-format off/on` comments
to force it; discuss formatter changes instead.

Assertions check assumptions about the code. Verify a public precondition
against the design and implementation before documenting it. Brace conditional
bodies containing assertion macros to avoid dangling-else constructs. Do not weaken compiler settings to bypass warnings. Formatting
passes and formatter-configuration changes need instructions; do not restyle
unrelated files. Check the generated guide when comment wrapping changes
because Doxygen can interpret wrapped text as list syntax.

## Documentation

The three document sets serve different readers.

- **User guide** lives in `doc/` at its existing paths. Lead with short
  examples for newcomers and link to advanced walkthroughs and the relevant
  API reference pages. Teach the valid input range and normal use of
  `color()`. Preserve existing detail during a future guide overhaul by
  moving it to the appropriate reference or advanced page.
- **API reference** lives in `doc/ref/`. Keep the Markdown readable directly.
  The landing page lists topics and public headers. Header indexes link to
  declarations, and entity pages show the public include and link back.
  Use exact API names in page titles for search and in filenames where
  practical. Use hyphens in prose filenames. Group overloaded functions on
  one page. Give each public class a folder with an `index.md` overview and
  dedicated member pages. Public nested classes get subfolders.
- **Design overview** belongs on `docs/Coord`. Record vision, rationale, and
  decisions about behavior users can rely on. Current implementation behavior
  and existing tests are evidence of what the library does today. Treat
  unresolved guarantees as open questions.

Under `doc/ref/color/`, document the umbrella include and use
`colors/`, `text_style/`, and `styled_text/` for the narrower headers. Group
SGR helpers in `color/sgr/` and link their pages to the umbrella include.
Document shared TJG utilities in `doc/ref/util/` with a single launch index,
direct includes, and dedicated API pages. Check whether a behavior is a
commitment before documenting it as a guarantee or enforcing it with a
regression test.

Reference entity pages always have Synopsis and Description, followed by
applicable sections in a consistent order. Give multiple overloads separate
descriptions; a single overload does not need an extra subsection. Class
overview pages link to constructor pages rather than repeating their prose.
Use tables with linked names and descriptions for member and non-member
functions and similar inventories. List associated free functions on the
relevant class page. Member-function categories may use Doxygen groups.
Use "Nested types" for class-scoped aliases and "Type definitions" for
namespace aliases, immediately before "Template parameters" where applicable.

Link declaration-page titles to committed source on GitHub. Keep topic-page
titles plain where no single source declaration is appropriate. Regenerate
permalinks with `support/reference-source-links.py` only when the source
revision and Doxygen XML match; see `support/color-pages.md`. Keep existing
permalinks until intentionally refreshing them, rather than changing every
link merely because a documentation commit changes HEAD.

## User-guide terminology and review

Use {color}'s print functions in examples that print styled arguments.
Prefer passing the styled values directly so printing can suppress generated
SGR on redirected output. A string formatted before the call can already
contain escape sequences. Use `namespace clr = tjg::color;` where a short
qualified call avoids ambiguity with a standard print overload.

Describe concatenated text and nested groups of styled text, with grouping
like parentheses and colors or emphasis applied to groups. Avoid exposing the
implementation as trees, nodes, roots, or leaves in user-facing explanations.
Preserve API identifiers and precise behavior while changing the language.

This terminology pass does not authorize removing explanations or corner
cases. Terry wants to decide which explanations readers need and which corner
cases to remove. Keep those details for his review. Do not assume that a
behavior is common sense and delete its explanation.

Use "text" or "styled text" where the distinction is clear. Use "text span"
where an individual piece's boundary matters, such as measuring display width
or handling escape sequences split across pieces. Use local namespace imports
in examples when they make styling expressions easier to read. For terminal
colors, use `using namespace tjg::color;` and `using enum term_color;` in
local scope when they keep expressions such as `fg(green)` readable. Check
for name collisions after removing qualification.

### Teaching color choices

The user guide teaches readers how to get the appearance they want. Lead
with `term_color` and a short example, then introduce named RGB colors. For
custom shades,
introduce `color(red, green, blue)` and `color(grayscale)` with inputs from
`0.0` to `1.0`. Both overloads return `rgb`. The one-argument form uses the
same value for all three channels.

The named neutral shades `rgb::dark_gray`, `rgb::gray`, and `rgb::light_gray`
match `color(0.25)`, `color(0.5)`, and `color(0.75)`, respectively. The guide
generates Neutral swatches from the named RGB constants.

Reserve direct `rgb{...}` construction and raw SGR for advanced material.
Indexed `gray` and `cube` serve readers who need precise SGR palette control
and understand how terminal palettes affect appearance. `term_color::gray` selects
slot 8, and `rgb::xterm_gray` is its fixed Xterm RGB counterpart (`#7F7F7F`).
Keep threading and implementation details out of the main explanation.

Use **current style** for the style tracked during formatting and **default
style** for `text_style{}`. Styled formatting and printing restore the
library-tracked entry style. Relative styles inherit unspecified colors and
combine emphasis with that style. At the outermost call, the tracked entry
style is the default style. Describe this behavior consistently across output
destinations.

## Repository and tools

The library repository is `tjgolubi/color`; its integration and default branch
is `dev`.
Coordination documents live at the root of the separate `docs/Coord` branch.
Inspect actual refs and worktrees before acting rather than assuming recorded
checkout state still holds.

On Terry's Windows/MSYS2 checkout, use MSYS2 Git only, never Windows Git.
Use `C:/msys64/usr/bin/git.exe` or `/usr/bin/git` from MSYS2 Bash. Put
`/usr/bin` on PATH for the MSYS2 build and documentation tools. The checkout
must preserve case-distinct paths such as `Color.md` and `color.md`; do not
rename them to work around a case-insensitive checkout.

Use the checkout's local toolchain and the GitHub connector for
remote inspection where appropriate. Machine-specific paths and tool versions
must be verified on the machine in use. Reuse existing Git identity, SSH
configuration, and credentials; keep credentials out of output and documents.

Use `git worktree list` to locate the checkouts before creating another one.
Enter the worktree for the branch you intend to work on. Do not switch the library checkout to a branch
already checked out in the coordination worktree. Registration and worktree
paths are local metadata, not setup commits or portable machine configuration.

Do not reset or synchronize a diverged checkout without authorization. Do not
push solely to preserve a cloud workspace. When requested, provide a backup
including source, uncommitted changes, and coordination documents. A local
commit alone does not establish durable workspace retention.

For cross-machine delivery, Terry prefers Git bundles over patches when
committing is authorized. Preserve exact commits and prerequisites, verify
bundle import separately, and provide fetch and integration commands. This
preference does not authorize commits or pushes.

## Branches and integration

Use `dev` to integrate features, fixes, and refactors. For a release, squash-merge
`dev` into `main`, then merge `main` back into `dev` before continuing work.
Neither `main` nor `master` exists in the inspected remote; create `main` when
Terry authorizes the first release. There was no committed `master` history to
rename. Release operations still need authorization.

Only pushes to `dev` publish the GitHub Pages user guide. Other branches and
pull requests can build the guide but must not deploy it. This includes
`docs/Coord`, `fix/Demos`, and a future `main` unless Terry changes that policy.


Create focused branches when authorized implementation begins from the agreed
baseline. Record the proposed name first. Use lowercase slash prefixes and
PascalCase subjects, such as `feat/Fluent`, `fix/Termux`, or `doc/ColorGuide`.
A proposed name or design entry does not authorize implementation.

Each accepted feature integration is one squash commit containing the
applicable source, tests, and documentation. Do not substitute a fast-forward
or ordinary merge. This policy does not authorize rewriting existing commits.

1. Confirm scope, baseline, dependencies, and preservation of local work.
2. Review the complete candidate, including source/API, binary/ABI, and
   stored-data compatibility where relevant. Unchanged size alone does not
   prove ABI compatibility.
3. Complete applicable source, tests, and user documentation, and run relevant
   local checks. Use the library README and `build.bash` for the standard build
   and regression procedure.
4. Terry pushes the candidate, or explicitly authorizes the assistant to push.
   Match the full local, remote, and CI commit SHAs. Every applicable workflow
   and matrix job must pass for that exact candidate before squash preparation.
   Queued, running, failed, cancelled, or missing expected jobs are not passes.
   Verify the feature is actually committed in the pushed tree.
5. Obtain authorization for the squash onto the agreed baseline. Prepare and
   verify it, then stop uncommitted for Terry's review unless instructed
   otherwise. A squash stages changes; review them with `git diff --cached`.
6. Terry commits and pushes the final integration, or explicitly authorizes
   those operations. Verify the resulting commit structure, matching full
   SHAs, and applicable CI results for the final commit.

CI results apply to the exact commit tested. When CI is required after an
amendment, rebase, or change to the integration tree, verify the resulting
SHA. Record intentional exclusions and distinguish local checks from remote
CI.

When Terry explicitly chooses CI on the final push for a batch of dependent
candidates, test the first squash locally on `dev`. Rebase each subsequent
candidate onto the updated `dev`, run the full local checks, and verify that
the resulting squash tree matches the tested candidate. Retain one squash
commit per candidate and verify every applicable CI job on the final pushed
SHA.

Check CI on demand; do not start periodic polling, cancel runs, or change
workflow policies without instruction. Batch authorized changes before pushes
to conserve Actions compute. Keep matrix fail-fast disabled so all jobs can
finish. Do not trigger unrelated release, security, or publication workflows
merely to broaden a validation claim.

Dependabot and lint are inherited configuration that Terry has not adopted.
Do not treat their presence as a request to maintain or modify them. Inspect
actual workflow triggers when determining applicable CI; a workflow being
enabled does not establish that it ran on a particular branch or commit.

Put build requirements, procedures, exact validation results, and coverage
limitations in [BuildAndTest.md](BuildAndTest.md). The coordination README should
refer to that document rather than repeat recent test results.

## Commits, releases, and history

Use Conventional Commits, such as `feat(color): named RGB constants` or
`fix(docs): correct the user guide`. Color is a fresh, unreleased project;
do not carry forward compatibility obligations, aliases, or breaking-change
markers from earlier development. Describe the actual effects of changes
without promising stable numeric or binary representations. Use Markdown
backticks around identifiers where appropriate. Keep subjects within 80
columns and wrap commit message bodies at 80 columns.

Do not generate changelogs, assign release numbers, or create or push tags
without instruction. Verify the current repository's release tooling before
using it. Published release tags stay fixed.

Before an authorized history rewrite, record the old tip and coordinate with
other checkouts. Resolve conflicts deliberately, compare content, and rerun
checks. Use an authorized `--force-with-lease` rather than unguarded force;
a lease protects the expected remote ref, not the intended content. Inspect
refs and reflogs before synchronizing another machine. Never force-push older
history merely to make a rejected push succeed.

## Coordination and website maintenance

Maintain a coherent account of current state, accepted behavior, constraints,
and open decisions. Replace superseded statements rather than appending a
chronological log. Keep only provenance needed to identify the baseline and
validation. Distinguish proposals, implementation, tested results, and
acceptance.

Keep Markdown table columns aligned for readability in Vim. Avoid competing
authoritative copies in attachments. Report library and coordination statuses
separately, including whether edits are local, committed, or pushed. Another
machine cannot obtain unpushed local edits from GitHub.

When asked to update both website and coordination documents, publish and
verify the authorized website update first, then record the confirmed version,
source, and deployment result. A prepared website edit is not a confirmed
publication. See [Website.md](Website.md) for detailed website procedures.
