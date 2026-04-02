#include "BattleSystem.h"


BattleSystem::BattleSystem ():  m_ApOnTurn(6),
                              playerTurn(true),
                              m_battleMapSize(2),
                              m_battleMap (std::vector<std::vector<TileType>>{{TileType::Floor,TileType::Floor}, 
                                                                              {TileType::Floor,TileType::Floor}}),
                              m_battlePlayerX(0),
                              m_battlePlayerY(0),
                              m_unitX(1),
                              m_unitY(1) {}
        
        void BattleSystem::BattleSystemRun(Player& player,Unit& enemy){
        if(RandomNumber() <= 10)
        {
            plaerTurn = false;
        }
        
        PrintBattle();

        while(player.IsAlive() && enemy.UnitIsAlive())
        {
           

        }
    
}




int BattleSystem::RandomNumber(){
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(1,20);
int random_number = dist(gen);
return random_number;
}



void BattleSystem::PrintBattle(int playerX,int playerY, int unitX,  int unitY){

    for(int y = 0; y < m_battleMapSize; y++)
    {
        for(int x = 0; x < m_battleMapSize; x++)
        {
            if(x == playerX && y == playerY)
            {
                std::cout << "P";
            }else if(x == unitX && y == unitY)
            {
                std::cout << "E";
            }else
            {
        switch(m_battleMap[y][x]){
        
            case TileType::Floor :
        std::cout << "#";
        break;
            case TileType::Fire  :
        std::cout << "F";
        break;
            case TileType::Water :
        std::cout << "W";
        break;
        default:
        std::cout << "invalid tile";
                break;


            }
                
        }
        std::cout << std::endl; 
      }
        
   }
   
}
