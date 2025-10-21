
#include "pong.hpp"
#include "menu_scene.hpp"
#include "game_scene.hpp"

const char* TITLE = "Pong!";
constexpr float TEXTSPACING = 5;
constexpr float TITLE_FONTSIZE = 40;
constexpr float SELECT_FONTSIZE = 30;



 
MenuCanvas::MenuCanvas(const char* title,  raylib::Color bg_color)
    : backgroundColor{bg_color}, 
    EasySize{raylib::MeasureTextEx(font, "Easy", SELECT_FONTSIZE, TEXTSPACING)},
    MediumSize{raylib::MeasureTextEx(font, "Medium", SELECT_FONTSIZE, TEXTSPACING)},
    DifficultSize{raylib::MeasureTextEx(font, "Difficult", SELECT_FONTSIZE, TEXTSPACING)},
    TxtSz {raylib::MeasureTextEx(font, title, SELECT_FONTSIZE, TEXTSPACING)}
{
}
raylib::Vector2 MenuCanvas::title_pos() const
{
    return raylib::Vector2{(winWidth-TxtSz.x)/2, (0.1f)*winHeight};
}
void  MenuCanvas::draw(size_t index) const 
{
    static auto position = raylib::Vector2{(winWidth-TxtSz.x)/2, (0.1f)*winHeight};
    
    raylib::draw([&]
    {
        raylib::ClearBackground(backgroundColor);
        raylib::DrawTextEx(font, TITLE, position, TITLE_FONTSIZE, TEXTSPACING, raylib::BLACK);
        raylib::DrawRectangleLinesEx(selections.at(index), thickness, raylib::BLACK);
        raylib::DrawTextEx(font, "Easy",      positionEasy, SELECT_FONTSIZE, TEXTSPACING, raylib::BLACK);
        raylib::DrawTextEx(font, "Medium",    positionMed,  SELECT_FONTSIZE, TEXTSPACING, raylib::BLACK);
        raylib::DrawTextEx(font, "Difficult", positionDif,  SELECT_FONTSIZE, TEXTSPACING, raylib::BLACK);
    });
}

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
 


MenuScene::MenuScene(raylib::Color bg_color)
    :  m_canvas{TITLE, bg_color}
{
    // if(!raylib::IsWindowReady())
    // {
    //     throw std::runtime_error("Menu creation error: Window not ready!\n");
    // }
}
void MenuScene::update_logic()
{
    if (raylib::IsKeyPressed(raylib::KEY_DOWN) && m_select_index < m_canvas.selections.size()-1)
    {
        next(m_difficulty);
        m_select_index++;
    }
    if (raylib::IsKeyPressed(raylib::KEY_UP) && m_select_index > 0)
    {
        previous(m_difficulty);
        m_select_index--;
    }
    if (raylib::IsKeyPressed(raylib::KEY_SPACE) || raylib::IsKeyPressed(raylib::KEY_ENTER))
    {
        m_is_finished = true;
    }
}
bool MenuScene::is_finished() const
{
    return m_is_finished;
}
void MenuScene::draw()  const  
{
    m_canvas.draw(m_select_index);
}
Difficulty MenuScene::get_difficulty() const
{
    return m_difficulty;
}
auto MenuScene::on_exit() -> std::unique_ptr<IGameScene>  
{
    raylib::Color bg_color = m_canvas.backgroundColor;
    return std::make_unique<GamePlayScene>(bg_color, get_difficulty());
}
