# Demos

These nine programs show how to style terminal output, wrap prose, and build
table layouts. Start with StyledDemo for a short example, or see how Tagged
prints the same styled note at different widths and alignments.

| Demo                               | What it shows                                                                |
| ---------------------------------- | ---------------------------------------------------------------------------- |
| [StyledDemo][styled-demo]          | Apply a style to a value inside a formatted message.                         |
| [StyledTextDemo][styled-text-demo] | [Walkthrough](styled-text-demo.md) of composition, underlay, and overlay.    |
| [Tagged][tagged]                   | [Walkthrough](tagged-demo.md) of tagged prose, wrapping, and alignment.      |
| [WrapTable][wrap-table]            | [Walkthrough](wrap-table.md) of wrapping and aligning styled cells.          |
| [TableDemo][table-demo]            | [Walkthrough](table-demo.md) of a colored dashboard with fixed-width fields. |
| [TableDemoOstream][table-ostream]  | Render the same dashboard using {color} stream insertion.                    |
| [TableDemoCpp][table-cpp]          | Render the dashboard with standard C++23 and raw SGR sequences.              |
| [TableDemoFmt][table-fmt]          | Render the dashboard with {fmt}.                                             |
| [Result42Compare][result-compare]  | Compare one styled message using raw SGR, {fmt}, and {color}.                |

## Build and run

From the repository root, use GNU make and a C++23 toolchain with support for
`<format>` and `<print>`. Use an ANSI-capable UTF-8 terminal to see the styles
and Unicode characters.

```sh
make -C demo StyledDemo
./demo/StyledDemo
```

Replace `StyledDemo` with another demo name. `TableDemoFmt` and
`Result42Compare` require a built copy of {fmt}. See the
[demo README][demo-build] for build options.

[styled-demo]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/StyledDemo.cpp
[styled-text-demo]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/StyledTextDemo.cpp
[tagged]: https://github.com/tjgolubi/color/blob/dev/demo/Tagged.cpp
[wrap-table]: https://github.com/tjgolubi/color/blob/dev/demo/WrapTable.cpp
[table-demo]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemo.cpp
[table-ostream]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemoOstream.cpp
[table-cpp]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemoCpp.cpp
[table-fmt]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemoFmt.cpp
[result-compare]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/Result42Compare.cpp
[demo-build]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/README.md
