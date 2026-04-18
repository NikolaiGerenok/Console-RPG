#pragma once
#include <string>
#include "MobTample.h"

class Unit{
public:

    Unit();
    ~Unit() = default;

    int getUnitHP() const;
    int getUnitMaxHP() const;
    int getUnitAttack() const;
    int getUnitDefence() const;
    int getUnitApPerTurn() const;
    int getUnitExpReward() const;
    float getUnitHealThreshold() const;
    int getHeal(int amount);

    bool UnitIsAlive() const;
    bool UnitIsDead() const;
    void UnitTakeDamage(int amount);
    

    void setUnitMaxHP(int value);
    void setUnitAttack(int value);
    void setDefence(int value);
    void setApOnTurn(int value);
    void setUnitHealAmount(int value);
    void setUnitThreshold(float value);
    void setExpReward(int value);
    void setUnitName(std::string text);
    void setUnitID(std::string text);

   
    static Unit CreateEnemy(const MobTamplate& tpl);

private:

    int m_UnitHP;
    int m_MaxUnitHP;
    int m_UnitDamage;
    int m_UnitDefence;
    bool m_UnitIsAlive;
    std::string m_mobID;
    std::string m_mobName;
    int m_ApPerTurn;
    int m_healAmount;
    float m_healThreshold;
    int m_expReward;

    
};
