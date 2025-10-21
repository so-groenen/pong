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
}
#include <cstdint>


#endif