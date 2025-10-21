cmake_minimum_required(VERSION 3.10.0)
project(Pong VERSION 0.1.0 LANGUAGES C CXX)

option(PLATFORM "Desktop")

add_executable(Pong src/menu_scene.cpp
                    src/game_scene.cpp
                    src/ending_scene.cpp
                    src/game.cpp
                    src/main.cpp)


find_package(raylib QUIET)
if(raylib_FOUND)
    message("Raylib found.")
else()
    message("Raylib not found, fetching from github")
    include(FetchContent)
    set(RAYLIB_VERSION 5.0)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
        FIND_PACKAGE_ARGS
    )
    FetchContent_MakeAvailable(raylib)
endif()



target_include_directories(Pong PRIVATE include)
target_compile_features   (Pong PRIVATE cxx_std_23)
target_link_libraries     (Pong PRIVATE raylib)
target_compile_options    (Pong PRIVATE -Wall)

message(STATUS "building for ${PLATFORM}")

if ("${PLATFORM}" STREQUAL "Web")
    target_compile_definitions(Pong PRIVATE PLATFORM_WEB)
    set_target_properties(Pong PROPERTIES SUFFIX ".html") 
    add_custom_command(
        TARGET Pong PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/src/imgui_shell.html $<TARGET_FILE_DIR:Pong> 
    )

    #For github pages:
    add_custom_command(
        TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy  $<TARGET_FILE_DIR:Pong>/Pong.html ${CMAKE_SOURCE_DIR}/docs/index.html
    )
    add_custom_command(
        TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:Pong>/Pong.js  ${CMAKE_SOURCE_DIR}/docs/Pong.js
    )
    add_custom_command(
        TARGET Pong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:Pong>/Pong.wasm ${CMAKE_SOURCE_DIR}/docs/Pong.wasm
    )
 
    target_link_options(Pong PRIVATE
                        -sUSE_GLFW=3
                        -sALLOW_MEMORY_GROWTH
                        -sASSERTIONS=1
                        -sWASM=1
                        -sASYNCIFY
                        -sGL_ENABLE_GET_PROC_ADDRESS=1
                        --shell-file imgui_shell.html)
else()
    target_link_libraries(Pong PRIVATE stdc++exp)
endif()