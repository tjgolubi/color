# TJG utilities

[API reference](../index.md) · [`<tjg/color.hpp>`](../color/index.md)

Use the headers listed below for the shared utilities.

## `<tjg/backslash.hpp>`

- [`tjg::backslash_escape`](backslash_escape.md)
- [`tjg::backslash_escape_to`](backslash_escape_to.md)
- [`tjg::backslash_unescape`](backslash_unescape.md)
- [`tjg::backslash_unescape_to`](backslash_unescape_to.md)

## Hash helpers

`<tjg/hash-support.hpp>` provides internal utilities used by the library's
hash implementations. Hash values are suitable for in-process lookup and
should not be serialized.

| Name                                   | Description                               |
| -------------------------------------- | ----------------------------------------- |
| [`tjg::hash_t`](hash_t.md)              | Result and seed type.                     |
| [`tjg::hash_value`](hash_value.md)      | Hashes one value using `std::hash`.       |
| [`tjg::hash_combine`](hash_combine.md)  | Mixes a value's hash into an existing seed. |
| [`tjg::hash_values`](hash_values.md)    | Hashes an ordered sequence from seed zero. |

## `<tjg/inline_buffer.hpp>`

- [`tjg::basic_inline_buffer`](basic_inline_buffer/index.md)
- [`tjg::inline_buffer`](inline_buffer.md)

## `<tjg/strip_ansi.hpp>`

- [`tjg::strip_ansi`](strip_ansi.md)

## `<tjg/utility.hpp>`

- [`tjg::CharType`](CharType.md)
- [`tjg::narrow_cast`](narrow_cast.md)
- [`tjg::enum_cast`](enum_cast.md)
