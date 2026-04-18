#include "BattleSystem.h"
#include "Config/BattleBalance.h"
#include <cstdlib>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>

namespace {
constexpr size_t kIgnoreNoEnemy = static_cast<size_t>(-1);
}

void BattleSystem::enemyAct(Player& player, size_t enemyIndex) {
    if (enemyIndex >= m_enemies.size()) {
        return;
    }
    Unit& enemy = m_enemies[enemyIndex].unit;
    int& m_unitX = m_enemies[enemyIndex].x;
    int& m_unitY = m_enemies[enemyIndex].y;

    const int adx = std::abs(m_battlePlayerX - m_unitX);
    const int ady = std::abs(m_battlePlayerY - m_unitY);

    if (adx + ady == 1) {
        if (m_UnitApOnTurn >= battle::kAttackApCost) {
            player.takeDamage(enemy.getUnitAttack());
            m_UnitApOnTurn -= battle::kAttackApCost;
        }
        return;
    }

    if (m_UnitApOnTurn < battle::kMoveApCost) {
        return;
    }

    m_BattleDX = 0;
    m_BattleDY = 0;
    if (m_battlePlayerX != m_unitX) {
        m_BattleDX = (m_battlePlayerX > m_unitX) ? 1 : -1;
    } else {
        m_BattleDY = (m_battlePlayerY > m_unitY) ? 1 : -1;
    }
    if (TryMoveUnit(enemyIndex)) {
        m_UnitApOnTurn -= battle::kMoveApCost;
    }
    m_BattleDX = 0;
    m_BattleDY = 0;
}

BattleSystem::BattleSystem()
    : m_ApOnTurn(battle::kApPerTurn)
    , playerTurn(true)
    , m_battleWidth(battle::kMapSize)
    , m_battleHeight(battle::kMapSize)
    , m_battlePlayerX(battle::kPlayerStartX)
    , m_battlePlayerY(battle::kPlayerStartY)
    , m_BattleDX(0)
    , m_BattleDY(0)
    , m_HelengFlask(battle::kHealingFlaskCount)
    , m_HalfHP(battle::kHealHpFractionThreshold)
    , m_getTreatment(battle::kHealAmount)
    , m_UnitApOnTurn(battle::kApPerTurn)
    , m_rng(std::random_device{}()) {
    m_battleMap.assign(
        static_cast<size_t>(m_battleHeight),
        std::vector<TileType>(static_cast<size_t>(m_battleWidth), TileType::Floor));
}

void BattleSystem::resetBattleState() {
    m_battleWidth = battle::kMapSize;
    m_battleHeight = battle::kMapSize;
    m_battlePlayerX = battle::kPlayerStartX;
    m_battlePlayerY = battle::kPlayerStartY;
    m_enemies.clear();
    m_BattleDX = 0;
    m_BattleDY = 0;
    m_HelengFlask = battle::kHealingFlaskCount;
    m_ApOnTurn = battle::kApPerTurn;
    m_UnitApOnTurn = battle::kApPerTurn;
    playerTurn = true;
    m_battleMap.assign(static_cast<size_t>(m_battleHeight),std::vector<TileType>(static_cast<size_t>(m_battleWidth), TileType::Floor));}

bool BattleSystem::anyEnemyAlive() const {
    for (const auto& e : m_enemies) {
        if (e.unit.UnitIsAlive()) {
            return true;
        }
    }
    return false;
}

int BattleSystem::findAdjacentLivingEnemyIndex() const {
    for (size_t i = 0; i < m_enemies.size(); ++i) {
        if (!m_enemies[i].unit.UnitIsAlive()) {
            continue;
        }
        const int dx = std::abs(m_battlePlayerX - m_enemies[i].x);
        const int dy = std::abs(m_battlePlayerY - m_enemies[i].y);
        if (dx + dy == 1) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

bool BattleSystem::cellBlockedByLivingEnemy(int x, int y, size_t ignoreEnemyIndex) const {
    for (size_t i = 0; i < m_enemies.size(); ++i) {
        if (i == ignoreEnemyIndex) {
            continue;
        }
        if (!m_enemies[i].unit.UnitIsAlive()) {
            continue;
        }
        if (m_enemies[i].x == x && m_enemies[i].y == y) {
            return true;
        }
    }
    return false;
}

void BattleSystem::applyBattleFromLoader(const BattleMapLoader& battle) {
    m_battleWidth = battle.getWidth();
    m_battleHeight = battle.getHeight();
    m_battleMap = battle.getMap();
    m_enemies = battle.getEnemies();

    m_battlePlayerX = battle::kPlayerStartX;
    m_battlePlayerY = battle::kPlayerStartY;
    if (!IsInsideBattle(m_battlePlayerX, m_battlePlayerY)) {
        m_battlePlayerX = 0;
        m_battlePlayerY = 0;
    }
   

    m_BattleDX = 0;
    m_BattleDY = 0;
    m_HelengFlask = battle::kHealingFlaskCount;
    m_ApOnTurn = battle::kApPerTurn;
    m_UnitApOnTurn = battle::kApPerTurn;
    playerTurn = true;
}

BattleResult BattleSystem::BattleSystemRun(Player& player, const BattleMapLoader& battle) {
    applyBattleFromLoader(battle);

    if (!anyEnemyAlive()) {
        return BattleResult::Won;
    }

    if (RandomNumber() <= 20) {
        playerTurn = false;
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    BattleDraw(player);

    while (player.isAlive() && anyEnemyAlive()) {
        if (playerTurn) {
            m_ApOnTurn = battle::kApPerTurn;
            while (player.isAlive() && anyEnemyAlive() && m_ApOnTurn > 0) {
                BattleDraw(player);
                std::cout << "R attack, WASD move\n";
                const char action = PlayerTakeAction();
                if (action == '\0') {
                    std::exit(0);
                }
                m_BattleDX = 0;
                m_BattleDY = 0;
                switch (action) {
                case 'r':
                case 'R': {
                    const int idx = findAdjacentLivingEnemyIndex();
                    if (idx >= 0) {
                        if (m_ApOnTurn >= battle::kAttackApCost) {
                            m_enemies[static_cast<size_t>(idx)].unit.UnitTakeDamage(player.getAttack());
                            m_ApOnTurn -= battle::kAttackApCost;
                        } else {
                            std::cout << "not enough AP to attack\n";
                        }
                    } else {
                        std::cout << "so far, move\n";
                    }
                } break;
                case 'w':
                case 'W':
                    m_BattleDY = -1;
                    m_ApOnTurn -= battle::kMoveApCost;
                    TryMovePlayer();
                    break;
                case 's':
                case 'S':
                    m_BattleDY = 1;
                    m_ApOnTurn -= battle::kMoveApCost;
                    TryMovePlayer();
                    break;
                case 'a':
                case 'A':
                    m_BattleDX = -1;
                    m_ApOnTurn -= battle::kMoveApCost;
                    TryMovePlayer();
                    break;
                case 'd':
                case 'D':
                    m_BattleDX = 1;
                    m_ApOnTurn -= battle::kMoveApCost;
                    TryMovePlayer();
                    break;
                default:
                    std::cout << "invalid imput\n";
                    break;
                }
            }
            playerTurn = false;
        } else {
            for (size_t e = 0; e < m_enemies.size(); ++e) {
                if (!player.isAlive() || !anyEnemyAlive()) {
                    break;
                }
                if (!m_enemies[e].unit.UnitIsAlive()) {
                    continue;
                }
                m_HelengFlask = battle::kHealingFlaskCount;
                m_UnitApOnTurn = m_enemies[e].unit.getUnitApPerTurn();
                while (player.isAlive() && m_enemies[e].unit.UnitIsAlive() && m_UnitApOnTurn > 0) {
                    BattleDraw(player);
                    WaitAnimation(battle::kDelayAction);
                    const int apBefore = m_UnitApOnTurn;
                    const float healFrac = m_enemies[e].unit.getUnitHealThreshold();
                    const bool wantsHeal =
                        m_enemies[e].unit.getUnitHP()
                            < m_enemies[e].unit.getUnitMaxHP() * healFrac
                        && m_HelengFlask > 0;
                    if (wantsHeal && m_UnitApOnTurn >= battle::kEnemyHealApCost) {
                        m_enemies[e].unit.getHeal(m_getTreatment);
                        m_HelengFlask -= 1;
                        m_UnitApOnTurn -= battle::kEnemyHealApCost;
                        WaitAnimation(battle::kDelayAction);
                    } else {
                        enemyAct(player, e);
                        WaitAnimation(battle::kDelayAction);
                    }
                    if (m_UnitApOnTurn == apBefore) {
                        break;
                    }
                }
            }
            playerTurn = true;
        }
    }
    BattleDraw(player);

    if (!player.isAlive()) {
        return BattleResult::Defeat;
    }
    return BattleResult::Won;
}

int BattleSystem::RandomNumber() {
    std::uniform_int_distribution<int> dist(1, 20);
    return dist(m_rng);
}

void BattleSystem::PrintBattle() {
    for (int y = 0; y < m_battleHeight; y++) {
        for (int x = 0; x < m_battleWidth; x++) {
            if (x == m_battlePlayerX && y == m_battlePlayerY) {
                std::cout << "P";
            } else {
                bool printedEnemy = false;
                for (const auto& sp : m_enemies) {
                    if (sp.unit.UnitIsAlive() && sp.x == x && sp.y == y) {
                        std::cout << "E";
                        printedEnemy = true;
                        break;
                    }
                }
                if (printedEnemy) {
                    continue;
                }
                switch (m_battleMap[static_cast<size_t>(y)][static_cast<size_t>(x)]) {
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
                    std::cout << "?";
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

bool BattleSystem::IsInsideBattle(int x, int y) const {
    return x >= 0 && x < m_battleWidth && y >= 0 && y < m_battleHeight;
}

int BattleSystem::TryMovePlayer() {
    const int BattleDX = m_battlePlayerX + m_BattleDX;
    const int BattleDY = m_battlePlayerY + m_BattleDY;
    if (!IsInsideBattle(BattleDX, BattleDY)
        || cellBlockedByLivingEnemy(BattleDX, BattleDY, kIgnoreNoEnemy)) {
        std::cout << "can't move there\n";
        m_ApOnTurn += battle::kMoveApCost;
        return 0;
    }

    m_battlePlayerX = BattleDX;
    m_battlePlayerY = BattleDY;
    return 0;
}

void BattleSystem::BattleDraw(Player& player) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    PrintBattle();

    std::cout << "=======================" << std::endl;
    std::cout << "Player HP:" << player.getHP() << "   ";
    int alive = 0;
    for (const auto& sp : m_enemies) {
        if (sp.unit.UnitIsAlive()) {
            ++alive;
        }
    }
    std::cout << "Enemies alive:" << alive << std::endl;
    for (size_t i = 0; i < m_enemies.size(); ++i) {
        if (!m_enemies[i].unit.UnitIsAlive()) {
            continue;
        }
        std::cout << "  [" << i << "] " << m_enemies[i].x << "," << m_enemies[i].y << " HP:"
                  << m_enemies[i].unit.getUnitHP() << std::endl;
    }
    std::cout << "Attack - r"
              << "   "
              << "AP:" << m_ApOnTurn << "  "
              << "EnemyAP:" << m_UnitApOnTurn << std::endl;
}

bool BattleSystem::TryMoveUnit(size_t enemyIndex) {
    if (enemyIndex >= m_enemies.size()) {
        return false;
    }
    int& m_unitX = m_enemies[enemyIndex].x;
    int& m_unitY = m_enemies[enemyIndex].y;
    const int nx = m_unitX + m_BattleDX;
    const int ny = m_unitY + m_BattleDY;
    if (!IsInsideBattle(nx, ny) || (nx == m_battlePlayerX && ny == m_battlePlayerY)
        || cellBlockedByLivingEnemy(nx, ny, enemyIndex)) {
        return false;
    }
    m_unitX = nx;
    m_unitY = ny;
    return true;
}

void BattleSystem::WaitAnimation(float amount) {
    std::cout << std::flush;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(static_cast<int>(amount * 1000.f)));
}
