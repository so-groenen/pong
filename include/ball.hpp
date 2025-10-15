#ifndef BALL_HPP
#define BALL_HPP 

#include "pong.hpp"
#include "utilities.hpp"
#include "Block.hpp"

class Ball
{
    raylib::Vector2 m_position{};
    raylib::Vector2 m_velocity{0.1, 0.1};
    raylib::Color m_color{raylib::VIOLET};
    raylib::RenderTexture2D m_renderTexture{};
    float m_radius{};
    float m_winWidth{};
    float m_winHeight{};
    bool isBelow(float bottom) const
    {
        bool centerIsBelow = (m_position.y             < bottom);
        bool isTouching    = (m_position.y + m_radius >= bottom);
        return (centerIsBelow && isTouching);
    }
    bool isAbove(float top) const
    {
        bool centerIsAbove  = (m_position.y             > top);
        bool isTouching     = (m_position.y + m_radius <= top);
        return (centerIsAbove && isTouching);
    }
    bool isLeft(float left) const
    {
        bool centerIsLeft  = (m_position.x             < left);
        bool isTouching    = (m_position.x + m_radius >= left);
        return (centerIsLeft && isTouching);
    }
    bool isRight(float right) const
    {
        bool centerIsRight  = (m_position.x             < right);
        bool isTouching     = (m_position.x + m_radius >= right);
        return (centerIsRight && isTouching);
    }
    void swapTexture(raylib::RenderTexture2D& t1, raylib::RenderTexture2D& t2)
    {
        raylib::RenderTexture2D temp = t1;
        t1 = t2;
        t2 = temp;
    }
    void swapRadii(float& r1, float& r2) const
    {
        float temp = r1;
        r1 = r2;
        r2 = temp;
    }
public:
    Ball() = default;
    Ball(float r)
        : m_radius{r}
    {
        if(!raylib::IsWindowReady())
        {
            throw std::runtime_error("Ball creation error: Window not ready!\n");
        }
        m_winWidth  = toFloat(raylib::GetScreenWidth());
        m_winHeight = toFloat(raylib::GetScreenHeight());
        m_position.x = m_winWidth /2;
        m_position.y = m_winHeight /2;

        m_renderTexture = raylib::LoadRenderTexture( toInt(m_radius*2.f), toInt(m_radius*2.f) );  
        raylib::BeginTextureMode(m_renderTexture);
            raylib::ClearBackground(raylib::BLANK);
            raylib::DrawCircle(toInt(m_radius), toInt(m_radius), m_radius, m_color);
        raylib::EndTextureMode();
    }
    Ball(const Ball& other)            = delete; // No copy! Otherwise we run into trouble when one gets destroyed and releases the render texture
    Ball& operator=(const Ball& other) = delete; // same.
    Ball& operator=(Ball&& other)               // only move allowed.
    {
        if(this != &other)
        {
            swapTexture(m_renderTexture, other.m_renderTexture);
            swapRadii(m_radius,          other.m_radius);        //gets unloaded when going out of scope.
 
            m_position  = other.m_position;
            m_velocity  = other.m_velocity;
            m_color     = other.m_color;
            m_winHeight = other.m_winHeight;
            m_winWidth  = other.m_winWidth;
        }
        return *this;
    }
    void draw() const
    {
        raylib::DrawTexture(m_renderTexture.texture, 
                            m_position.x - m_radius,
                            m_position.y - m_radius,
                            raylib::WHITE);
    }
    void setVelocity(raylib::Vector2 vel)
    {
        m_velocity = vel;
    }
    void checkWallCollision()
    {
        // if (m_position.x <= m_radius || m_position.x >= (m_winWidth - m_radius) )
        // {
        //     m_velocity.x *= -1;
        // }
        if (m_position.y <= m_radius || m_position.y >= (m_winHeight - m_radius) )
        {
            m_velocity.y *= -1;
        }
    }
    void checkBlockCollision(const Block& block)
    {
        if (raylib::CheckCollisionCircleRec(m_position, m_radius, block.getRect()))
        {   
            float xLeft   = block.getRect().x;
            float xRight  = block.getRect().x + block.getRect().width;
            float yBottom = block.getRect().y;
            float yTop    = block.getRect().y + block.getRect().height;
            if(isLeft(xLeft))
            {
                m_position.x  = xLeft - m_radius;
                if (m_velocity.x > 0)
                {
                    m_velocity.x *= -1;
                }                
            }
            else if(isRight(xRight))
            {
                m_position.x  = xRight + m_radius;
                if (m_velocity.x < 0)
                {
                    m_velocity.x *= -1;
                }                
            }
            else if(isBelow(yBottom))
            {
                m_position.y  = yBottom - m_radius;
                if (m_velocity.y > 0)
                {
                    m_velocity.y *= -1;
                }                
            }
            else if(isAbove(yTop))
            {
                m_position.y  = yTop + m_radius;
                if (m_velocity.y < 0)
                {
                    m_velocity.y *= -1;
                }                
            } 
        }
    }

    void move()
    {
        m_position.x += m_velocity.x;
        m_position.y += m_velocity.y;
    }
    raylib::Vector2 getPos() const
    {
        return m_position;
    }
    void resetPosition()
    {
        m_position.x = m_winWidth /2;
        m_position.y = m_winHeight /2;
    }
    float getRadius() const
    {
        return m_radius;
    }
    ~Ball()
    {
        raylib::UnloadRenderTexture(m_renderTexture);
    }
};

#endif