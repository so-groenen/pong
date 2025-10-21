#include "game_scene.hpp"
#include "ending_scene.hpp"
#include <print>

using namespace std::literals::string_view_literals;


GamePlayScene::GamePlayScene(raylib::Color bg_color, Difficulty difficulty)
:  m_background_color{bg_color}, m_difficulty{difficulty}
{
    if(!raylib::IsWindowReady())
    {
        throw std::runtime_error("Game creation error: Window not ready!\n");
    }

    m_win_width  = to_float(raylib::GetScreenWidth());
    m_win_height = to_float(raylib::GetScreenHeight());

    // set player block
    raylib::Vector2 player_pos{0.05f*m_win_width, 0.5f*m_win_height};
    m_player = Block{player_pos};
    m_player.set_color(raylib::VIOLET);

    // Set enemy block
    float line_of_sight = m_win_width/2;
    raylib::Vector2 enemy_pos{m_win_width - (m_player.rect().x + m_player.rect().width), 0.5f*m_win_height};
    m_enemy = EnemyBlock{enemy_pos, line_of_sight};
    m_enemy.set_color(raylib::BLUE);

    // set Ball
    const float ball_radius {0.025f*m_win_height}; 
    raylib::Vector2 ball_vel{8, 8};
    
    m_ball = std::move(Ball{ball_vel, ball_radius});  // we need to move the texture resource. if we copy it, the original will unload the rendertexutre and we can not use it.
    
    float enemy_velocity{}; 

    std::string_view diff_name{};
    switch (difficulty)
    {
    case Difficulty::EASY:
        diff_name      = "Easy Mode!"sv;
        enemy_velocity = 0.0095;
        break;
    case Difficulty::MEDIUM:
        enemy_velocity = 0.01;
        diff_name      = "Medium Mode!"sv;
        break;
    case Difficulty::DIFFICULT:
        diff_name      = "Difficult Mode!"sv;
        enemy_velocity = 0.015;
        break;
    }
    m_enemy.set_velocity(enemy_velocity);
    std::println("{}, vel = {}", diff_name, m_enemy.velocity());
    m_ball.reset_position();

}
void GamePlayScene::update_logic()
{
    // handle player input
    if (raylib::IsKeyDown(raylib::KEY_UP))
    {
        m_player.move_up();
    }
    if (raylib::IsKeyDown(raylib::KEY_DOWN))
    {
        m_player.move_down();
    }

    // update collisions
    m_ball.check_wall_collision();
    m_ball.check_block_collision(m_player);
    m_ball.check_block_collision(m_enemy);


    // update game entitites (enemy position etc)
    m_ball.move();
    m_enemy.move(m_ball);

    // check game status:
    if(m_ball.position().x < 0)
    {
        m_has_won     = false;
        m_is_finished = true;
    }
    if(m_ball.position().x > m_win_width)
    {
        m_has_won     = true;
        m_is_finished = true;
    }
}

void GamePlayScene::draw() const 
{
    raylib::draw([&]
    {
        raylib::ClearBackground(m_background_color);
        m_player.draw();
        m_enemy.draw();
        m_ball.draw();
    });
}
bool GamePlayScene::is_finished() const 
{
    return m_is_finished;
}
auto GamePlayScene::on_exit() -> std::unique_ptr<IGameScene>
{
    raylib::Color ending_bg_color = m_background_color;
    return std::make_unique<EndingScene>(has_won(), ending_bg_color);
}
bool GamePlayScene::has_won() const 
{
    return m_has_won;
}



