# `tagged()` parser requirements

[Document map](README.md) · [Workflow](Workflow.md)

Draft · November 21, 2026

## Purpose

`tjg::color::tagged()` converts prose with inline styling into `styled_text`
or `wstyled_text`. Both overloads use the same grammar.

```cpp
auto tagged(std::string_view text) -> styled_text;
auto tagged(std::wstring_view text) -> wstyled_text;
```

The result keeps its own text. Preserve input whitespace, including actual
newlines, except where markup is consumed or an escape is decoded. A caller
can format the result directly or pass it to `word_wrap()`. A caller can also
pass the narrow result to `wrapped()` for formatted or streamed output.

Start implementation from a `dev` version that includes `1175ed1` and
`1b3c596`. Those commits supply the `rgb::xterm_*` names and enhanced
`word_wrap()` behavior. The parser can be implemented independently of
`wrapped()`.

## Tag syntax

Supported tag names are lowercase and case-sensitive. The identifier starts
immediately after `<` or `</`. Spaces between tokens and before `>` are
ignored. For example, `<color = red / blue >` and `<color=red/blue>` match the
same syntax. The angle brackets in `a < b > c` stay literal.

An opening style tag pairs with its named closing tag or `</>`. The shorthand
`</>` closes the innermost open styling tag and stays literal when there is
no such tag. A punctuation opener pairs with its matching punctuation closer.
Close nested scopes from the inside out. For example, `<b>*text*</>` is valid.
The forms `*italic</>`, `*italic</i>`, and `<i>italic*` stay literal.

`<br>` emits one newline and opens no scope. Two consecutive `<br>` tags
produce a blank line, including in a single-line C++ raw string literal.

## Emphasis

Each of the eight existing emphasis attributes has a standalone tag with a
matching end tag.

| Attribute   | Named tag                   | Short tag  | Shorthand  |
| ----------- | --------------------------- | ---------- | ---------- |
| `bold`      | `<bold>…</bold>`            | `<b>…</b>` | `**text**` |
| `faint`     | `<faint>…</faint>`          |            |            |
| `italic`    | `<italic>…</italic>`        | `<i>…</i>` | `*text*`   |
| `underline` | `<underline>…</underline>`  | `<u>…</u>` | `_text_`   |
| `blink`     | `<blink>…</blink>`          |            |            |
| `reverse`   | `<reverse>…</reverse>`      |            |            |
| `conceal`   | `<conceal>…</conceal>`      |            |            |
| `strike`    | `<strike>…</strike>`        | `<s>…</s>` | `~~text~~` |

`<emphasis=bold | underline>…</emphasis>` applies several attributes at once.
Accept `|` and `,` as separators, with optional spaces around them.

For a shorthand pair, the character immediately before the opening delimiter
and the character immediately after the closing delimiter must each be outside
Unicode general categories Letter (`L`), Number (`N`), and Mark (`M`), or the
delimiter must be at the corresponding input boundary. Check decoded code
points. Han characters qualify as letters, and combining marks count as word
characters so an accent stays part of its word for this check.

One consecutive asterisk can delimit italic, and two can delimit bold. A run
of three or more stays literal as a unit in both opening and closing positions.
Unmatched shorthand stays literal.

## Color and style scopes

Use `<color=fg/bg>…</color>`. A single value selects the foreground. Either
slot may be empty to inherit that channel. The slash separates the two slots.
For example, `<color=red/>` opens the same scope as `<color=red>` and takes a
closing tag. Both slots accept named RGB colors, terminal palette entries,
and `#RRGGBB` with exactly six hexadecimal digits of either case.

| Opening tag              | Effect                                       |
| ------------------------ | -------------------------------------------- |
| `<color=red>`            | Fixed foreground `rgb::red`                  |
| `<color=cyan/indigo>`    | Fixed foreground and background RGB colors   |
| `<color=/dark_blue>`     | Fixed background with foreground inherited   |
| `<color=#CD0000/indigo>` | Hex RGB foreground and named RGB background  |
| `<color=term_red>`       | Foreground from the terminal's red slot      |
| `<color=xterm_red>`      | Fixed Xterm-default red `rgb::xterm_red`     |
| `<color=red, absolute>`  | Fixed red on a fresh style scope             |

Use the library's named RGB spellings without the `rgb::` qualifier. Reserve
`term_` in markup for `term_color` palette entries, whose appearance follows
the user's terminal. Use `xterm_` for the fixed Xterm defaults exposed by
`rgb::xterm_*`.

Tags and shorthand can nest. Relative scopes inherit unspecified colors and
combine emphasis. The `absolute` modifier starts from the terminal defaults
before applying the tag's colors, clearing inherited colors and emphasis.
Nested markup can apply styles within that scope. Closing a scope restores
the enclosing style.

## Literal text and recovery

Outside a literal span, a backslash escapes a markup delimiter or another
backslash. For example, `\<bold>` emits `<bold>` and `` \` `` emits a literal
backtick. Preserve an unrecognized escape such as `\q`, a trailing backslash,
and literal backslash-letter sequences such as `\n`.

A backslash followed by one ASCII space emits U+00A0 NO-BREAK SPACE. For
example, pass `R"(10\ kg)"` or `"10\\ kg"` to `tagged()` to keep `10` and `kg`
together when wrapping. `\-` is the soft-hyphen escape described below.

Accept `\u` followed by four hexadecimal digits and `\U` followed by eight,
with digits `A` through `F` accepted in either case. Encode the Unicode scalar
value as literal text in the result. For example, `\u00A0` emits a no-break
space, `\U0001F642` emits 🙂, and `\u002A` emits an asterisk without opening
emphasis. Preserve malformed escapes and invalid scalar values verbatim,
including surrogate values and values above U+10FFFF.

An unescaped backtick and its closing backtick delimit a literal span. The
delimiters are removed. Backslashes inside the span stay literal, and the text
inherits the surrounding style. An unmatched backtick stays literal.

Skip well-formed unrecognized opening and closing tags while parsing their
contents normally. For example, `<foo>Hello **world**</foo>` displays
`Hello world` with `world` bold. `<span>` is an unrecognized tag. To display a
tag itself, escape its opening `<` or put it in a literal span.

Preserve malformed tags as literal text and continue parsing. This includes
unknown color or emphasis values within a recognized tag, mismatched closes,
and recognized openings with no matching close. A mismatched closing tag
leaves the active style alone. For example, `<color=redd>hello</color>`
appears unchanged when it occurs on its own.

## Unicode data and wrapping

Extend the existing Unicode table generation to supply the delimiter-boundary
lookup for shorthand emphasis. Generate compact ranges from
the checked-in Unicode data. Expand `First` and `Last` records to cover their
full ranges, as `GenUnicodeTables.cpp` already does for printability. Use the
same boundary categories for UTF-8 and wide input.

`tagged()` converts `\-` to U+00AD SOFT HYPHEN. A plain `-` is a visible
hyphen. An ordinary C++ string literal spells the parser escape as `"\\-"`.
In a raw string, write `\-` directly.

`word_wrap()` treats U+00AD as zero display columns and omits it from the
returned text unless the marked break is used, in which case it emits an
ASCII hyphen. A word that fits on a fresh line can still move there intact.
These rules also apply to U+00AD present directly in the input.

`word_wrap()` preserves U+00A0 as one display column and keeps the adjacent
text together when it fits on a full line. For an oversized group with no
preferred break, it can break at U+00A0 before resorting to a forced split.
The break consumes the no-break space and adds no hyphen.

`word_wrap()` can split an oversized group between adjacent code points in
the Unicode Ideographic (`ID`) line-break class without adding a hyphen.
At four display columns, `北京大学` wraps as `北京` and `大学`. The generated
wrap table already provides this lookup.

## Acceptance examples

- `<color=cyan>Lorem **ipsum** _dolor_</color>.` renders cyan text, adds bold
  and underline to the marked words, and restores the outer style for `.`.
- `<bold>before <color=red, absolute>inside</color> after</bold>` renders
  `inside` as fixed red with the default background and no inherited bold.
  Both `before` and `after` are bold.
- `` `<b>**literal**</b>` `` emits `<b>**literal**</b>` literally.
- `foo_bar_baz Really??` keeps both the identifier and punctuation intact.
- `東京*です*` stays literal. In `東京：*です*`, punctuation permits the
  italic span.
- `***italic* and bold**` stays literal. The opening asterisk run remains
  intact and opens no scope.
- `super\-califragilistic\-expiali\-docious` wraps at width 16 as `super-`,
  `califragilistic-`, and `expialidocious`.
- `10\ kg` and `10\u00A0kg` both emit `10` and `kg` separated by U+00A0.
  The result stays on one line at width five and wraps as `10` and `kg` at
  width four. Inside a backtick-delimited literal, both escapes stay verbatim.
- Two styled prose paragraphs separated by a blank line retain that break
  when passed to `wrapped(tagged(prose))`. A styled phrase that crosses a
  wrap boundary retains its style on both lines.
