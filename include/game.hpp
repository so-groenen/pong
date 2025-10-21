#ifndef GAME_HPP
#define GAME_HPP

#include "raylib_backend.hpp"
#include "menu_scene.hpp"
#include "interface_game_scene.hpp"

class Game 
{
    std::unique_ptr<IGameScene> m_scene{};
    raylib::Camera2D m_camera{};
public:
    Game();
    void run();
    ~Game();
};



#endif