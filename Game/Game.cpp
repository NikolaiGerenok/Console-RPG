#include "Game.h"
#include "BattleMapLoader.h"
#include "BattleResult.h"
#include "Tile.h"
#include "BattleTrigerReader.h"
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

std::string worldMapFilePath() {
#ifdef _WIN32
    char buf[MAX_PATH]{};
    if (GetModuleFileNameA(nullptr, buf, MAX_PATH) > 0) {
        const std::filesystem::path exe(buf);
        return (exe.parent_path() / "data" / "map1.txt").string();
    }
#endif
    return "data/map1.txt";
}

bool tryLoadWorldMap(WorldMap& wm) {
    if (wm.loadFromFile(worldMapFilePath())) {
        return true;
    }
    return wm.loadFromFile("WorldMap/map/map1.txt");
}

std::string battleTriggerFilePath() {
#ifdef _WIN32
    char buf[MAX_PATH]{};
    if (GetModuleFileNameA(nullptr, buf, MAX_PATH) > 0) {
        const std::filesystem::path exe(buf);
        return (exe.parent_path() / "data" / "DataBattleTriger.txt").string();
    }
#endif
    return "data/DataBattleTriger.txt";
}

void tryLoadBattleTriggers(BattleTrigerReader& reader) {
    reader.ReadTrigerFromFile(battleTriggerFilePath());
    reader.ReadTrigerFromFile("WorldMap/battletriger/DataBattleTriger.txt");
}

std::string battleMapFilePath(const std::string& fileName) {
#ifdef _WIN32
    char buf[MAX_PATH]{};
    if (GetModuleFileNameA(nullptr, buf, MAX_PATH) > 0) {
        const std::filesystem::path exe(buf);
        return (exe.parent_path() / "data" / fileName).string();
    }
#endif
    return "WorldMap/battlemap/" + fileName;
}

bool tryLoadBattleMap(BattleMapLoader& loader, const std::string& fileName) {
    if (loader.LoadBatleFromFile(battleMapFilePath(fileName))) {
        return true;
    }
    const std::string repoPath = "WorldMap/battlemap/" + fileName;
    if (loader.LoadBatleFromFile(repoPath)) {
        return true;
    }
    return loader.LoadBatleFromFile("WorldMap/battlemap/battlemap1.txt");
}

} // namespace

Game::Game()
      : m_playerX(0)
      , m_playerY(0)
      , m_savePlayerX(0)
      , m_savePlayerY(0)
      , input(' ')
      , m_dy(0)
      , m_dx(0) {
    applyDefaultMap();
}

void Game::applyDefaultMap() {
    if (!tryLoadWorldMap(m_worldMap)) {
        std::cerr << "Map load failed (tried exe_dir/data/map1.txt, then WorldMap/map/map1.txt).\n";
    }
    tryLoadBattleTriggers(m_battleTriggers);
}

void Game::restartSession() {
    m_player.resetToInitialState();
    m_playerX = 0;
    m_playerY = 0;
    applyDefaultMap();
}

void Game::showDefeatMenu() {
    std::cout << "Game over. [Q] Quit  [R] Restart\n";
    bool restarted = false;
    do {
        const char choice = PlayerInput();
        if (choice == '\0' || choice == 'q' || choice == 'Q') {
            std::exit(0);
        }
        if (choice == 'r' || choice == 'R') {
            restartSession();
            restarted = true;
        } else {
            std::cout << "Press Q to quit or R to restart.\n";
        }
    } while (!restarted);
}


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

    DrawUI(m_player);
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

    auto tile = m_worldMap.getTile(m_playerX, m_playerY);
    if(!tile){
        return;
    }else{
        switch(*tile){
            case TileType::Floor         :
                break;
            case TileType::Battle        :
                startBattle(); break;
            case TileType::Treasure      :
                giveTreasure();break;
            
            default:
                std::cout<< "invalid tile" << std::endl;
                break;
        }
    }

}

void Game::giveTreasure(){
    std::cout<< "you find new sword" << std::endl;
    m_player.addDamage(5);
    m_worldMap.setTile(m_playerX, m_playerY, TileType::Floor);
    
}


void Game::startBattle() {
    std::string fileName = "battlemap1.txt";
    if (const auto battle = m_battleTriggers.findKey(m_playerX, m_playerY)) {
        fileName = *battle;
    }

    std::cout << "Battle starts!\n";
    BattleMapLoader loader;
    if (!tryLoadBattleMap(loader,fileName)) {
        std::cerr << "Load error\n";
        return;
    }

    const BattleResult result = m_battleSystem.BattleSystemRun(m_player, loader);

    switch (result) {
    case BattleResult::Won:
        std::cout << "You won.\n";
        m_worldMap.setTile(m_playerX, m_playerY, TileType::Floor);
        {
            int totalExp = 0;
            for (const auto& spawn : loader.getEnemies()) {
                totalExp += spawn.unit.getUnitExpReward();
            }
            m_player.addExperience(totalExp);
        }
        break;
    case BattleResult::Defeat:
        std::cout << "You were defeated.\n";
        showDefeatMenu();
        break;
    }
}

void Game::DrawUI(Player& player){
    std::cout << "=======================" << std::endl;
std::cout << "Player HP:" << player.getHP() << "   ";
std::cout << "EXP:" << player.getExpToNextLevel() << std::endl;
std::cout << "LVL:" << player.getLevel() <<std::endl;

}

