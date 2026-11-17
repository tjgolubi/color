# Publishing the Color user guide

The guide sources live in `doc/` in `tjgolubi/color`. The `Color guide`
workflow (`.github/workflows/doc.yml`) builds the guide on pushes and pull
requests. Only pushes to `dev` upload a Pages artifact and run the deployment
job. Publication also requires the repository setup below.

## One-time GitHub setup

In the repository's **Settings → Pages**, select **GitHub Actions** as the
build and deployment source. Actions must also be enabled for the repository.

In **Settings → Environments → github-pages**, ensure deployment branch rules
allow `dev`. If using a selected-branches policy, add `dev`.

Use GitHub's built-in token and Pages deployment identity; no personal access
token or separate hosting credentials are needed.

## Publication workflow

The build job validates pushes and pull requests and uploads `build/doc-html/`
as a Pages artifact only for a push to `dev`. The dependent deployment job uses
the `github-pages` environment and `pages: write` and `id-token: write`
permissions. The build retains `contents: read` for source checkout. Publication
is restricted to pushes to `dev`; feature branches, pull requests, and the
separate `docs/Coord` branch do not publish. Pages deployments are serialized
without cancelling a deployment already in progress.

Official Pages actions are pinned to full commit SHAs. A prepared workflow is
not evidence of a successful deployment; verify the run after it is pushed.

After a deployment-enabled workflow is pushed to `dev`, inspect its build and
deployment jobs under **Actions → Color guide**. Confirm both succeeded for
the intended commit and verify the live overview, navigation, API references,
links, and color swatches. A successful build alone does not establish a
published site.

## Guide configuration and local build

`support/mkdocs-pages.yml` inherits `support/mkdocs.yml` and sets the publication
URL, repository links, and edit links for `dev`. The intended guide address is
https://tjgolubi.github.io/color/, with the overview at the site root.

From the repository root, with Python 3 and Doxygen available, run:

```sh
cmake -S . -B build
cmake --build build --target doc
```

The target installs the hash-pinned documentation dependencies into
`build/doc-venv` and writes `build/doc-html/index.html`. This builds the guide
locally without publishing it. The GitHub workflow uses the same publication
configuration and writes its output to `build/doc-html/`.
