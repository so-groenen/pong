#include "pong.hpp"
#include "Block.hpp"
#include "utilities.hpp"
#include "ball.hpp"
#include "enemy.hpp"
#include "Menu.hpp"
#include "game.hpp"


int main()
{
    const uint32_t width    = 1024;
    const uint32_t height   = 512;
    const char* title       = "Pong - The game";
    constexpr raylib::Color MyBackgroundColor{122, 172, 216, UINT8_MAX};
   
    raylib::InitWindow(width, height, title);

    GameState currentState{GameState::MENU};
    Difficulty difficulty{Difficulty::EASY};

    Menu myMenu{MyBackgroundColor};
    Game myGame{MyBackgroundColor};

    raylib::SetTargetFPS(60);
    while (!raylib::WindowShouldClose())
    {
        myMenu.showMenu(currentState, difficulty);
        myGame.play(currentState, difficulty);
        myMenu.showEndCredits(currentState);
    }

    raylib::CloseWindow();

    return 0;
}

 