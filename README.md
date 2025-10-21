## Pong!

A super basic **Pong** game in Raylib & C++23.<br>
I initially wrote it whilst learning Raylib and C++, I brushed it up a bit state-pattern, that is, 
using virtual classes & unique pointers rather than having different game loops for different scenes:<br>

```c++
void Game::run()
{
    std::unique_ptr<IGameScene> scene = std::make_unique<MenuScene>(BACKGROUND_COLOR);
    while (!raylib::WindowShouldClose())
    {
        scene->update_logic();
        scene->draw();
        if (scene->is_finished())
        {
            std::unique_ptr<IGameScene> current = std::move(scene);
            scene = current->on_exit();
        }
    }
}
```
### TODO:

Try to upload a small WASM demo using emscripten.