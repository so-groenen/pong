#include "game.hpp"


const char* WINDOW_TITLE                {"Pong!"};
constexpr uint32_t WIDTH                {1920UL};
constexpr uint32_t HEIGHT               {1080UL};
constexpr raylib::Color BACKGROUND_COLOR{11, 43, 55, UINT8_MAX};
constexpr raylib::Color OUTER_LINE_COLOR{82, 116, 165, UINT8_MAX};
constexpr raylib::Color FIELD_COLOR     {122, 172, 216, UINT8_MAX};
constexpr float LINE_THICKNESS          {5.f};
constexpr uint32_t TARGET_FPS           {60UL};
constexpr float DEFAULT_ZOOM            {0.75f};

 
void draw_playing_field(int screen_width, int screen_height, const raylib::Color& outer_color,  const raylib::Color& inner_color, int thickness) 
{
    raylib::DrawRectangle(0, 0, screen_width, screen_height, inner_color);

    raylib::DrawRectangle(-thickness, -thickness, screen_width + 2*thickness, thickness, outer_color);
    raylib::DrawRectangle(-thickness, screen_height, screen_width + 2*thickness, thickness, outer_color);
    raylib::DrawRectangle(-thickness, 0, thickness, screen_height, outer_color);
    raylib::DrawRectangle(screen_width, 0, thickness, screen_height, outer_color);
}



Game::Game()
{
    raylib::InitWindow(WIDTH, HEIGHT, WINDOW_TITLE);

    m_camera.target   = {to_float(WIDTH)/2.f, to_float(HEIGHT)/2.f};
    m_camera.offset   = {to_float(WIDTH)/2.f, to_float(HEIGHT)/2.f};
    m_camera.rotation = 0.f;
    m_camera.zoom     = DEFAULT_ZOOM;
}
void Game::run()
{
    m_scene = std::make_unique<MenuScene>();

    raylib::SetTargetFPS(TARGET_FPS);
    while (!raylib::WindowShouldClose())
    {
        float dt = raylib::GetFrameTime();

        m_scene->update_logic(dt);
        raylib::draw(BACKGROUND_COLOR, m_camera, [&]
        {
            draw_playing_field(WIDTH, HEIGHT, OUTER_LINE_COLOR, FIELD_COLOR, LINE_THICKNESS);
            m_scene->draw();
        });


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
