// WorldMap.h
// this file contains the declaration of the WorldMap class

#pragma once 
#include <vector>
#include <optional>
#include "Tile.h"


class WorldMap{
    public:
    WorldMap();

    ~WorldMap() = default; 

    int getSize() const;

    bool IsInside(int x, int y) const;

    std::optional<TileType> getTile(int x, int y) const;

    void Print(int playerX,int playerY);

    void setTile(int x, int y, TileType tile);


    
    private:

    const int m_size;
    std::vector<std::vector<TileType>> m_map;

};