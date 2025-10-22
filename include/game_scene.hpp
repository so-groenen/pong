#ifndef GAME_HPP
#define GAME_HPP

#include "difficulty.hpp"
#include "raylib_backend.hpp"
#include "utilities.hpp"
#include "ball.hpp"
#include "enemy.hpp"
#include "interface_game_scene.hpp"

 
class GamePlayScene : public IGameScene
{
    Block m_player{};
    EnemyBlock m_enemy{};
    Ball m_ball{};
    float m_win_width{};
    float m_win_height{};
    bool m_has_won{};
    bool m_is_finished{false};
public:
    GamePlayScene(Difficulty difficulty);
    void update_logic(float dt) override;
    void draw() const override ;
    bool is_finished() const override ;
    auto on_exit() -> std::unique_ptr<IGameScene> override;
    bool has_won() const ;
    ~GamePlayScene() = default;
};
 


#endif