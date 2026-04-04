#include "BattleSystem.h"
#include <cstdlib>
#include <iostream>

BattleSystem::BattleSystem()
    : m_ApOnTurn(6)
    , playerTurn(true)
    , m_battleMapSize(2)
    , m_battleMap(std::vector<std::vector<TileType>>{
          {TileType::Floor, TileType::Floor},
          {TileType::Floor, TileType::Floor},
      })
    , m_battlePlayerX(0)
    , m_battlePlayerY(0)
    , m_unitX(1)
    , m_unitY(1)
    , m_BattleDX(0)
    , m_BattleDY(0) {}

void BattleSystem::BattleSystemRun(Player& player, Unit& enemy) {
    if (RandomNumber() <= 10) {
        playerTurn = false;
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    BattleDraw( player, enemy);

    while (player.isAlive() && enemy.UnitIsAlive() && m_ApOnTurn > 0) {
        if (playerTurn) {
            std::cout << "Take Action" << std::endl;
            const char action = PlayerTakeAction();
            if (action == '\0') {
                std::exit(0);
            }
            m_ApOnTurn = 6;
            m_BattleDX = 0;
            m_BattleDY = 0;
            switch (action) {
            case 'r':
            case 'R':
                enemy.UnitTakeDamage(player.getAttack());
                m_ApOnTurn -= 2;
                BattleDraw(player,enemy);
                break;
            case 'w':
            case 'W':
                m_BattleDY = -1;
                m_ApOnTurn -= 1;
                TryMovePlayer();
                BattleDraw( player, enemy);
                break;
            case 's':
            case 'S':
                m_BattleDY = 1;
                m_ApOnTurn -= 1;
                TryMovePlayer();
                BattleDraw( player, enemy);
                break;
            case 'a':
            case 'A':
                m_BattleDX = -1;
                m_ApOnTurn -= 1;
                TryMovePlayer();
                BattleDraw( player, enemy);
                break;
            case 'd':
            case 'D':
                m_BattleDX = 1;
                m_ApOnTurn -= 1;
                TryMovePlayer();
                BattleDraw( player, enemy);
                break;
            default:
                std::cout << "invalid imput";
                break;
            }
            playerTurn = false;
        } else {
            player.takeDamage(enemy.getUnitAttack());
            m_ApOnTurn -= 2;
            playerTurn = true;
        }
        
       
    }
}

int BattleSystem::RandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 20);
    int random_number = dist(gen);
    return random_number;
}

void BattleSystem::PrintBattle(int playerX, int playerY, int unitX, int unitY) {
    for (int y = 0; y < m_battleMapSize; y++) {
        for (int x = 0; x < m_battleMapSize; x++) {
            if (x == playerX && y == playerY) {
                std::cout << "P";
            } else if (x == unitX && y == unitY) {
                std::cout << "E";
            } else {
                switch (m_battleMap[y][x]) {
                case TileType::Floor:
                    std::cout << "#";
                    break;
                case TileType::Fire:
                    std::cout << "F";
                    break;
                case TileType::Water:
                    std::cout << "W";
                    break;
                default:
                    std::cout << "invalid tile";
                    break;
                }
            }
        }
        std::cout << std::endl;
    }
}

char BattleSystem::PlayerTakeAction() {
    char ch = 0;
    if (!(std::cin >> ch)) {
        return '\0';
    }
    return ch;
}

bool BattleSystem::IsInsideBattle(int x, int y) const{
    return x >= 0 && x < BattleSize() && y >=0 && y < BattleSize();
  }

int BattleSystem::BattleSize() const{
    return m_battleMapSize;
}

int BattleSystem::TryMovePlayer(){
    const int BattleDX = m_battlePlayerX + m_BattleDX;
    const int BattleDY = m_battlePlayerY + m_BattleDY;
    if (!IsInsideBattle(BattleDX, BattleDY) || BattleDX == m_unitX && BattleDY == m_unitY ) {
        std::cout << "can't move there\n";
        return m_ApOnTurn +=1;
    }

    m_battlePlayerX = BattleDX;
    m_battlePlayerY = BattleDY;
    return 0;
}

void BattleSystem::BattleDraw(Player& player, Unit& enemy){
    #ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

PrintBattle(m_battlePlayerX, m_battlePlayerY, m_unitX, m_unitY);

std::cout << "=======================" << std::endl;
std::cout << "Player HP:" << player.getHP() << "   ";
std::cout << "Enemy HP" << enemy.getUnitHP() << std::endl;
std::cout << "Attack - r" << m_ApOnTurn <<std::endl;

}