# Website

[Document map](README.md) · [Workflow](Workflow.md) · [Build and test](BuildAndTest.md)

Updated November 22, 2026.

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
The homepage shows the dashboard and WrapTable screenshots. At `#wrap-table`,
visitors can download `WrapTable.cpp`, read its GitHub source, or follow the
guide walkthrough. The demo shows multiline styled cells and Unicode display
width in a layout defined by the example program, four-column hanging indents
in the work-item notes, and a tagged, wrapped footer. The page describes soft
hyphens, ideographic breaks, and no-break spaces. At `#wrap-prose`, a runnable
example uses `wrapped()` with a format field width and `rgb::xterm_cyan`, with
links to the `wrapped()` and Xterm palette references. At `#tagged-demo`,
the terminal screenshot and full `Tagged.cpp` code block each use the section
width, with the screenshot first. The code block has a copy button. Links lead
to the walkthrough, source download, GitHub source, and the `tagged()` API
reference. Keep the marketing copy focused on visible results and examples.
Detailed SGR and `println()` behavior belongs in the library documentation.
The getting-started
section links to installation instructions, the API reference, and the guide's
demo index. It documents CMake 3.31 and linking the static archive using
`tjg::tjg`.

### Comparison pages

- `comparisons.html`: the small sentence example, with three code blocks side
  by side for raw C++23 sequences, {fmt} restoration, and {color} nesting.
  It links to all three table comparison pages. `#table` remains a landing
  point for those links and the WrapTable showcase. The C++23 explanation
  identifies SGR (Select Graphic Rendition) and links to the Wikipedia section
  on SGR.
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
On the C++23 side, the second block starts at `struct span` on line 20.
On the {fmt} side, it starts at `// Reuse column backgrounds` on line 31.

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
`dist/assets/result42.png` matches `demo/Result42.png`.
`dist/assets/wrap-table.png` matches `demo/WrapTable.png` (1040 × 651).
`dist/assets/tagged-demo.png` matches `demo/Tagged.png` (1040 × 698).

The published comparison source and links use the `dev` snapshot
`fc368946e2c4bb836d487952935070698cfbf8d5`. `dist/examples/` contains all nine
demos and the site's quick-start program. The result page displays excerpts
from `Result42Compare.cpp`. The three dashboard pages show complete sources
using `TableDemo.cpp` alongside `TableDemoCpp.cpp`, `TableDemoFmt.cpp`, or
`TableDemoOstream.cpp`. Refresh copied code, section boundaries, line labels,
downloads, and source links together after an accepted demo update.

## Last recorded public deployment

Sites confirmed that version 23 succeeded on November 22, 2026 at 2:29 p.m.
CST. The source commit was pushed and the matching archive was saved before
deployment. Sites metadata confirmed the public audience.

| Item             | Value                                                                                  |
| ---------------- | -------------------------------------------------------------------------------------- |
| Site URL         | https://color-kit-cpp23.tjgolubi.chatgpt.site                                          |
| Project ID       | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02`                                             |
| Version          | 23                                                                                     |
| Saved version ID | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02~appgver_803c92daaa888191921a97c1cb4469f5`    |
| Deployment ID    | `appgdep_6b03509ec45c8191b3affd8ac2d0eab3`                                             |
| Source commit    | `74891ea4ccac9874447b7a470935d30c789479eb`                                             |
| Audience         | Public                                                                                 |

## Verification and current handoff

The nine demo downloads and four screenshots matched the `fc36894` library
snapshot byte for byte before the source links were refreshed. The Tagged
output appears above the complete `Tagged.cpp` example. All five live pages
were checked after the homepage's `println()` newline-order explanation was
removed in version 23.

The [GitHub Pages user guide](https://tjgolubi.github.io/color/) was published
separately from `dev` commit `fc36894`. See [BuildAndTest.md](BuildAndTest.md)
for the guide and CI results.

### Homepage idea under discussion

Consider leading with a Tagged example inspired by Taskwarrior's `task news`
entry for writeable contexts. The idea is to wrap the explanatory prose and
show the command transcript in its actual terminal colors, preserving column
spacing. A uniform inset and a contrasting background would distinguish the
transcript. The live homepage still leads with the red `42` example.

## Maintenance

Use the current Sites skill and native tools. Retrieve fresh metadata, access,
and source before editing; preserve this project ID and public audience.
Keep site source separate from library and coordination commits. An authorized
site update includes normal source preparation and publication through Sites.

The current Sites source helper opened the checkout, pushed the exact source,
and packaged the deployment archive. Pass source credentials through hidden
stdin and keep them out of files and output.
On Windows, the native Sites helper uses Git for Windows in the separate Site
checkout. Use MSYS2 Git for the library and coordination worktrees.

Validate affected copy, source sections, assets, links, and interactions. Push
the exact source before saving its matching archive, then deploy that saved
version. Confirm deployment before reporting success. Resume saved versions
or nonterminal deployments rather than creating duplicates after interruption.
When both site and coordination updates are requested, publish and verify the
site first, then record the actual version and provenance here. Distinguish
local, committed, and pushed coordination edits. Keep current state and useful
procedures rather than accumulating a website history.
