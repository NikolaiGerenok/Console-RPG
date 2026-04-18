#pragma once
#include "BattleSystem.h"
#include "BattleTrigerReader.h"
#include "Player.h"
#include "WorldMap.h"
#include <vector>

class Game {
 public:

    Game();
   
    ~Game() = default;

    void Run();
    void Exploration();
    char PlayerInput();
    void startBattle();
    void giveTreasure();
    void applyDefaultMap();
    void restartSession();
    void showDefeatMenu();
    void DrawUI(Player& player);

 private:
    WorldMap m_worldMap;
    BattleTrigerReader m_battleTriggers;
    Player m_player;
    BattleSystem m_battleSystem;
    int m_playerX;
    int m_playerY;
    int m_savePlayerX;
    int m_savePlayerY;
    char input;
    int m_dy;
    int m_dx;
    



};