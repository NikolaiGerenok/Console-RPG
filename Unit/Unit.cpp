#include "Unit.h"

Unit::Unit() 
             : m_UnitHP(25)
             , m_MaxUnitHP(25)
             , m_UnitDamage(1)
             , m_UnitIsAlive(true)
             , m_UnitDefence(5){}

int Unit::getUnitHP() const{
    return m_UnitHP;
}

int Unit::getUnitAttack() const{
    return m_UnitDamage;
}

int Unit::getUnitMaxHP() const{
    return m_MaxUnitHP;
}

int Unit::getUnitDefence() const{
    return m_UnitDefence;
}

bool Unit::UnitIsAlive() const {
    return m_UnitIsAlive;
}

bool Unit::UnitIsDead() const {
    return !m_UnitIsAlive;
}

void Unit::UnitTakeDamage (int amount){
    if(amount > 0 && UnitIsAlive()){
        m_UnitHP -= amount;
        if(m_UnitHP < 0){
            m_UnitHP = 0;
        }
        if(m_UnitHP == 0){
            m_UnitIsAlive = false;
        }
    }
}