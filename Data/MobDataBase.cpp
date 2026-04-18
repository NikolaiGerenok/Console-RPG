#include "MobDatabase.h"
#include <stdexcept>
#include <unordered_map>

namespace {

const std::unordered_map<std::string, MobTamplate> kMobDb = {
    {"goblin",
     MobTamplate{
         "goblin",
         "Goblin",
         25,// maxHP
         10,//attack
         5,//defence
         6, //ap per turn
         10,// heal amount
         0.5f,// heal tresehold
         20,// exp reward
     }},
    {"orc",
     MobTamplate{
         "orc",
         "Orc",
         30, 6, 4, 5, 6, 0.4f, 40,
     }},
};

} // namespace

const MobTamplate& GetMobTemplateById(const std::string& id) {
    const auto it = kMobDb.find(id);
    if (it == kMobDb.end()) {
        throw std::runtime_error("Unknown mob id: " + id);
    }
    return it->second;
}
