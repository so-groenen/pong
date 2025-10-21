#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "block.hpp"
#include "ball.hpp"
#include <cmath>

class EnemyBlock: public Block
{
    float m_lineOfsight{};
public:
    EnemyBlock() = default;
    EnemyBlock(raylib::Vector2 position, float lineOfSight)
        :  Block{position}, m_lineOfsight{lineOfSight}
    {
    }
    EnemyBlock& operator=(const EnemyBlock& other) = default;
    void move(const Ball& ball)
    {
        if ( fabs(ball.getPos().x-getCenter().x) < m_lineOfsight )
        {
            if (ball.getPos().y < getCenter().y)
            {
                moveUp();
            }
            if (ball.getPos().y > getCenter().y)
            {
                moveDown();
            }    
        }
    }
    ~EnemyBlock() = default;
};

#endif