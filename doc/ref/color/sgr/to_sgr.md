# [`tjg::color::to_sgr`](https://github.com/tjgolubi/color/blob/bf01e2dda7a63533f350ec19807749fca60a40cb/include/tjg/color/bits/sgr-support.hpp#L244)

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
auto to_sgr(const text_style& style) -> std::string;
auto to_sgr(const text_style& target, const text_style& initial)
  -> std::string;
```

## Description

Returns only an opening [SGR](https://en.wikipedia.org/wiki/ANSI_escape_code#Select_Graphic_Rendition_parameters) sequence or a transition.

### Opening style: `to_sgr(const text_style& style)`

Leaves unspecified components of a relative style alone. Absolute styles start with a reset, and an empty relative style produces an empty string.

### Style transition: `to_sgr(const text_style& target, const text_style& initial)`

Both styles describe complete states. Unspecified colors mean terminal defaults and absent emphasis means off. The initial absolute flag is ignored. An absolute target emits a reset followed by its specified style. For relative targets the current implementation chooses the shorter of selective changes and a reset followed by the target, preferring selective changes on ties.

## Parameters

| Parameter | Description                                 |
| ---       | ---                                         |
| `style`   | Style to open in the one-argument overload. |
| `target`  | Complete desired style for a transition.    |
| `initial` | Complete style before the transition.       |

## Return value

A narrow string containing only the opening SGR or transition.

## See also

[`wrap_sgr`](wrap_sgr.md) styles literal text in one call.
