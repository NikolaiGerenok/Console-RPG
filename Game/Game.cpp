#include "Game.h"
#include <iostream>
#include "Player.h"



 


void Game::Run(){
    while(true){
        Exploration();   
    }
}

char Game::PlayerInput(){
      char input;
      return std::cin >> input;
}

void Game::Exploration(){
    m_worldMap.Print(m_playerX,m_playerY);
    std::cout << "enter action" << std::endl;
    switch(PlayerInput()){
        case 'w':
        case 'W':
            m_dx = 0; m_dy = -1; break;
        case 's':
        case 'S':
             m_dx = 0; m_dy =  1; break;
        case 'a':
        case 'A':
             m_dx = -1; m_dy = 0; break;
        case 'd': 
        case 'D':
             m_dx =  1; m_dy = 0; break;
        
        default: std::cout << "invalid input" << std::endl; 
    }

   
}

Game::Game() : m_DefaultMap(std::vector<std::vector<int>>{{0,0},{2,1}}),
             m_savePlayerX(0),
             m_savePlayerY(0),
             input(' '),
             m_dy(0),
             m_dx(0){}

