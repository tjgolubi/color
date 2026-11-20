# Demos

These eight programs show how to style terminal output, compose styled text,
and build table layouts. Start with StyledDemo for a short example or follow
the WrapTable walkthrough to build a table with wrapped cells.

| Demo                               | What it shows                                                                |
| ---------------------------------- | ---------------------------------------------------------------------------- |
| [StyledDemo][styled-demo]          | Apply a style to a value inside a formatted message.                         |
| [StyledTextDemo][styled-text-demo] | [Walkthrough](styled-text-demo.md) of composition, underlay, and overlay.    |
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

Replace `StyledDemo` with another demo name, or run `make -C demo run` to
build and run all eight. `TableDemoFmt` and `Result42Compare` require a built
copy of {fmt}. See the [demo README][demo-build] for build options.

[styled-demo]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/StyledDemo.cpp
[styled-text-demo]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/StyledTextDemo.cpp
[wrap-table]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/WrapTable.cpp
[table-demo]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemo.cpp
[table-ostream]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemoOstream.cpp
[table-cpp]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemoCpp.cpp
[table-fmt]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/TableDemoFmt.cpp
[result-compare]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/Result42Compare.cpp
[demo-build]: https://github.com/tjgolubi/color/blob/c94e78f4048aba62f22599cebf44507c39a3c4fa/demo/README.md
