# Website

[Document map](README.md) · [Workflow](Workflow.md) · [Build and test](BuildAndTest.md)

Updated November 17, 2026.

## Purpose and audience

The Color website is a marketing tool for the general C++23 community. Answer
"Why should I use this?" before presenting technical details. Color is a
standalone header library using standard formatting and printing.

Welcome newer C++ programmers who want more expressive terminal output but
may not know ANSI or SGR escape sequences. Show concrete everyday benefits:
readable results, noticeable warnings, and nested styling that automatically
restores the enclosing appearance. More experienced visitors can explore the
code comparisons. Terry began describing two audiences; the second audience
has not yet been explicitly defined.

Visitors will arrive through the GitHub README and Terry's personal project
page. Other projects may link to the site, but no such referral is confirmed.
The website introduces the library and demonstrates its value; the user guide
provides usage details and the API reference. Do not duplicate that guide.

## Content and visual direction

Keep the dark charcoal and green visual style, readable typography, and top
navigation. The navigation links to Overview, Comparisons, the user guide,
and the GitHub repository. Keep introductory text brief and plain. Avoid
leading with CI results, implementation machinery, or long feature inventories.

### Homepage

- Introduce what Color is useful for, then quickly show a small complete
  program printing "The result is 42 bytes." Underline the sentence, make
  the number red, and show expected appearance immediately below the code.
- Show short everyday status and emphasis examples.
- Display the colored table screenshot as an example of what is possible.
  Link to its source without displaying its lengthy code on the homepage.
- Explain composition and restoration briefly, then offer repository and
  user-guide links and minimal header-only C++23 setup guidance.

### Comparisons page

Use side-by-side examples to explain readability and the work handled by the
library. Keep these detailed comparisons separate from the homepage.

- `NestedDemo.cpp`: raw C++23 sequences, explicit restoration with {fmt},
  and automatic nested-style restoration with Color. An expandable explanation
  includes the repository screenshot of all five source examples.
- `Cpp23Demo.cpp`, `FmtColorDemo0.cpp`, and `TableDemo.cpp`: the same dashboard
  implemented with standard C++23, external {fmt}, and Color. Tabs explain
  each approach and link to its source and download; full source is expandable.
- Link to styled-argument, underlay/overlay, and ostream examples for visitors
  who want more detail.

Mention {fmt} only where relevant to the comparisons. Do not frame Color as
an extension, contribution, or future port. Do not add unrequested feature
plans, performance claims, testimonials, or adoption claims.

## Assets and source

The separate site checkout is `/workspace/sites/color-kit`. It is buildless
HTML, CSS, and JavaScript with static output in `dist/`:

- `dist/index.html`: homepage.
- `dist/comparisons.html`: comparisons.
- `dist/assets/style.css` and `site.js`: styling, code copying, and accessible
  comparison tabs with keyboard navigation.
- `dist/assets/table-demo.png`: exact copy of library `doc/table-demo.png`.
- `dist/assets/nested-demo.png`: exact copy of library `demo/NestedDemo.png`.
- `dist/examples/`: seven original demo sources and the compiled quick-start
  example shown on the homepage.

Demo source links identify library commit
`c576f5df6b4b7d2ba8fa59a2ac9acf9239a6d687`. Refresh links and downloadable
copies together when updating examples. Screenshots are terminal captures;
terminal palettes, themes, and attribute support affect appearance. Do not
infer that other implementations produce byte-identical output.

## Current deployment

This is a new Site, separate from any earlier website. Native Sites deployment
confirmed success November 17, 2026 at 04:22:34 UTC. It remains owner-private
for Terry's review; it is not yet a public marketing launch.

| Item             | Value                                                                               |
| ---------------- | ----------------------------------------------------------------------------------- |
| Site URL         | https://color-kit-cpp23.tjgolubi.chatgpt.site                                       |
| Project ID       | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02`                                          |
| Version          | First saved version                                                                 |
| Saved version ID | `appgprj_6afbd589fbb08191b3ab25ed2fb0dc02~appgver_4ec4fe7a6190819193df79c94b773890` |
| Deployment ID    | `appgdep_6afbd68398b8819197069b82abb25c8d`                                          |
| Source commit    | `13b07d649609779cb43877d8fe21d1e4c9dc01e0`                                          |
| Audience         | Owner-private                                                                       |

The exact site source is committed and pushed to its separate Sites repository
on `main`. `.openai/hosting.json` retains the project ID and declares
`static.directory` as `dist`. Deployment archive:
`/workspace/sites/color-kit-deploy.tar.gz`, created with `git archive` from
the pushed source commit. Source and archive contain no credentials.

## Verification and outstanding issues

The quick-start program compiled with GCC in C++23 mode and strict warnings.
Its output exactly matched the expected underline, red number, foreground
restoration, final reset, and newline. JavaScript syntax, tab selection,
keyboard navigation, and clipboard behavior passed automated checks.
Both HTML pages passed balanced-tag, unique-ID, and local-link/asset/anchor
checks. Seven demo downloads and the table screenshot matched repository
files. GitHub repository and table-source links returned HTTP 200.

Browser tooling was unavailable in this workspace; no visual browser review
or responsive browser test is claimed. The seven comparison demos were read
and copied, not freshly built or run during site creation.

The user-guide address `https://tjgolubi.github.io/color/` returned HTTP 404.
The site retains that intended guide destination and adds a footer fallback
to `https://github.com/tjgolubi/color/tree/dev/doc`. The current
`.github/workflows/doc.yml` builds the guide but has no Pages deployment
step. A passing guide build does not establish publication. Terry wants the
guide published; deployment repair remains outstanding and no library workflow
was changed during website creation.

The library README still links to `https://color.tjgolubi.chatgpt.site`, which
differs from this new Site. That address was not changed or verified. Resolve
the final public site address and audience before updating inbound links.

## Maintenance

Use the current Sites skill and native tools. Retrieve fresh metadata, access,
and source before editing; preserve this Site's identity. Keep site source
separate from the library. An authorized site update includes the normal Sites
source preparation and publication workflow, not library or coordination
commits or pushes. Preserve the audience unless Terry instructs a change.

Validate changed examples, assets, links, and interactions; perform visual QA
when supported and report limits. Push the exact source before saving its
matching archive, and deploy the saved version. Confirm successful deployment
before reporting publication. Reuse saved versions and ongoing deployments
rather than creating duplicate results after interruptions. Keep credentials
in memory and pass them through hidden stdin, never files or shell arguments.

For updates covering site and coordination, publish and verify the site first,
then record its actual provenance here. Distinguish local, committed, and pushed
coordination changes. Keep current purpose, procedures, confirmed deployment,
and open issues rather than accumulating a website history.
