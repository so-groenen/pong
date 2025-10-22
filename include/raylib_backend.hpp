#ifndef RAYLIB_BACKEND
#define RAYLIB_BACKEND

#include <iostream>
#include <stdexcept>
 
namespace raylib
{
    #include "raylib.h"
    
    template<typename F>
    inline void draw(F draw_func) 
    requires std::invocable<F>
    {
        BeginDrawing();
            draw_func();
        EndDrawing();
    }
    template<typename F>
    inline void draw(Color bg_color, F draw_func) 
    requires std::invocable<F>
    {
        BeginDrawing();
        ClearBackground(bg_color);
            draw_func();
        EndDrawing();
    }

    template<typename F>
    inline void draw(Color bg_color, const Camera2D& camera, F draw_func) 
    requires std::invocable<F>
    {
        BeginDrawing();
        ClearBackground(bg_color);
            BeginMode2D(camera);
            draw_func();
            EndMode2D();
        EndDrawing();
    }
    inline Vector2 operator*(const Vector2& vec, float s)
    {
        return {s*vec.x, s*vec.y};
    }
    inline Vector2 operator*(float s, const Vector2& vec)
    {
        return {s*vec.x, s*vec.y};
    }
    inline Vector2 operator+(Vector2 lhs, const Vector2& rhs)
    {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }
    inline Vector2& operator+=(Vector2& lhs, const Vector2& rhs)
    {
        lhs.x += rhs.x;
        lhs.y += rhs.y;
        return lhs;
    }
}
#include <cmath>
#include <cstdint>
 

#endif