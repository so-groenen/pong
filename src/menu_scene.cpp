#include "menu_scene.hpp"
#include "game_scene.hpp"

const char* TITLE     {"Pong!"};
const char* Easy      {"Easy"};
const char* Medium    {"Medium"};
const char* Difficult {"Difficult"};

constexpr float TEXTSPACING     {5};
constexpr float TITLE_FONTSIZE  {120};
constexpr float SELECT_FONTSIZE {50};
 
 
MenuCanvas::MenuCanvas(const char* title)
    : easy_size     {raylib::MeasureTextEx(font, Easy, SELECT_FONTSIZE, TEXTSPACING)},
    medium_size   {raylib::MeasureTextEx(font, Medium, SELECT_FONTSIZE, TEXTSPACING)},
    difficult_size{raylib::MeasureTextEx(font, Difficult, SELECT_FONTSIZE, TEXTSPACING)},
    title_txt_size{raylib::MeasureTextEx(font, title, TITLE_FONTSIZE, TEXTSPACING)}
{
}
raylib::Vector2 MenuCanvas::title_pos() const
{
    return raylib::Vector2{(win_width-title_txt_size.x)/2, (0.1f)*win_height};
}
void MenuCanvas::draw(size_t index) const 
{
    static auto position = raylib::Vector2{(win_width-title_txt_size.x)/2, (0.1f)*win_height};
    raylib::DrawTextEx(font, TITLE, position, TITLE_FONTSIZE, TEXTSPACING, raylib::BLACK);
    raylib::DrawRectangleLinesEx(selections.at(index), thickness, raylib::BLACK);
    
    raylib::DrawTextEx(font, Easy,      position_easy, SELECT_FONTSIZE, TEXTSPACING, raylib::BLACK);
    raylib::DrawTextEx(font, Medium,    position_med,  SELECT_FONTSIZE, TEXTSPACING, raylib::BLACK);
    raylib::DrawTextEx(font, Difficult, position_dif,  SELECT_FONTSIZE, TEXTSPACING, raylib::BLACK);
}

 
 


MenuScene::MenuScene()
    :  m_canvas{TITLE}
{
    if(!raylib::IsWindowReady())
    {
        throw std::runtime_error("Menu creation error: Window not ready!\n");
    }
}
void MenuScene::update_logic(float dt)
{
    if (raylib::IsKeyPressed(raylib::KEY_DOWN))
    {
        ++m_difficulty; // correct range is ensured with operator overload
    }
    if (raylib::IsKeyPressed(raylib::KEY_UP))
    {
        --m_difficulty; 
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
    m_canvas.draw(to_size_t(m_difficulty));
}
Difficulty MenuScene::get_difficulty() const
{
    return m_difficulty;
}
auto MenuScene::on_exit() -> std::unique_ptr<IGameScene>  
{
    // raylib::Color bg_color = m_canvas.background_color;
    return std::make_unique<GamePlayScene>(get_difficulty());
}
