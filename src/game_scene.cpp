#include "game_scene.hpp"
#include "ending_scene.hpp"
 
GamePlayScene::GamePlayScene(raylib::Color bg_color, Difficulty difficulty)
:  m_backgroundColor{bg_color}, m_difficulty{difficulty}
{
    if(!raylib::IsWindowReady())
    {
        throw std::runtime_error("Game creation error: Window not ready!\n");
    }

    m_win_width  = toFloat(raylib::GetScreenWidth());
    m_win_height = toFloat(raylib::GetScreenHeight());

    // set player block
    raylib::Vector2 PlayerPosition{0.05f*m_win_width, 0.5f*m_win_height};
    player = Block{PlayerPosition};
    player.setColor(raylib::VIOLET);

    // Set enemy block
    float LineOfSight = m_win_width/2;
    raylib::Vector2 EnemyPosition{m_win_width - (player.getRect().x + player.getRect().width), 0.5f*m_win_height};
    enemy = EnemyBlock{EnemyPosition, LineOfSight};
    enemy.setColor(raylib::BLUE);

    // set Ball
    const float ballRadius = 0.025f*m_win_height; 

    ball = std::move(Ball{ballRadius});  // we need to move the texture resource. if we copy it, the original will unload the rendertexutre and we can not use it.
    ball.setVelocity(raylib::Vector2{8, 8}); //use random number generator to randomize orientation.

    switch (difficulty)
    {
    case Difficulty::EASY:
        difficultyName = "Easy Mode!";
        enemy.setVelocity(0.0095);
        break;
    case Difficulty::MEDIUM:
        difficultyName = "Medium Mode!";
        enemy.setVelocity(0.01);
        break;
    case Difficulty::DIFFICULT:
        difficultyName = "Difficult Mode!";
        enemy.setVelocity(0.015);
        break;
    }
    ball.resetPosition();

}
void GamePlayScene::update_logic()
{
    // add a switch-case to change the velocity of enemy block depending on level EASY/MEDIUM/DIFFICULT.
        // handle player input
    if (raylib::IsKeyDown(raylib::KEY_UP))
    {
        player.moveUp();
    }
    if (raylib::IsKeyDown(raylib::KEY_DOWN))
    {
        player.moveDown();
    }

    // update collisions
    ball.checkWallCollision();
    ball.checkBlockCollision(player);
    ball.checkBlockCollision(enemy);


    // update game entitites (enemy position etc)
    ball.move();
    enemy.move(ball);

            // check game status:
    if(ball.getPos().x < 0)
    {
        m_has_won = false;
        m_is_finished = true;
    }
    if(ball.getPos().x > m_win_width)
    {
        m_has_won = true;
        m_is_finished = true;
    }
}

void GamePlayScene::draw() const 
{
    raylib::draw([&]
    {
        raylib::ClearBackground(m_backgroundColor);
        // raylib::DrawText(difficultyName.c_str(), 0.5*m_win_width, 0.1*m_win_height, 20, raylib::BLACK);
        player.draw();
        enemy.draw();
        ball.draw();
    });
    // raylib::BeginDrawing();
    //     raylib::ClearBackground(m_backgroundColor);
    //     // raylib::DrawText(difficultyName.c_str(), 0.5*m_win_width, 0.1*m_win_height, 20, raylib::BLACK);
    //     player.draw();
    //     enemy.draw();
    //     ball.draw();
    // raylib::EndDrawing();
}
bool GamePlayScene::is_finished() const 
{
    return m_is_finished;
}
auto GamePlayScene::on_exit() -> std::unique_ptr<IGameScene>
{
    raylib::Color ending_bg_color = m_backgroundColor;
    return std::make_unique<EndingScene>(has_won(), ending_bg_color);
    // return std::make_unique<MenuScene>(ending_bg_color);
}
bool GamePlayScene::has_won() const 
{
    return m_has_won;
}



