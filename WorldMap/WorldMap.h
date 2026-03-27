// WorldMap.h
// this file contains the declaration of the WorldMap class

#pragma once 
#include <vector>

class WorldMap{
    public:
    WorldMap();

    ~WorldMap() = default; // default destructor 

    int getSize() const;

    bool IsInside(int x, int y) const;

    int getTile(int x, int y) const;

    void Print(int playerX,int playerY);


    
    private:
    const int m_size;
    std::vector<std::vector<int>> m_map;

};