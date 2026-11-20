# [`tjg::color::Color`](https://github.com/tjgolubi/color/blob/92039b88e7f226935de41ed533b8601ddeff5517/include/tjg/color/colors.hpp#L504)

Header: [`<tjg/color/colors.hpp>`](index.md).

## Synopsis

```cpp
template<typename T>
concept Color = std::same_as<std::remove_cvref_t<T>, rgb>
             || std::same_as<std::remove_cvref_t<T>, term_color>
             || std::same_as<std::remove_cvref_t<T>, cube>
             || std::same_as<std::remove_cvref_t<T>, gray>;
```

## Description

Recognizes the four concrete color types, including their const and reference forms. [`color_t`](color_t.md) and [`no_color_t`](no_color_t/index.md) do not satisfy it.

## Template parameters

| Parameter | Description                                                            |
| ---       | ---                                                                    |
| `T`       | Type to test after removing const, volatile, and reference qualifiers. |
