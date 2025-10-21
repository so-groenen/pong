cmake_minimum_required(VERSION 3.10.0)
project(Pong VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Pong src/menu_scene.cpp
                    src/game_scene.cpp
                    src/ending_scene.cpp
                    src/game.cpp
                    src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features   (${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries     (${PROJECT_NAME} PRIVATE raylib)
target_link_libraries     (${PROJECT_NAME} PRIVATE stdc++exp)
target_compile_options    (${PROJECT_NAME} PRIVATE -Wall)

