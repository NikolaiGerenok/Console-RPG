#include "WorldMap.h"
#include <iostream>
#include <sstream>

WorldMap::WorldMap()
    : m_width(2)
    , m_height(2)
    , m_map(2, std::vector<TileType>(2, TileType::Floor)) {}

int WorldMap::getWidth() const {
    return m_width;
}

int WorldMap::getHeight() const {
    return m_height;
}

int WorldMap::getSize() const {
    return m_width > m_height ? m_width : m_height;
}

bool WorldMap::IsInside(int x, int y) const {
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

std::optional<TileType> WorldMap::getTile(int x, int y) const {
    if (!IsInside(x, y)) {
        return std::nullopt;
    }
    return m_map[static_cast<size_t>(y)][static_cast<size_t>(x)];
}

char WorldMap::tileToChar(TileType t) {
    switch (t) {
    case TileType::Floor:
        return '#';
    case TileType::Treasure:
        return 'T';
    case TileType::Battle:
        return 'B';
    case TileType::BattleCleared:
        return '.';
    case TileType::Water:
        return 'W';
    case TileType::Fire:
        return 'F';
    default:
        return '?';
    }
}

void WorldMap::Print(int playerX, int playerY) {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (x == playerX && y == playerY) {
                std::cout << 'P';
            } else {
                std::cout << tileToChar(m_map[static_cast<size_t>(y)][static_cast<size_t>(x)]);
            }
        }
        std::cout << '\n';
    }
}

void WorldMap::setTile(int x, int y, TileType tile) {
    if (IsInside(x, y)) {
        m_map[static_cast<size_t>(y)][static_cast<size_t>(x)] = tile;
    }
}

bool WorldMap::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Cannot open map: " << path << '\n';
        return false;
    }

    std::string line;
    if (!std::getline(file, line)) {
        return false;
    }

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
        m_height = h;
        m_width = w;
    }

    m_map.assign(static_cast<size_t>(m_height),
                 std::vector<TileType>(static_cast<size_t>(m_width), TileType::Floor));

    for (int y = 0; y < m_height; ++y) {
        if (!std::getline(file, line)) {
            std::cerr << "Map file too short at row " << y << '\n';
            return false;
        }
        std::stringstream ss(line);
        for (int x = 0; x < m_width; ++x) {
            int code = 0;
            ss >> code;
            if (ss.fail()) {
                std::cerr << "Bad tile at " << x << ',' << y << '\n';
                return false;
            }
            if (x + 1 < m_width) {
                ss.ignore();
            }
            m_map[static_cast<size_t>(y)][static_cast<size_t>(x)] = static_cast<TileType>(code);
        }
    }

    return true;
}
