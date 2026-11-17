# Website

[Document map](README.md) · [Workflow](Workflow.md) · [Build and test](BuildAndTest.md)

Updated November 17, 2026.

## Purpose and audience

The {color} website is a marketing tool for the general C++23 community.
Answer "Why should I use this?" before presenting technical details. Present
{color} as a standalone header library using standard formatting and printing.

Welcome newer C++ programmers who want expressive terminal output but may not
know ANSI or SGR codes. Show readable results, noticeable warnings, and nested
styling that restores the enclosing appearance automatically. Experienced
visitors can explore the comparisons. Terry began describing two audiences;
the second audience has not been explicitly defined.

Terry confirmed that the public site is accessible and linked from his page.
Visitors can also arrive from the library README once its website link is
updated. No referral from another library's maintainers has been confirmed.
The site introduces benefits and examples; link to the generated user guide
for detailed usage and API reference rather than maintaining another guide.

## Content and presentation

Keep the dark charcoal and green palette, readable typography, and top links
to Overview, Comparisons, the user guide, and GitHub. Use `{color}` for the
project name in titles, navigation, column headings, and prose, matching
`{fmt}` in comparisons. Preserve code identifiers exactly.

Start with a brief plain-language introduction and everyday uses. Avoid
leading with CI status, implementation details, or long feature inventories.
The homepage quickly shows a small complete program printing "The result is
42 bytes." with an underlined sentence and red number; expected output is
immediately below the code. It also shows simple status and emphasis examples.
The dashboard screenshot demonstrates what is possible, with a source link
rather than its full code on the homepage.

### Comparison pages

- `comparisons.html`: the small sentence example, with three code blocks side
  by side for raw C++23 sequences, {fmt} restoration, and {color} nesting.
  It links to both table comparison pages. `#table` remains a landing point
  for those links.
- `cpp23-vs-color.html`: complete C++23 and {color} table programs side by side.
- `fmt-vs-color.html`: complete {fmt} and {color} table programs side by side.

Each table page aligns ten corresponding source sections, from setup and cell
rendering through the individual dashboard rows. The table screenshot and
column labels stay pinned above the code while scrolling. Code remains
visible, with a copy button for each block and complete-source downloads.
Individual blocks scroll horizontally on narrow screens. Compact viewport
styles and measured reference height keep the pinned area and anchor spacing
manageable. Terry reviewed the pages and confirmed the pinned output works.

Keep comparisons fair: use clear, idiomatic C++23 and {fmt}, consistent names,
and matching comment sections where appropriate. Do not inflate alternatives
with avoidable clutter or excessive blank lines. Mention {fmt} in relevant
demo comparisons, without framing {color} as an extension or future port.
No benchmark, adoption, or unrequested future-feature claims are established.

## Source and assets

The separate site checkout is `/workspace/sites/color-kit`, on `main`. It is
buildless HTML/CSS/JavaScript with static output under `dist/` and identity in
`.openai/hosting.json` (`static.directory` is `dist`). The four HTML files are
the homepage and the three comparison pages above. `dist/assets/style.css`
and `site.js` implement styling, copying, and pinned-reference measurement.

`dist/assets/table-demo.png` matches library `doc/table-demo.png`;
`dist/assets/nested-demo.png` matches library `demo/NestedDemo.png`.
`dist/examples/` contains seven original demos and the quick-start program.
The screenshots' `東京` text is retained; Terry considered Beijing but did not
request that change. Preserve text and screenshots together. Terminal palettes,
themes, and attribute support affect appearance.

Published source links and example downloads identify library snapshot
`c576f5df6b4b7d2ba8fa59a2ac9acf9239a6d687`. The displayed code reconstructs the
complete original programs without source changes. Refresh copied code,
section boundaries, downloads, and source links together after an accepted
demo update; do not rely on old line numbers.

## Current public deployment

Native Sites deployment confirmed version 4 succeeded November 17, 2026 at
05:30:52 UTC. Access is public by Terry's instruction. The site has its own
project and source repository; the earlier website was not modified.

| Item             | Value                                                                               |
| ---------------- | ----------------------------------------------------------------------------------- |
| Site URL         | https://color-kit-cpp23.tjgolubi.chatgpt.site                                       |
| Project ID       | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02`                                          |
| Version          | 4                                                                                   |
| Saved version ID | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02~appgver_0c6654a573288191ad4fa8a87ca8b20f` |
| Deployment ID    | `appgdep_6afbe685eb7c819183bd0acac1235276`                                          |
| Source commit    | `1e5a8215891398bb0f933a7764f33c083a64aede`                                          |
| Audience         | Public                                                                              |

The exact source is committed and pushed. The deployed archive is
`/workspace/sites/color-kit-branded.tar.gz`, created with `git archive` from
that pushed commit. No credentials are stored in source or archives.

## Verification and current handoff

The quick-start program compiled with GCC in C++23 mode and strict warnings;
its output matched expected style transitions and newline. All four pages
passed balanced-HTML, unique-ID, and local-link/asset/anchor checks. The table
pages reconstruct both complete sources exactly across ten section pairs.
The seven source downloads and screenshots match their repository inputs.
JavaScript syntax, copying, and pinned-reference height measurement passed
checks. Browser tooling was unavailable to the assistant; visual review and
confirmation of scrolling behavior came from Terry, not automated browser QA.

The user guide is now published at https://tjgolubi.github.io/color/ and uses
`{color}` branding. Its latest verified `dev` build and deployment passed;
see [BuildAndTest.md](BuildAndTest.md). The footer's guide-source fallback is
still available, but the live guide no longer returns 404.

`fix/Demos` at `acd98bd` is pushed for Terry's review. It aligns C++23 and
{fmt} names and comments and introduces `bold_underline`; each demo's output
is unchanged. The website still shows the original demo snapshot. Do not
publish the candidate as accepted work without instructions.

The library README still links to `https://color.tjgolubi.chatgpt.site`, rather
than the new public site above. Updating that inbound link remains outstanding;
no library README edit has been made.

## Maintenance

Use the current Sites skill and native tools. Retrieve fresh metadata, access,
and source before editing; preserve this project ID and public audience.
Keep site source separate from library and coordination commits. An authorized
site update includes normal source preparation and publication through Sites.

The installed skill's source helper was unavailable in this workspace. Source
synchronization used ordinary Git with short-lived credentials passed through
hidden stdin and process-local authentication headers. No credentials were
persisted. Prefer the supported helper when available in another environment.

Validate affected copy, source sections, assets, links, and interactions. Push
the exact source before saving its matching archive, then deploy that saved
version. Confirm deployment before reporting success. Resume saved versions
or nonterminal deployments rather than creating duplicates after interruption.
When both site and coordination updates are requested, publish and verify the
site first, then record the actual version and provenance here. Distinguish
local, committed, and pushed coordination edits. Keep current state and useful
procedures rather than accumulating a website history.
