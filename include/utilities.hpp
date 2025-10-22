#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <iostream>
#include "raylib_backend.hpp"

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

 

// inline void randomize_dir(raylib::Vector2& vec)
// {
//     float r{sqrtf(vec.x*vec.x + vec.y*vec.y)};

//     auto theta  = to_float(raylib::GetRandomValue(0, 2*PI));
//     vec.x       = r*cosf(theta);
//     vec.y       = r*sinf(theta);
// }

// inline raylib::Vector2 get_rand_vec(float magnitude)
// {
//     raylib::Vector2 vec{magnitude, 0};
//     randomize_dir(vec);
//     return vec;
// }




#endif