// WorldMap.cpp
// this file contains the implementation of the WorldMap class

#include "WorldMap.h"
#include <iostream>

int WorldMap::getSize() const{
    return m_size;
   }

   bool WorldMap::IsInside(int x, int y) const{
     return x >= 0 && x < m_map.size() && y >=0 && y < m_map.size();
   }

   std::optional<TileType> WorldMap::getTile(int x, int y) const{
    if(IsInside(x,y)){
         return m_map[y][x];
        }
        return std::nullopt; // if the tile is not inside the map
    }

    void WorldMap::Print(int playerX,int playerY){

    for(int y = 0; y < m_size; y++){
        for(int x = 0; x < m_size; x++){
            if(x == playerX && y == playerY){
                std::cout << "P";
            }else{
                std::cout << "#";
            }
        }
        std::cout << std::endl; // print a new line after each row
    }
}

void WorldMap::setTile(int x, int y, TileType tile) {
    if (IsInside(x, y)) {
        m_map[y][x] = tile;
    }
}



WorldMap::WorldMap() 
      : m_size(2)
      , m_map(m_size, std::vector<TileType>(m_size, TileType::Floor)) {}

       
    



       