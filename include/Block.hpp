#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include "raylib_backend.hpp"
#include "utilities.hpp"

constexpr float BLOCK_WIDTH_RATIO      {0.025f}; // x windows width
constexpr float BLOCK_HEIGHT_RATIO     {0.4f};   // x windows height
constexpr float DEFAULT_VELOCITY_RATIO {0.02f};  // x windows height


class Block
{
    raylib::Vector2   m_position{};
    raylib::Color     m_color{raylib::VIOLET};
    raylib::Rectangle m_rect{};
    float m_win_height{};
    float m_win_width{};
    float m_delta_y{};   // By how much do we move?
public:
    Block() = default;
    Block(raylib::Vector2 position)
        : m_position{position}
    {
        if(!raylib::IsWindowReady())
        {
            throw std::runtime_error("Block creation error: Window not ready!\n");
        }
        m_win_width    = to_float(raylib::GetScreenWidth());
        m_win_height   = to_float(raylib::GetScreenHeight());
        m_rect.width   = BLOCK_WIDTH_RATIO  * m_win_width;;
        m_rect.height  = BLOCK_HEIGHT_RATIO * m_win_height;
        m_rect.x       = position.x;
        m_rect.y       = position.y;
        m_delta_y      = DEFAULT_VELOCITY_RATIO * m_win_height;
    }
    Block& operator=(const Block& other) = default;

    void move_up()
    {
        if (m_rect.y > 0)
        {
            m_rect.y -= m_delta_y;
        }
    }
    void set_color(raylib::Color color)
    {
        m_color = color;
    }
    float velocity() const 
    {
        return m_delta_y;
    }
    void move_down()
    {
        if (m_rect.y < (m_win_height - m_rect.height) )
        {
            m_rect.y += m_delta_y;
        }
    }
    //velocity in [%_windows Height] pixel per 1/60 s. . 
    void set_velocity(float p)
    {       
        m_delta_y = p*m_win_height;
    }
    void draw() const
    {
        raylib::DrawRectangleRec(m_rect, m_color);
    }
    raylib::Vector2 center() const
    {
        return {m_rect.x + m_rect.width/2, m_rect.y + m_rect.height/2};
    }
    raylib::Rectangle rect() const
    {
        return m_rect;
    }
    ~Block() = default;
};

#endif