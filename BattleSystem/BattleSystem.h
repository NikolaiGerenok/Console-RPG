#pragma once
#include "Player.h"
#include "Unit.h"
#include <iostream>
#include <random>
#include <vector>
#include "Tile.h"


class BattleSystem {
public:
    BattleSystem();
    ~BattleSystem() = default;

    void giveAP();
    void outComeBattle();
    void BattleSystemRun(Player&, Unit&);
    int RandomNumber();
    void PrintBattle(int playerX, int playerY, int unitX, int unitY);
    char PlayerTakeAction();
    int BattleSize() const;
    bool IsInsideBattle(int x, int y) const;
    int TryMovePlayer();
    void BattleDraw(Player& player, Unit& enemy);

private:
    int m_ApOnTurn;
    bool playerTurn;
    std::vector<std::vector<TileType>> m_battleMap;
    int m_battleMapSize;
    int m_battlePlayerX;
    int m_battlePlayerY;
    int m_unitX;
    int m_unitY;
    int m_BattleDX;
    int m_BattleDY;
};
