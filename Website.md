# Website

[Document map](README.md) · [Workflow](Workflow.md) · [Build and test](BuildAndTest.md)

Updated November 20, 2026.

## Purpose and audience

The {color} website is a marketing tool for the general C++23 community.
Answer "Why should I use this?" before presenting technical details. Present
{color} as a standalone C++23 library using standard formatting and printing.

Welcome newer C++ programmers who want expressive terminal output but may not
know ANSI or SGR codes. Show readable results, noticeable warnings, and nested
styling that restores the enclosing appearance automatically. Experienced
visitors can explore the comparisons. Terry began describing two audiences;
the second audience has not been explicitly defined.

Terry confirmed that the public site is accessible and linked from his page.
Visitors can also arrive through the corrected library README website link. No referral from another library's maintainers has been confirmed.
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
  It links to all three table comparison pages. `#table` remains a landing
  point for those links. The C++23 explanation identifies SGR (Select Graphic
  Rendition) and links to the Wikipedia section on SGR.
- `cpp23-vs-color.html`: complete C++23 and {color} table programs side by side.
- `fmt-vs-color.html`: complete {fmt} and {color} table programs side by side.
- `ostream-vs-format.html`: {color} ostream and formatting table programs side
  by side, with stream and formatting width behavior explained.

Each table page aligns eleven corresponding source sections, from setup and
cell rendering through the dashboard rows and final Request ID example. The
table screenshot and column labels stay pinned above the code while scrolling.
Each code block has a copy button, and each program is available as a download.
Individual blocks scroll horizontally on narrow screens. Compact viewport
styles and measured reference height keep the pinned area and anchor spacing
manageable. Terry reviewed the pages and confirmed the pinned output works.

Keep comparisons fair: use clear, idiomatic C++23 and {fmt}, consistent names,
and matching comment sections where appropriate. Do not inflate alternatives
with avoidable clutter or excessive blank lines. Mention {fmt} in relevant
demo comparisons, without framing {color} as an extension or future port.
The homepage acknowledges the excellent work of the {fmt} project and its
influence on {color}'s color and styling API, links to https://fmt.dev/, and
recommends it to visitors who cannot use C++23, noting its C++11 support.
The C++23 table page also briefly explains SGR and links to
https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters.
No benchmark, adoption, or unrequested future-feature claims are established.

## Source and assets

The site has a separate source checkout on `main`. It uses static HTML, CSS,
and JavaScript under `dist/`. The tracked `.openai/hosting.json` declares the
Site identity and static directory. `dist/assets/style.css` and `site.js`
handle styling, copying, and pinned-reference measurement.

`dist/assets/table-demo.png` matches `demo/TableDemo.png` (1480 × 440), the
cropped terminal screenshot with `Request ID: 002a — completed`.
`dist/assets/result42.png` matches `demo/Result42.png`. The larger pinned
dashboard screenshot display introduced in version 9 is in the current site.
Preserve the screenshots and matching demo text together, including 東京.

The published comparison source and links use the `dev` snapshot
`15cf6cee9c1ea49f199ce2bca236c7378cd2602f`. `dist/examples/` contains all seven
demos and the site's quick-start program. The result page displays excerpts
from `Result42Compare.cpp`. The three dashboard pages show complete sources
using `TableDemo.cpp` alongside `TableDemoCpp.cpp`, `TableDemoFmt.cpp`, or
`TableDemoOstream.cpp`. Refresh copied code, section boundaries, line labels,
downloads, and source links together after an accepted demo update.

## Last recorded public deployment

Sites confirmed that version 13 succeeded on November 19, 2026 at 22:41:46 UTC.
The source commit was pushed and the matching archive was saved before
deployment. Sites metadata at that verification confirmed the public audience.

| Item             | Value                                                                               |
| ---------------- | ----------------------------------------------------------------------------------- |
| Site URL         | https://color-kit-cpp23.tjgolubi.chatgpt.site                                       |
| Project ID       | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02`                                          |
| Version          | 13                                                                                  |
| Saved version ID | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02~appgver_3b04613a0cd8819180676dbf7b9b4b16` |
| Deployment ID    | `appgdep_6aff7b2573f48191a53dcd8458be825a`                                          |
| Source commit    | `82f7b853144333e5738e159a9f1ee0b36c302ffc`                                          |
| Audience         | Public                                                                              |

## Verification and current handoff

Version 13 serves the seven demos from the recorded `dev` snapshot.
The eighth demo, `WrapTable`, and the `word_wrap()` guide and reference
are on `feat/Wrap`. The feature-branch guide build skipped publication.
For a future site update after integration, review the header-only claims
and the build and link instructions for downloads against the static archive.

At the version 13 verification, all seven demo downloads and both screenshots
matched the library snapshot
byte for byte. The homepage and comparisons page link to the current library
snapshot, and their live HTML matched the deployed source. All five public
pages were checked. Keep details about individual RGB names in the user guide.

The [GitHub Pages user guide](https://tjgolubi.github.io/color/) was built and
published separately from the same library commit. See
[BuildAndTest.md](BuildAndTest.md) for the guide and CI results.

## Maintenance

Use the current Sites skill and native tools. Retrieve fresh metadata, access,
and source before editing; preserve this project ID and public audience.
Keep site source separate from library and coordination commits. An authorized
site update includes normal source preparation and publication through Sites.

The current Sites source helper opened the checkout, pushed the exact source,
and packaged the deployment archive. Pass source credentials through hidden
stdin and keep them out of files and output.

Validate affected copy, source sections, assets, links, and interactions. Push
the exact source before saving its matching archive, then deploy that saved
version. Confirm deployment before reporting success. Resume saved versions
or nonterminal deployments rather than creating duplicates after interruption.
When both site and coordination updates are requested, publish and verify the
site first, then record the actual version and provenance here. Distinguish
local, committed, and pushed coordination edits. Keep current state and useful
procedures rather than accumulating a website history.
