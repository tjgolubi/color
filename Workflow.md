# Workflow

[Document map](README.md)

Updated November 19, 2026.

## Authorization and scope

Modify project files only when Terry instructs us in the imperative mood.
Questions, observations, and statements of intent are discussion, not edit
authorization. Read-only inspection and CI checks needed to answer a prompt
are allowed.

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

Preserve untracked convenience scripts, archives, logs, and demo binaries.
Mention them when they affect the task, could be included accidentally, or
could conflict with a branch switch. Do not include them in commits or stashes
automatically.

## Project and coding guidance

Color is a standalone C++23 header library using standard formatting and
printing. The existing implementation defines the current design. Derive design descriptions from the
current source and tests. The source code and user guide define the design;
do not maintain a separate `CppDesign.md`. Preserve useful rationale near the
implementation or in the guide after checking it against the current code.
Record uncertainty as a question, not an inferred plan. External-library
comparisons belong in the demo context. The marketing homepage also credits
{fmt}'s inspiration and recommends it for visitors who cannot use C++23.
The user guide describes this initial release in the present tense: do not
include old API behavior, migration notes, or an upstream-extension narrative.
Keep required source attribution intact.

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
brace on the signature line when they fit; otherwise prefer:

```cpp
auto function(arguments)
  -> return_type
{
```

This conditional layout preference is not fully expressed by the current
formatter configuration. Do not add noisy `clang-format off/on` comments
to force it; discuss formatter changes instead.

Brace conditional bodies containing assertion macros to avoid dangling-else
constructs. Do not weaken compiler settings to bypass warnings. Formatting
passes and formatter-configuration changes need instructions; do not restyle
unrelated files. Check the generated guide when comment wrapping changes
because Doxygen can interpret wrapped text as list syntax.

## User-guide terminology and review

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
in examples when they make styling expressions easier to read. Check for
names that hide API types or functions after qualification is removed.

### Teaching color choices

The user guide teaches readers how to get the appearance they want. Start
with named `term_color` values and named RGB constants. For custom shades,
introduce `color(red, green, blue)` and `color(grayscale)` with inputs from
`0.0` to `1.0`. Both overloads return `rgb`. The one-argument form uses the
same value for all three channels.

The named neutral shades `rgb::dark_gray`, `rgb::gray`, and `rgb::light_gray`
match `color(0.25)`, `color(0.5)`, and `color(0.75)`, respectively. The guide
generates Neutral swatches from the named RGB constants.

Reserve direct `rgb{...}` construction, indexed `gray` and `cube` values, and
raw SGR for advanced material or explicit comparisons. The appearance of
indexed colors depends on the terminal palette. `term_color::gray` selects
slot 8, and `rgb::term_gray` is its fixed Xterm RGB counterpart (`#7F7F7F`).
Keep threading and implementation details out of the main explanation.

Use **current style** for the style tracked during formatting and **default
style** for `text_style{}`. Nested formatting inherits and restores the current
style. The outermost formatting or printing call restores the default style.
Describe this behavior consistently across output destinations.

## Repository and tools

The library repository is `tjgolubi/color`; its integration and default branch
is `dev`.
Coordination documents live at the root of the separate `docs/Coord` branch.
Inspect actual refs and worktrees before acting rather than assuming recorded
checkout state still holds.

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

Any new commit, amendment, rebase, or changed integration tree requires CI for
the resulting SHA. Earlier results do not validate changed code. Record
intentional exclusions and distinguish local checks from remote CI.

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
backticks around identifiers where appropriate.

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
