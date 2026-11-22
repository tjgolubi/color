# Unicode table generation

The checked-in tables use Unicode 18.0.0. To fetch missing inputs using `curl`,
run this command from the repository root.

```sh
make -C support/unicode download
```

The target fetches missing copies of `UnicodeData.txt`, `EastAsianWidth.txt`,
`PropList.txt`, and `LineBreak.txt`. It leaves existing files in place. When
updating Unicode, change `UNICODE_VERSION` in the Makefile and refresh all
inputs together.

Run `make` in this directory to regenerate the private classification tables
`src/UnicodeData.hpp` and `src/WrapData.hpp`, and the constexpr width table
`include/tjg/color/bits/EastAsianWidth.hpp`. Regeneration uses local inputs
and works offline. Wrapping table generation requires Python 3 (`PYTHON` can
select its executable).

Run `python3 gen-wrap-tables.py` in this directory to regenerate the private
`src/WrapData.hpp` table. It uses `White_Space` and `Quotation_Mark` from
`PropList.txt`, punctuation categories from `UnicodeData.txt`, and the
Ideographic (`ID`) line-break class from `LineBreak.txt`. Punctuation break
preferences exclude opening punctuation and quotation marks. The same table
provides the Letter, Number, and Mark categories for `tagged()` emphasis
boundaries, including ranges expressed as `First` and `Last` records.
