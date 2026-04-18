#include "BattleMapLoader.h"
#include "MobDatabase.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {

void stripCarriageReturn(std::string& line) {
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
}

} // namespace

BattleMapLoader::BattleMapLoader()
    : m_battleWidth(2)
    , m_battleHeight(2)
    , m_mapBattle(2, std::vector<TileType>(2, TileType::Floor)) {}

bool BattleMapLoader::LoadBatleFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Cannot open map: " << path << '\n';
        return false;
    }

    std::string line;
    if (!std::getline(file, line)) {
        return false;
    }
    stripCarriageReturn(line);

    {
        std::stringstream head(line);
        char sep = ',';
        int h = 0;
        int w = 0;
        head >> h >> sep >> w;
        if (h <= 0 || w <= 0 || head.fail()) {
            std::cerr << "Bad map header (expected height,width)\n";
            return false;
        }
        m_battleHeight = h;
        m_battleWidth = w;
    }

    m_mapBattle.assign(static_cast<size_t>(m_battleHeight),
                       std::vector<TileType>(static_cast<size_t>(m_battleWidth), TileType::Floor));

    for (int y = 0; y < m_battleHeight; ++y) {
        if (!std::getline(file, line)) {
            std::cerr << "Map file too short at row " << y << '\n';
            return false;
        }
        stripCarriageReturn(line);
        std::stringstream ss(line);
        for (int x = 0; x < m_battleWidth; ++x) {
            int code = 0;
            ss >> code;
            if (ss.fail()) {
                std::cerr << "Bad tile at " << x << ',' << y << '\n';
                return false;
            }
            if (x + 1 < m_battleWidth) {
                ss.ignore();
            }
            m_mapBattle[static_cast<size_t>(y)][static_cast<size_t>(x)] = static_cast<TileType>(code);
        }
    }

    m_enemies.clear();

    while (std::getline(file, line)) {
        stripCarriageReturn(line);
        if (line.empty()) {
            continue;
        }
        if (line == "#MOBS") {
            break;
        }
    }

    if (line != "#MOBS") {
        std::cerr << "Missing #MOBS section\n";
        return false;
    }

    while (std::getline(file, line)) {
        stripCarriageReturn(line);
        if (line.empty()) {
            continue;
        }

        std::istringstream ss(line);
        std::string id;
        int x = 0;
        int y = 0;
        char sep = ',';

        if (!std::getline(ss, id, ',')) {
            std::cerr << "Bad mob line (no id): " << line << '\n';
            continue;
        }
        ss >> x >> sep >> y;

        if (ss.fail()) {
            std::cerr << "Bad mob line: " << line << '\n';
            continue;
        }try {
            const MobTamplate& tpl = GetMobTemplateById(id);
            Unit u = Unit::CreateEnemy(tpl);
            m_enemies.push_back(EnemySpawn{std::move(u), x, y});
        } catch (const std::exception&) {
            std::cerr << "Unknown mob id: " << id << '\n';
            return false;
        }
    }

    return true;
}
