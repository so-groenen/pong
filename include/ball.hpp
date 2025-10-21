#ifndef BALL_HPP
#define BALL_HPP 

#include "raylib_backend.hpp"
#include "utilities.hpp"
#include "block.hpp"
#include <print>

inline void swap_texture(raylib::RenderTexture2D& t1, raylib::RenderTexture2D& t2)
{
    raylib::RenderTexture2D temp = t1;
    t1 = t2;
    t2 = temp;
}

class Ball
{
    raylib::Vector2 m_position{};
    raylib::Vector2 m_velocity{};
    raylib::Color m_color{raylib::VIOLET};
    raylib::RenderTexture2D m_render_tex{};
    float m_radius{};
    float m_win_width{};
    float m_win_height{};
    bool is_below(float bottom) const
    {
        bool center_is_below = (m_position.y             < bottom);
        bool is_touching    = (m_position.y + m_radius >= bottom);
        return (center_is_below && is_touching);
    }
    bool is_above(float top) const
    {
        bool center_is_above  = (m_position.y             > top);
        bool is_touching     = (m_position.y + m_radius <= top);
        return (center_is_above && is_touching);
    }
    bool is_left(float left) const
    {
        bool center_is_left  = (m_position.x             < left);
        bool is_touching    = (m_position.x + m_radius >= left);
        return (center_is_left && is_touching);
    }
    bool is_right(float right) const
    {
        bool center_is_right  = (m_position.x             < right);
        bool is_touching     = (m_position.x + m_radius >= right);
        return (center_is_right && is_touching);
    }

public:
    explicit Ball(raylib::Vector2 velocity = (raylib::Vector2){5.f,5.f}, float r = 10)
        : m_velocity{velocity}, m_radius{r}
    {
        if(!raylib::IsWindowReady())
        {
            throw std::runtime_error("Ball creation error: Window not ready!\n");
        }
        m_win_width  = to_float(raylib::GetScreenWidth());
        m_win_height = to_float(raylib::GetScreenHeight());
        m_position.x = m_win_width /2;
        m_position.y = m_win_height /2;

        std::println("Ball texture create:");
        m_render_tex = raylib::LoadRenderTexture( to_int(m_radius*2.f), to_int(m_radius*2.f) );  
        raylib::BeginTextureMode(m_render_tex);
            raylib::ClearBackground(raylib::BLANK);
            raylib::DrawCircle(to_int(m_radius), to_int(m_radius), m_radius, m_color);
        raylib::EndTextureMode();
        std::println("Ball texture created!");
    }

    Ball(const Ball& other)            = delete; // No copy! Otherwise we run into trouble when one gets destroyed and releases the render texture
    Ball& operator=(const Ball& other) = delete; // same.
    Ball& operator=(Ball&& other)                // only move allowed.
    {
        if(this != &other)
        {
            swap_texture(m_render_tex, other.m_render_tex);
            m_radius     = other.m_radius;
            m_position   = other.m_position;
            m_velocity   = other.m_velocity;
            m_color      = other.m_color;
            m_win_height = other.m_win_height;
            m_win_width  = other.m_win_width;
            std::println("Ball texture moved!");
        }
        return *this;
    }
    void draw() const
    {
        raylib::DrawTexture(m_render_tex.texture, 
                            m_position.x - m_radius,
                            m_position.y - m_radius,
                            raylib::WHITE);
    }
    void set_velocity(raylib::Vector2 vel)
    {
        m_velocity = vel;
    }
    void check_wall_collision()
    {
        // if (m_position.x <= m_radius || m_position.x >= (m_win_width - m_radius) )
        // {
        //     m_velocity.x *= -1;
        // }
        if (m_position.y <= m_radius || m_position.y >= (m_win_height - m_radius) )
        {
            m_velocity.y *= -1;
        }
    }
    void check_block_collision(const Block& block)
    {
        if (raylib::CheckCollisionCircleRec(m_position, m_radius, block.rect()))
        {   
            float x_left   = block.rect().x;
            float x_right  = block.rect().x + block.rect().width;
            float y_bottom = block.rect().y;
            float y_top    = block.rect().y + block.rect().height;
            if(is_left(x_left))
            {
                m_position.x  = x_left - m_radius;
                if (m_velocity.x > 0)
                {
                    m_velocity.x *= -1;
                }                
            }
            else if(is_right(x_right))
            {
                m_position.x  = x_right + m_radius;
                if (m_velocity.x < 0)
                {
                    m_velocity.x *= -1;
                }                
            }
            else if(is_below(y_bottom))
            {
                m_position.y  = y_bottom - m_radius;
                if (m_velocity.y > 0)
                {
                    m_velocity.y *= -1;
                }                
            }
            else if(is_above(y_top))
            {
                m_position.y  = y_top + m_radius;
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
    raylib::Vector2 position() const
    {
        return m_position;
    }
    void reset_position()
    {
        m_position.x = m_win_width /2;
        m_position.y = m_win_height /2;
    }
    float radius() const
    {
        return m_radius;
    }
    ~Ball()
    {
        std::println("Ball: Unloading render texutre:");
        raylib::UnloadRenderTexture(m_render_tex);
    }
};

#endif