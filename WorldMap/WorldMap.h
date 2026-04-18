#pragma once

#include "Tile.h"
#include <fstream>
#include <optional>
#include <string>
#include <vector>

class WorldMap {
public:
    WorldMap();

    int getWidth() const;
    int getHeight() const;
    int getSize() const;

    bool IsInside(int x, int y) const;
    std::optional<TileType> getTile(int x, int y) const;
    void Print(int playerX, int playerY);
    void setTile(int x, int y, TileType tile);

    bool loadFromFile(const std::string& path);

private:
    int m_width;
    int m_height;
    std::vector<std::vector<TileType>> m_map;

    static char tileToChar(TileType t);
};
