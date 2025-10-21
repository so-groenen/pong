#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <iostream>


template<typename T>
constexpr float to_float(const T value) requires std::floating_point<T> || std::integral<T>
{
    return static_cast<float>(value);
}

template<typename T>
constexpr int to_int(const T value)  requires std::floating_point<T> || std::integral<T>
{
    return static_cast<int>(value);
}
template<typename T>
constexpr int to_size_t(const T value)  requires std::floating_point<T> || std::integral<T> || std::is_scoped_enum_v<T>
{
    return static_cast<size_t>(value);
}

#endif