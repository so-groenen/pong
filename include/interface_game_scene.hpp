#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP
#include <memory>

enum class Scenes
{
    Menu,
    Game,
    End,
};

class IGameScene
{
public:
    virtual void draw() const = 0;
    virtual void update_logic() = 0;
    virtual auto on_exit() -> std::unique_ptr<IGameScene> = 0;
    virtual bool is_finished() const = 0;
};

 


#endif