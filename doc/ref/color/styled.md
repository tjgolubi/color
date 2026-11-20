# `tjg::color::styled`

Header: [`<tjg/color.hpp>`](index.md).

## Synopsis

```cpp
// The return type is a formattable wrapper.
template<typename T>
constexpr auto styled(const T& value, text_style ts);
```

Returns a wrapper that borrows `value` and stores a copy of `ts`. The value must remain alive until formatting or insertion completes. Use the result directly as a format argument or stream operand.

During formatting, a relative style inherits unspecified components from the surrounding style. An absolute style starts from terminal defaults. After formatting the argument, the surrounding style is restored. Format specifications are handled by the wrapped value’s formatter.

```cpp
using namespace tjg::color;
using enum term_color;
std::println("The result is {} bytes.", styled(42, fg(red)));
```
