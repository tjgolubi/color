# `tjg::color::to_sgr`

Header: [`<tjg/color.hpp>`](../index.md).

## Synopsis

```cpp
auto to_sgr(const text_style& ts) -> std::string;
auto to_sgr(const text_style& target, const text_style& initial)
  -> std::string;
```

Returns an opening SGR sequence or a transition. The one-argument overload leaves unspecified components of a relative style alone. Absolute styles start with a reset, and an empty relative style produces an empty string.

With `target` and `initial`, both styles describe complete states. Unspecified colors mean terminal defaults and absent emphasis means off. The initial absolute flag is ignored. An absolute target emits a reset followed by its specified style. For relative targets the current implementation chooses the shorter of selective changes and a reset followed by the target, preferring selective changes on ties.

The result contains only the opening sequence or transition. Constructing it can allocate. To style literal text in one call, see [`wrap_sgr`](wrap_sgr.md).
