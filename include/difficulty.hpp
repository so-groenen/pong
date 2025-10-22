#ifndef DifficultY_HPP
#define DifficultY_HPP


#include <iostream>
 

enum class Difficulty : uint8_t
{
    Easy = 0,
    Medium = 1,
    Difficult = 2
};

// from the guidlines: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-macro
inline Difficulty& operator++(Difficulty& diff)
{
    return diff = (diff == Difficulty::Difficult) ? Difficulty::Easy : static_cast<Difficulty>(static_cast<uint8_t>(diff)+1);
}
inline Difficulty& operator--(Difficulty& diff)
{
    return diff = (diff == Difficulty::Easy) ? Difficulty::Difficult : static_cast<Difficulty>(static_cast<uint8_t>(diff)-1);
}

#endif