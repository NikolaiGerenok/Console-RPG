cmake_minimum_required(VERSION 3.20)
project(ConsoleRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(console-rpg
    main.cpp
    Game/Game.cpp
    WorldMap/WorldMap.cpp
    Player/Player.cpp
)

target_include_directories(console-rpg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldMap
    ${CMAKE_CURRENT_SOURCE_DIR}/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tile
)
