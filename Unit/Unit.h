#pragma once

class Unit{
public:

    Unit();
    ~Unit() = default;

    int getUnitHP() const;
    int getUnitMaxHP() const;
    int getUnitAttack() const;
    int getUnitDefence() const;
    bool UnitIsAlive() const;
    bool UnitIsDead() const;
    void UnitTakeDamage(int amount);

private:

    int m_UnitHP;
    int m_MaxUnitHP;
    int m_UnitDamage;
    int m_UnitDefence;
    bool m_UnitIsAlive;
    
};
