#pragma once

#include <string>

struct MobTamplate {
    std::string id;
    std::string name;
    int maxHP;
    int attack;
    int defence;
    int apPerTurn;
    int healAmount;
    float healThreshold;
    int expReward;
};
