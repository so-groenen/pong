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
    EnemyBlock(raylib::Vector2 position)
        :  Block{position}
    {
    }
    EnemyBlock& operator=(const EnemyBlock& other) = default;
    void set_line_of_sight(float line_of_s)
    {
        m_line_of_sight = line_of_s;
    }
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
        else
        {
            stand_still();
        }
    }
    ~EnemyBlock() = default;
};

#endif