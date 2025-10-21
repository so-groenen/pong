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
}
#include <cstdint>

 
#endif