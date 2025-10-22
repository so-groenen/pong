#include "ending_scene.hpp"
#include "menu_scene.hpp"

const char* WIN_TEXT                 {"Congrats, You Won!!!"};
const char* LOST_TEXT                {"Oh you lost..."};
constexpr float ENDING_TEXT_SPACING  {5};
constexpr float ENDING_FONTSIZE      {120};

const char* get_ending_txt(bool has_won)
{
    return has_won? WIN_TEXT : LOST_TEXT;
}


EndingScene::EndingScene(bool has_won)
    : m_text{get_ending_txt(has_won)} 
{
    if(!raylib::IsWindowReady())
    {
        throw std::runtime_error("EndingScene: Window not ready!\n");
    }
    title_txt_size = raylib::MeasureTextEx(m_font, m_text, ENDING_FONTSIZE, ENDING_TEXT_SPACING);
    position       = raylib::Vector2{to_float(raylib::GetScreenWidth())/2 - title_txt_size.x/2, to_float(raylib::GetScreenHeight())/2 - title_txt_size.y/2};
}
bool EndingScene::is_finished() const
{
    return m_is_finished;
} 
void EndingScene::update_logic(float dt)
{
    if (raylib::IsKeyPressed(raylib::KEY_SPACE))
    {
        m_is_finished = true;
    }
}
auto EndingScene::on_exit() -> std::unique_ptr<IGameScene>
{
    return std::make_unique<MenuScene>();
}
void EndingScene::draw() const
{
    raylib::DrawTextEx(m_font, m_text, position, ENDING_FONTSIZE, ENDING_TEXT_SPACING, raylib::BLACK);
}



