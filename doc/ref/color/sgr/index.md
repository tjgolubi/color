# SGR and ANSI helpers

Header: [`<tjg/color.hpp>`](../index.md).

Generate [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) terminal styling sequences, parse styled text, or strip escape sequences from styled text.

| Name                                        | Description                                                        |
| ---                                         | ---                                                                |
| [`parse_styled_text`](parse_styled_text.md) | Parses SGR sequences into styled text.                             |
| [`sgr_reset`](sgr_reset.md)                 | Returns a sequence that resets terminal colors and emphasis.       |
| [`strip_ansi`](strip_ansi.md)               | Removes escape sequences while preserving the styles and grouping. |
| [`to_sgr`](to_sgr.md)                       | Generates an opening style sequence or a style transition.         |
| [`wrap_sgr`](wrap_sgr.md)                   | Surrounds literal text with styling and a reset.                   |
