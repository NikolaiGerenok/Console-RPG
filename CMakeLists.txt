cmake_minimum_required(VERSION 3.20)
project(ConsoleRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(console-rpg
    main.cpp
    Game/Game.cpp
    WorldMap/WorldMap.cpp
    Player/Player.cpp
    Unit/Unit.cpp
    BattleSystem/BattleSystem.cpp
    BattleSystem/BattleMapLoader.cpp
    BattleSystem/BattleTrigerReader.cpp
    Data/MobDataBase.cpp
)

target_include_directories(console-rpg PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Data
    ${CMAKE_CURRENT_SOURCE_DIR}/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/WorldMap
    ${CMAKE_CURRENT_SOURCE_DIR}/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tile
    ${CMAKE_CURRENT_SOURCE_DIR}/Unit
    ${CMAKE_CURRENT_SOURCE_DIR}/BattleSystem
)

add_custom_command(TARGET console-rpg POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:console-rpg>/data"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/WorldMap/map/map1.txt"
            "$<TARGET_FILE_DIR:console-rpg>/data/map1.txt"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/WorldMap/battlemap/battlemap1.txt"
            "$<TARGET_FILE_DIR:console-rpg>/data/battlemap1.txt"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/WorldMap/battlemap/battlemap2.txt"
            "$<TARGET_FILE_DIR:console-rpg>/data/battlemap2.txt"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/WorldMap/battlemap/battlemap3.txt"
            "$<TARGET_FILE_DIR:console-rpg>/data/battlemap3.txt"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/WorldMap/battletriger/DataBattleTriger.txt"
            "$<TARGET_FILE_DIR:console-rpg>/data/DataBattleTriger.txt"
)
