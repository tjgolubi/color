# [`tjg::color::basic_styled_text::operator=`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/styled_text.hpp#L77)

Type: [`tjg::color::basic_styled_text`](index.md).

Header: [`<tjg/color/styled_text.hpp>`](../index.md).

## Synopsis

```cpp
auto operator=(const basic_styled_text& other) -> basic_styled_text&;

auto operator=(basic_styled_text&& other) noexcept -> basic_styled_text&;
```

## Description

Both overloads return `*this`. Self-assignment leaves the value unchanged.

### Copy assignment: `operator=(const basic_styled_text& other)`

Replaces the current value with a copy of the source.

### Move assignment: `operator=(basic_styled_text&& other)`

Replaces the current value by moving from the source.
