#ifndef PONG_HPP
#define PONG_HPP

#include <iostream>
#include <stdexcept>

namespace raylib
{
    #include <raylib.h>
}
#include <cstdint>


using std::uint32_t, std::size_t, std::int8_t;

enum class GameState
{
    MENU = 0,
    // SELECT,
    ISRUNNING,
    WON,
    LOST,
};

enum class Difficulty : uint8_t
{
    EASY = 0,
    MEDIUM = 1,
    DIFFICULT = 2
};

void next(Difficulty& difficulty)
{
    uint8_t value = static_cast<uint8_t>(difficulty);
    if(value < static_cast<uint8_t>(Difficulty::DIFFICULT))
    {
        value++;
        difficulty = static_cast<Difficulty>(value);
    }
}

void previous(Difficulty& difficulty)
{
    uint8_t value = static_cast<uint8_t>(difficulty);
    if(value > static_cast<uint8_t>(Difficulty::EASY))
    {
        value--;
        difficulty = static_cast<Difficulty>(value);
    }
}

bool isRunning(const GameState& state)
{
    return state == GameState::ISRUNNING;
}

bool isMenu(const GameState& state)
{
    return state == GameState::MENU;
}

bool isEndingCredits(const GameState& state)
{
    bool won  = (state == GameState::WON);
    bool lost = (state == GameState::LOST);

    return (won || lost);
}
#endif