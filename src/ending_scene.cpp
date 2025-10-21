#include "ending_scene.hpp"
#include "menu_scene.hpp"

constexpr float ENDING_TEXT_SPACING = 5;
constexpr float ENDING_FONTSIZE = 30;
const char* WIN_TEXT = "Congrats, You Won!!!";
const char* LOST_TEXT = "Oh you lost...";

const char* get_ending_txt(bool has_won)
{
    if (has_won)
    {
        return WIN_TEXT;
    }
    return LOST_TEXT;
}


EndingScene::EndingScene(bool has_won, raylib::Color bg_color)
    : m_text{get_ending_txt(has_won)}, 
     m_backgroundColor{bg_color}
{
    if(!raylib::IsWindowReady())
    {
        throw std::runtime_error("Menu creation error: Window not ready!\n");
    }
    TxtSz    = raylib::MeasureTextEx(m_font, m_text, ENDING_FONTSIZE, ENDING_TEXT_SPACING);
    position = raylib::Vector2{toFloat(raylib::GetScreenWidth())/2 - TxtSz.x/2, toFloat(raylib::GetScreenHeight())/2 - TxtSz.y/2};
}
bool EndingScene::is_finished() const
{
    return m_is_finished;
} 
void EndingScene::update_logic()
{
    if (raylib::IsKeyPressed(raylib::KEY_SPACE))
    {
        m_is_finished = true;
    }
}
auto EndingScene::on_exit() -> std::unique_ptr<IGameScene>
{
    raylib::Color bg_color{122, 172, 216, UINT8_MAX};
    return std::make_unique<MenuScene>(bg_color);
}
void EndingScene::draw() const
{
    raylib::draw([&]
    {
        raylib::ClearBackground(m_backgroundColor);
        raylib::DrawTextEx(m_font, m_text, position, ENDING_FONTSIZE, ENDING_TEXT_SPACING, raylib::BLACK);
    });
    // raylib::BeginDrawing();
    //     raylib::ClearBackground(m_backgroundColor);
    //     raylib::DrawTextEx(m_font, m_text, position, ENDING_FONTSIZE, ENDING_TEXT_SPACING, raylib::BLACK);
    // raylib::EndDrawing();
}



