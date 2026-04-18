#pragma once

class Player {
public:
    Player();
    ~Player() = default;

    int getHP() const;
    int getMaxHP() const;
    int getLevel() const;
    int getAttack() const;
    int getDefence() const;
    int getExpToNextLevel() const;
    bool isAlive() const;
    bool isDead() const;
    void takeDamage(int amount);
    void addExperience(int amount);
    void resetToInitialState();
    void addDamage(int amount);
   

private:
    void applyLevelUp();

    int m_playerHP;
    int m_maxPlayerHP;
    int m_playerDamage;
    int m_playerDefence;
    int m_playerLVL;
    int m_totalEXP;
    bool m_isAlive;
};
