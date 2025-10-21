#ifndef DifficultY_HPP
#define DifficultY_HPP


#include <iostream>
 

enum class Difficulty
{
    Easy = 0,
    Medium = 1,
    Difficult = 2
};

// from the guidlines: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-macro
inline Difficulty& operator++(Difficulty& diff)
{
    return diff = (diff == Difficulty::Difficult) ? Difficulty::Easy : static_cast<Difficulty>(static_cast<int>(diff)+1);
}
inline Difficulty& operator--(Difficulty& diff)
{
    return diff = (diff == Difficulty::Easy) ? Difficulty::Difficult : static_cast<Difficulty>(static_cast<int>(diff)-1);
}

#endif