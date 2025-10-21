#ifndef DIFFICULTY_HPP
#define DIFFICULTY_HPP


#include <iostream>
 

enum class Difficulty
{
    EASY = 0,
    MEDIUM = 1,
    DIFFICULT = 2
};

// from the guidlines: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-macro
inline Difficulty& operator++(Difficulty& diff)
{
    return diff = (diff == Difficulty::DIFFICULT) ? Difficulty::DIFFICULT : static_cast<Difficulty>(static_cast<int>(diff)+1);
}
inline Difficulty& operator--(Difficulty& diff)
{
    return diff = (diff == Difficulty::EASY) ? Difficulty::EASY : static_cast<Difficulty>(static_cast<int>(diff)-1);
}

#endif