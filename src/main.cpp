#include "raylib_backend.hpp"
#include "menu_scene.hpp"
#include "interface_game_scene.hpp"

int main()
{
    const uint32_t width    = 1024;
    const uint32_t height   = 512;
    const char* title       = "Pong - The game";
    constexpr raylib::Color bg_color{122, 172, 216, UINT8_MAX};
   
    raylib::InitWindow(width, height, title);

    raylib::SetTargetFPS(60);

    
    std::unique_ptr<IGameScene> scene = std::make_unique<MenuScene>(bg_color);
    while (!raylib::WindowShouldClose())
    {
        scene->update_logic();
        scene->draw();
        if (scene->is_finished())
        {
            std::unique_ptr<IGameScene> current = std::move(scene);
            scene = current->on_exit();
        }
    }
    raylib::CloseWindow();
    return 0;
}


