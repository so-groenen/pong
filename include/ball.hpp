#ifndef BALL_HPP
#define BALL_HPP 

#include "raylib_backend.hpp"
#include "utilities.hpp"
#include "block.hpp"
#include <print>

constexpr float DRIFT_COEFF {0.3f};

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
    inline bool is_below(float bottom) const
    {
        return (m_position.y < bottom); 
    }
    inline bool is_above(float top) const
    {
        return (m_position.y > top);
    }
    inline bool is_left(float left) const
    {
        return (m_position.x < left);
    }
    inline bool is_right(float right) const
    {
        return (m_position.x >= right);
    }
    inline raylib::Vector2 next_pos() const 
    {
        return {m_position.x + m_velocity.x,m_position.y + m_velocity.y};
    }
public: 
    explicit Ball(raylib::Vector2 velocity = (raylib::Vector2){5.f,5.f}, raylib::Color color = raylib::VIOLET, float r = 10)
        : m_velocity{velocity}, m_color{color}, m_radius{r}
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
        std::println("Ball texture created: size: {}x{}, rad: {}", m_render_tex.texture.width,m_render_tex.texture.height, m_radius);
    }
    void set_position(raylib::Vector2 pos)
    {
        m_position = pos;
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
                            m_position.x - m_render_tex.texture.width/2.f,
                            m_position.y - m_render_tex.texture.height/2.f,
                            raylib::WHITE);
    }
    void set_velocity(raylib::Vector2 vel)
    {
        m_velocity = vel;
    }
    void check_wall_collision()
    {
        if (next_pos().y <= m_radius || next_pos().y >= (m_win_height - m_radius) )
        {
            m_velocity.y *= -1;
        }
    }
    void check_block_collision(const Block& block)
    {
        if (raylib::CheckCollisionCircleRec(next_pos(), m_radius, block.rect()))
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

            if(is_below(y_bottom))
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
            m_velocity.y += DRIFT_COEFF * block.vertical_velocity();
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