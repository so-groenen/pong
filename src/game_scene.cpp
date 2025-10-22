#include "game_scene.hpp"
#include "ending_scene.hpp"
#include <print>

using namespace std::literals::string_view_literals;
 
constexpr float MIN_ANGLE {-PI/3.f}; 
constexpr float MAX_ANGLE {+PI/3.f};
void randomize_dir(raylib::Vector2& vec)
{
    float r{sqrtf(vec.x*vec.x + vec.y*vec.y)};

    int rand_sgn   = 1 - 2*raylib::GetRandomValue(0,1);
    auto theta     = raylib::GetRandomValue(to_int(MIN_ANGLE), to_int(MAX_ANGLE));
    vec.x          = rand_sgn*r*cosf(to_float(theta));
    vec.y          = r*sinf(to_float(theta));
}

raylib::Vector2 get_rand_vec(float magnitude)
{
    raylib::Vector2 vec{magnitude, 0};
    randomize_dir(vec);
    return vec;
}



GamePlayScene::GamePlayScene(Difficulty difficulty)
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
    m_player.set_velocity(1.f*m_win_height);

    // Set enemy block
    raylib::Vector2 enemy_pos{m_win_width - (m_player.rect().x + m_player.rect().width), 0.5f*m_win_height};
    m_enemy = EnemyBlock{enemy_pos};
    m_enemy.set_color(raylib::BLUE);


    // set Ball
    const int ball_radius {to_int(0.025f*m_win_height)}; // Ball texture size is in int, therefor having "integer valued" floats makes life easier
    m_ball = Ball{raylib::WHITE, to_float(ball_radius)};  // we need to move the texture resource. if we copy it, the original will unload the rendertexutre and we can not use it.

 
    // set ball & enemy velocities depending on difficulty!
    raylib::Vector2 easy_ball_vel = get_rand_vec(0.5*m_win_width);

    float enemy_velocity{}; 
    float line_of_sight{};
    raylib::Vector2 ball_velocity{};
    std::string_view diff_name{};
    switch (difficulty)
    {
    case Difficulty::Easy:
        diff_name      = "Easy Mode!"sv;
        enemy_velocity = 0.25f * m_win_height;
        ball_velocity  = easy_ball_vel;
        line_of_sight  = m_win_width/4.f;
        break;
    case Difficulty::Medium:
        enemy_velocity = 0.75f * m_win_height;
        diff_name      = "Medium Mode!"sv;
        ball_velocity  =  1.2f * easy_ball_vel;
        line_of_sight  = m_win_width/3.f;
        break;
    case Difficulty::Difficult:
        enemy_velocity = 1.f * m_win_height;
        diff_name      = "Difficult Mode!"sv;
        ball_velocity  = 2.5f * easy_ball_vel;
        line_of_sight  = m_win_width/2.f;
        break;
    }
    m_enemy.set_velocity(enemy_velocity);
    m_enemy.set_line_of_sight(line_of_sight);
    m_ball.set_velocity(ball_velocity);

    std::println("{}, vel = {}", diff_name, enemy_velocity);
}
void GamePlayScene::update_logic(float dt)
{
    // handle player input
    if (raylib::IsKeyDown(raylib::KEY_UP))
    {
        m_player.move_up(dt);
    }
    if (raylib::IsKeyDown(raylib::KEY_DOWN))
    {
        m_player.move_down(dt);
    }
    else
    {
        m_player.stand_still();
    }

    // update collisions
    m_ball.check_wall_collision(dt);
    m_ball.check_block_collision(m_player, dt);
    m_ball.check_block_collision(m_enemy, dt);


    // update game entitites (enemy position etc)
    m_ball.move(dt);
    m_enemy.move(m_ball, dt);

    // check game status:
    if(m_ball.position().x - m_ball.radius() < 0)
    {
        m_has_won     = false;
        m_is_finished = true;
    }
    if(m_ball.position().x +  m_ball.radius() > m_win_width)
    {
        m_has_won     = true;
        m_is_finished = true;
    }
}

void GamePlayScene::draw() const 
{
    m_player.draw();
    m_enemy.draw();
    m_ball.draw();
}
bool GamePlayScene::is_finished() const 
{
    return m_is_finished;
}
auto GamePlayScene::on_exit() -> std::unique_ptr<IGameScene>
{
    return std::make_unique<EndingScene>(has_won());
}
bool GamePlayScene::has_won() const 
{
    return m_has_won;
}



