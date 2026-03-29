#include "Player.h"

Player::Player() : 
                m_maxPlayerHP(30),
                m_playerHP(30),
                m_playerDamage(10),
                m_playerLVL(1),
                m_isAlive(true),
                m_totalEXP(0),
                m_playerDefence(5){}


int Player::getHP() const {
    return m_playerHP;
}

int Player::getAttack() const {
    return m_playerDamage;
}

int Player::getDefence() const {
    return m_playerDefence;
}

int Player::getLevel() const {
    return m_playerLVL;
}

int Player::getMaxHP() const {
    return m_maxPlayerHP;
}


 bool Player::isAlive() const {
    return m_isAlive;
}

bool Player::isDead() const {
    return !m_isAlive;
}

void  Player::takeDamage(int amount){
    if( amount > 0 && isAlive())
    {
   
    m_playerHP -= amount;
    if(m_playerHP < 0){
        m_playerHP = 0;
    }
    if( m_playerHP == 0){
        m_isAlive = false;
    }
  }
}

void  Player::addExperience(int amount){
    if(amount <= 0 ){
        return;
    }
    m_totalEXP += amount;

    while(m_totalEXP > 100*m_playerLVL){
        m_playerLVL++;
        m_maxPlayerHP += 5;
        m_playerHP += 5;
        m_playerDamage += 5;
    }
  
  }  

  int Player::getExpToNextLevel() const {
     return 100*m_playerLVL - m_totalEXP;
  }


