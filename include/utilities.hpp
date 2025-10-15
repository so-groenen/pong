#ifndef UTILITIES_HPP
#define UTILITIES_HPP

template<typename T>
constexpr float toFloat(const T value)
{
    return static_cast<float>(value);
}

template<typename T>
constexpr int toInt(const T value)
{
    return static_cast<int>(value);
}

#endif