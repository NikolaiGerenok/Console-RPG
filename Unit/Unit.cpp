#include "Unit.h"

Unit::Unit() 
             : m_UnitHP(25)
             , m_MaxUnitHP(25)
             , m_UnitDamage(1)
             , m_UnitIsAlive(true)
             , m_UnitDefence(5)
             , m_ApPerTurn(6)
             , m_expReward(10)
             , m_healAmount(10)
             , m_healThreshold(0.5f)
             , m_mobID("   ")
             , m_mobName("  "){}


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

int Unit::getUnitApPerTurn() const {
    return m_ApPerTurn;
}

int Unit::getUnitExpReward() const {
    return m_expReward;
}

float Unit::getUnitHealThreshold() const {
    return m_healThreshold;
}

void Unit::setApOnTurn(int value){
    m_ApPerTurn = value;
}

void Unit::setUnitMaxHP(int value){
    m_MaxUnitHP = value;
}

void Unit::setUnitAttack(int value){
    m_UnitDamage = value;
}

void Unit::setDefence(int value){
    m_UnitDefence = value;
}

void Unit::setExpReward(int value){
    m_expReward = value;
}

void Unit::setUnitHealAmount(int value){
    m_healAmount = value;
}

void Unit::setUnitID(std::string text){
    m_mobID = text;
}

void Unit::setUnitName(std::string text){
    m_mobName = text;
}

void Unit::setUnitThreshold(float value){
    m_healThreshold = value;
}


bool Unit::UnitIsAlive() const {
    return m_UnitIsAlive;
}

bool Unit::UnitIsDead() const {
    return !m_UnitIsAlive;
}

int Unit::getHeal(int amount){
    return m_UnitHP += amount;
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

Unit Unit::CreateEnemy(const MobTamplate& tpl) {
    Unit u;
    u.setUnitID(tpl.id);
    u.setUnitName(tpl.name);
    u.setUnitMaxHP(tpl.maxHP);
    u.m_UnitHP = tpl.maxHP;
    u.setUnitAttack(tpl.attack);
    u.setDefence(tpl.defence);
    u.setApOnTurn(tpl.apPerTurn);
    u.setUnitHealAmount(tpl.healAmount);
    u.setUnitThreshold(tpl.healThreshold);
    u.setExpReward(tpl.expReward);
    u.m_UnitIsAlive = true;
    return u;
}