#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "block.hpp"
#include "ball.hpp"
#include <cmath>

class EnemyBlock: public Block
{
    float m_line_of_sight{};
public:
    EnemyBlock() = default;
    EnemyBlock(raylib::Vector2 position, float line_of_sight)
        :  Block{position}, m_line_of_sight{line_of_sight}
    {
    }
    EnemyBlock& operator=(const EnemyBlock& other) = default;
    void move(const Ball& ball)
    {
        if ( fabs(ball.position().x-center().x) < m_line_of_sight )
        {
            if (ball.position().y < center().y)
            {
                move_up();
            }
            if (ball.position().y > center().y)
            {
                move_down();
            }    
        }
    }
    ~EnemyBlock() = default;
};

#endif