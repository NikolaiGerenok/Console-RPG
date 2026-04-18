#pragma once
#include "BattleMapLoader.h"
#include "BattleResult.h"
#include "Player.h"
#include "Unit.h"
#include "Tile.h"
#include <random>
#include <vector>

class BattleSystem {
public:
    BattleSystem();
    ~BattleSystem() = default;

    /** Карта и враги берутся из уже загруженного `BattleMapLoader`. */
    BattleResult BattleSystemRun(Player& player, const BattleMapLoader& battle);

    void resetBattleState();
    int RandomNumber();
    void PrintBattle();
    char PlayerTakeAction();
    int battleWidth() const { return m_battleWidth; }
    int battleHeight() const { return m_battleHeight; }
    bool IsInsideBattle(int x, int y) const;
    int TryMovePlayer();
    void BattleDraw(Player& player);
    bool TryMoveUnit(size_t enemyIndex);
    void WaitAnimation(float amount);

private:
    void applyBattleFromLoader(const BattleMapLoader& battle);
    bool anyEnemyAlive() const;
    /** -1 если рядом никого */
    int findAdjacentLivingEnemyIndex() const;
    bool cellBlockedByLivingEnemy(int x, int y, size_t ignoreEnemyIndex) const;

    void enemyAct(Player& player, size_t enemyIndex);

    int m_ApOnTurn;
    int m_UnitApOnTurn;
    bool playerTurn;
    std::vector<std::vector<TileType>> m_battleMap;
    int m_battleWidth;
    int m_battleHeight;
    int m_battlePlayerX;
    int m_battlePlayerY;
    std::vector<BattleMapLoader::EnemySpawn> m_enemies;
    int m_BattleDX;
    int m_BattleDY;
    int m_HelengFlask;
    const float m_HalfHP;
    const int m_getTreatment;
    std::mt19937 m_rng;
};
