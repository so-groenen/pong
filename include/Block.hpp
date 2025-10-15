#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include "pong.hpp"
#include "utilities.hpp"

class Block
{
    raylib::Vector2   m_position{};
    raylib::Color     m_color{raylib::VIOLET};
    raylib::Rectangle m_rect{};
    float m_winHeight{};
    float m_winWidth{};
    float m_deltaY{};
public:
    Block() = default;
    Block(raylib::Vector2 position)
        : m_position{position}
    {
        if(!raylib::IsWindowReady())
        {
            throw std::runtime_error("Block creation error: Window not ready!\n");
        }
        m_winWidth          = toFloat(raylib::GetScreenWidth());
        m_winHeight         = toFloat(raylib::GetScreenHeight());
        m_rect.width        = 0.025f*m_winWidth;;
        m_rect.height       = 0.4f*m_winHeight;
        m_rect.x            = position.x;
        m_rect.y            = position.y;
        m_deltaY            = 0.02f * m_winHeight;
    }
    Block& operator=(const Block& other) = default;

    void setDeltaY(float deltay)
    {
        m_deltaY = deltay;
    }
    void moveUp()
    {
        if (m_rect.y > 0)
        {
            m_rect.y -= m_deltaY;
        }
    }
    void setColor(raylib::Color color)
    {
        m_color = color;
    }
    void moveDown()
    {
        if (m_rect.y < (m_winHeight - m_rect.height) )
        {
            m_rect.y += m_deltaY;
        }
    }
    //velocity in [%_windows Height] pixel per 1/60 s. . 
    void setVelocity(float p)
    {       
        m_deltaY = p*m_winHeight;
    }
    void draw() const
    {
        raylib::DrawRectangleRec(m_rect, m_color);
    }
    raylib::Vector2 getCenter() const
    {
        return {m_rect.x + m_rect.width/2, m_rect.y + m_rect.height/2};
    }
    raylib::Rectangle getRect() const
    {
        return m_rect;
    }
    ~Block() = default;
};

#endif