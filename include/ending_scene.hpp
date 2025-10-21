#ifndef ENDING_HPP
#define ENDING_HPP

#include "raylib_backend.hpp"
#include "interface_game_scene.hpp"
#include "utilities.hpp"

class EndingScene : public IGameScene
{
    const char* m_text;
    raylib::Font m_font{raylib::GetFontDefault()};
    raylib::Color m_background_color{};
    raylib::Vector2 title_txt_size{};
    raylib::Vector2 position{raylib::Vector2{to_float(raylib::GetScreenWidth())/2 - title_txt_size.x/2, to_float(raylib::GetScreenHeight())/2 - title_txt_size.y/2}};
    bool m_is_finished{};
public:
    EndingScene(bool has_won, raylib::Color bg_color);
    bool is_finished() const override;
    void update_logic() override;
    auto on_exit() -> std::unique_ptr<IGameScene> override;
    void draw() const override;
    ~EndingScene() = default;
};
 
 

#endif