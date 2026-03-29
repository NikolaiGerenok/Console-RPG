#include "Game.h"
#include <cstdlib>
#include <iostream>



 


void Game::Run(){
    while(true){
        Exploration();   
    }
}

char Game::PlayerInput() {
    char ch = 0;
    if (!(std::cin >> ch)) {
        return '\0';
    }
    return ch;
}

void Game::Exploration() {

#ifdef _WIN32
   
    system("cls");
#else
    system("clear");
#endif

    m_worldMap.Print(m_playerX, m_playerY);
  
    std::cout << "WASD = move, Q = quit\n";

    const char cmd = PlayerInput();
    if (cmd == '\0') {
        std::exit(0);
    }

    m_dx = 0;
    m_dy = 0;
    switch (cmd) {
        case 'w':
        case 'W':
            m_dy = -1;
            break;
        case 's':
        case 'S':
            m_dy = 1;
            break;
        case 'a':
        case 'A':
            m_dx = -1;
            break;
        case 'd':
        case 'D':
            m_dx = 1;
            break;
        case 'q':
        case 'Q':
            std::exit(0);
        default:
            std::cout << "invalid input\n";
            return;
    }

    const int nx = m_playerX + m_dx;
    const int ny = m_playerY + m_dy;
    if (!m_worldMap.IsInside(nx, ny)) {
        std::cout << "can't move there\n";
        return;
    }

    m_playerX = nx;
    m_playerY = ny;
}

Game::Game()
    : m_playerX(0),
      m_playerY(0),
      m_savePlayerX(0),
      m_savePlayerY(0),
      m_DefaultMap(std::vector<std::vector<int>>{{0, 0}, {2, 1}}),
      input(' '),
      m_dy(0),
      m_dx(0) {}

