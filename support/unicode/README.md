# Unicode table generation

The checked-in tables use Unicode 18.0.0. To download the inputs, run these
commands from the repository root.

```sh
cd support/unicode
curl --fail --location --remote-name https://www.unicode.org/Public/18.0.0/ucd/UnicodeData.txt
curl --fail --location --remote-name https://www.unicode.org/Public/18.0.0/ucd/EastAsianWidth.txt
curl --fail --location --remote-name https://www.unicode.org/Public/18.0.0/ucd/PropList.txt
```

When updating Unicode, use the same release in all three URLs.

Run `make` in this directory to regenerate the private classification tables
`src/UnicodeData.hpp` and `src/WrapData.hpp`, and the constexpr width table
`include/tjg/color/bits/EastAsianWidth.hpp`. Wrapping table generation requires
Python 3 (`PYTHON` can select its executable).

Run `python3 gen-wrap-tables.py` in this directory to regenerate the private
`src/WrapData.hpp` table. It uses `White_Space` and `Quotation_Mark` from
`PropList.txt`, and punctuation categories from `UnicodeData.txt`, excluding
opening punctuation and quotation marks. These are wrapping break preferences,
not a complete Unicode line-breaking algorithm.
