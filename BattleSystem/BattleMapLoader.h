#pragma once
#include <string>
#include <vector>
#include "Tile.h"
#include "Unit.h"

class BattleMapLoader {
public:
    struct EnemySpawn {
        Unit unit;
        int x{};
        int y{};
    };

    BattleMapLoader();
    ~BattleMapLoader() = default;

    bool LoadBatleFromFile(const std::string& path);

    int getWidth() const { return m_battleWidth; }
    int getHeight() const { return m_battleHeight; }
    const std::vector<std::vector<TileType>>& getMap() const { return m_mapBattle; }
    const std::vector<EnemySpawn>& getEnemies() const { return m_enemies; }

private:
    int m_battleWidth;
    int m_battleHeight;
    std::vector<std::vector<TileType>> m_mapBattle;
    std::vector<EnemySpawn> m_enemies;
};
