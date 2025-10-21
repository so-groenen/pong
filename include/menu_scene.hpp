#ifndef MENU_HPP
#define MENU_HPP

#include "raylib_backend.hpp"
#include "difficulty.hpp"
#include "utilities.hpp"
#include <array>
#include "interface_game_scene.hpp" 

struct MenuCanvas
{
    raylib::Font font{raylib::GetFontDefault()};

    const float thickness   = 3;
    const float win_width   = to_float(raylib::GetScreenWidth());
    const float win_height  = to_float(raylib::GetScreenHeight());
                
    raylib::Color backgroundColor{};

    raylib::Vector2 easy_size{};       // Gets init at runtime
    raylib::Vector2 medium_size{};     // Gets init at runtime
    raylib::Vector2 difficult_size{};  // Gets init at runtime

    raylib::Vector2 position_easy = raylib::Vector2{(win_width - easy_size.x)/2,      2*win_height/6};
    raylib::Vector2 position_med  = raylib::Vector2{(win_width - medium_size.x)/2,    3*win_height/6};
    raylib::Vector2 position_dif  = raylib::Vector2{(win_width - difficult_size.x)/2, 4*win_height/6};

    float box_width  = (1.2)*difficult_size.x;
    float box_height = (1.4)*difficult_size.y;
    float box_x_start = (win_width - box_width)/2;

    float y1 = (position_easy.y + easy_size.y/2)      - box_height/2;
    float y2 = (position_med.y  + medium_size.y/2)    - box_height/2;
    float y3 = (position_dif.y  + difficult_size.y/2) - box_height/2;

    std::array<raylib::Rectangle, 3> selections = 
    {
        raylib::Rectangle{box_x_start, y1, box_width, box_height},
        raylib::Rectangle{box_x_start, y2, box_width, box_height},
        raylib::Rectangle{box_x_start, y3, box_width, box_height},
    };
    raylib::Vector2 title_txt_size {};
    MenuCanvas(const char* title,  raylib::Color bg_color);
    void draw(size_t index) const;
private:
    raylib::Vector2 title_pos() const;
};



class MenuScene : public IGameScene
{
    Difficulty m_difficulty{Difficulty::Easy};
    MenuCanvas m_canvas;
    bool m_is_finished{false};
public:
    MenuScene(raylib::Color bg_color);
    void update_logic() override;
    bool is_finished() const override;
    void draw() const override;
    Difficulty get_difficulty() const ;
    auto on_exit() -> std::unique_ptr<IGameScene> override;
    ~MenuScene() = default;
};
 
 
 
#endif