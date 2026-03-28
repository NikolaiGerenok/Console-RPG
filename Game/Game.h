#pragma once
#include "WorldMap.h"
#include <vector>

class Game{
 public:

    Game();
   
    ~Game() = default;

    void Run();
    void Exploration();
    void Battle();
    void RestFromInitial();
    char PlayerInput();

 private:
    WorldMap m_worldMap;
    int m_savePlayerX;
    int m_savePlayerY;
    const std::vector<std::vector<int>> m_DefaultMap; 
    char input;
    int m_dy;
    int m_dx;



};