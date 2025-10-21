#include "game.hpp"

constexpr raylib::Color BACKGROUND_COLOR{122, 172, 216, UINT8_MAX};
constexpr uint32_t WIDTH                {1024};
constexpr uint32_t HEIGHT               {512};
const char* WINDOW_TITLE                {"Pong!"};
constexpr uint32_t TARGET_FPS           {60};

 
Game::Game()
{
    raylib::InitWindow(WIDTH, HEIGHT, WINDOW_TITLE);
}
void Game::run()
{
    m_scene = std::make_unique<MenuScene>(BACKGROUND_COLOR);

    raylib::SetTargetFPS(TARGET_FPS);
    while (!raylib::WindowShouldClose())
    {
        m_scene->update_logic();
        m_scene->draw();
        if (m_scene->is_finished())
        {
            std::unique_ptr<IGameScene> current = std::move(m_scene);
            m_scene = current->on_exit();
        }
    }
}
Game::~Game()
{
    raylib::CloseWindow();
}
