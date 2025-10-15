#ifndef MENU_HPP
#define MENU_HPP

#include "pong.hpp"
#include "utilities.hpp"
#include <array>

class Menu
{
    const char* m_MenuText{"Pong!"};
    const char* m_WonText{"Congrats, You Won!!!"};
    const char* m_LostText{"Oh you lost..."};
    const float m_textSpacing{5};
    float m_fontSize{40};
    raylib::Font m_font{};
    raylib::Vector2 m_pos{};
    raylib::Color m_backgroundColor{};

public:
    Menu(raylib::Color MyBackgroundColor)
        :  m_font{raylib::GetFontDefault()}, m_backgroundColor{MyBackgroundColor}
    {
        if(!raylib::IsWindowReady())
        {
            throw std::runtime_error("Menu creation error: Window not ready!\n");
        }
        // raylib::Vector2 TxtSz {raylib::MeasureTextEx(m_font, m_MenuText, m_fontSize, m_textSpacing)};
        // m_pos = raylib::Vector2{toFloat(raylib::GetScreenWidth())/2 - TxtSz.x/2, toFloat(raylib::GetScreenHeight())/2 - TxtSz.y/2};
    }
    // void showTitleScreen(GameState& currentState) const
    // {

    //     while (!raylib::WindowShouldClose() && isMenu(currentState))
    //     {
    //         // handle player input
    //         if (raylib::IsKeyPressed(raylib::KEY_SPACE))
    //         {
    //             currentState = GameState::SELECT;
    //             // currentState = GameState::ISRUNNING;
    //         }
            
    //         // draw
    //         raylib::BeginDrawing();
    //             raylib::ClearBackground(m_backgroundColor);
    //             raylib::DrawTextEx(m_font, m_MenuText, m_pos, m_fontSize, m_textSpacing, raylib::BLACK);
    //         raylib::EndDrawing();
    //     }
    // }
    void showMenu(GameState& currentState, Difficulty& difficulty)
    {

        difficulty               = Difficulty::EASY;

        const float fontSize   = 30;
        const float thickness  = 3;
        const float winWidth   = toFloat(raylib::GetScreenWidth());
        const float winHeight  = toFloat(raylib::GetScreenHeight());
                

        raylib::Vector2 EasySize{raylib::MeasureTextEx(m_font,      "Easy", fontSize, m_textSpacing)};
        raylib::Vector2 MediumSize{raylib::MeasureTextEx(m_font,    "Medium", fontSize, m_textSpacing)};
        raylib::Vector2 DifficultSize{raylib::MeasureTextEx(m_font, "Difficult", fontSize, m_textSpacing)};

        raylib::Vector2 positionEasy = raylib::Vector2{(winWidth - EasySize.x)/2,      2*winHeight/6};
        raylib::Vector2 positionMed  = raylib::Vector2{(winWidth - MediumSize.x)/2,    3*winHeight/6};
        raylib::Vector2 positionDif  = raylib::Vector2{(winWidth - DifficultSize.x)/2, 4*winHeight/6};

        float boxWidth  = (1.2)*DifficultSize.x;
        float boxHeight = (1.4)*DifficultSize.y;
        float boxXStart = (winWidth - boxWidth)/2;

        float y1 = (positionEasy.y + EasySize.y/2)      - boxHeight/2;
        float y2 = (positionMed.y  + MediumSize.y/2)    - boxHeight/2;
        float y3 = (positionDif.y  + DifficultSize.y/2) - boxHeight/2;

        std::array<raylib::Rectangle, 3> rects = 
        {
            raylib::Rectangle{boxXStart, y1, boxWidth, boxHeight},
            raylib::Rectangle{boxXStart, y2, boxWidth, boxHeight},
            raylib::Rectangle{boxXStart, y3, boxWidth, boxHeight},
        };
        size_t index = 0; 

        raylib::Vector2 TxtSz {raylib::MeasureTextEx(m_font, m_MenuText, m_fontSize, m_textSpacing)};
        m_pos = raylib::Vector2{(winWidth-TxtSz.x)/2, (0.1f)*winHeight};

        while (!raylib::WindowShouldClose() && isMenu(currentState))
        {
            // handle user input
            if (raylib::IsKeyPressed(raylib::KEY_DOWN) && index < rects.size()-1)
            {
                next(difficulty);
                index++;
            }
            if (raylib::IsKeyPressed(raylib::KEY_UP) && index > 0)
            {
                previous(difficulty);
                index--;
            }
            if (raylib::IsKeyPressed(raylib::KEY_SPACE) || raylib::IsKeyPressed(raylib::KEY_ENTER))
            {
                currentState = GameState::ISRUNNING;
            }

            // draw
            raylib::BeginDrawing();
                raylib::ClearBackground(m_backgroundColor);
                raylib::DrawTextEx(m_font, m_MenuText, m_pos, m_fontSize, m_textSpacing, raylib::BLACK);

                raylib::DrawRectangleLinesEx(rects.at(index), thickness, raylib::BLACK);
                raylib::DrawTextEx(m_font, "Easy",      positionEasy, fontSize, m_textSpacing, raylib::BLACK);
                raylib::DrawTextEx(m_font, "Medium",    positionMed,  fontSize, m_textSpacing, raylib::BLACK);
                raylib::DrawTextEx(m_font, "Difficult", positionDif,  fontSize, m_textSpacing, raylib::BLACK);
            raylib::EndDrawing();
        }

    }
    void showEndCredits(GameState& currentState) const
    {

        std::string text{};
        switch (currentState)
        {
        case GameState::WON:
            text = m_WonText;
            break;
        case GameState::LOST:
            text = m_LostText;
            break;
        default:
            break;
        }
        float fontSize = 30;
        raylib::Vector2 TxtSz{raylib::MeasureTextEx(m_font, text.c_str(), fontSize, m_textSpacing)};
        raylib::Vector2 position = raylib::Vector2{toFloat(raylib::GetScreenWidth())/2 - TxtSz.x/2, toFloat(raylib::GetScreenHeight())/2 - TxtSz.y/2};


        while (!raylib::WindowShouldClose() && isEndingCredits(currentState))
        {
            // handle user input
            if (raylib::IsKeyPressed(raylib::KEY_SPACE))
            {
                currentState = GameState::MENU;
            }
            
            // draw
            raylib::BeginDrawing();
                raylib::ClearBackground(m_backgroundColor);
                raylib::DrawTextEx(m_font, text.c_str(), position, fontSize, m_textSpacing, raylib::BLACK);
            raylib::EndDrawing();
        }
    }
};
 


#endif