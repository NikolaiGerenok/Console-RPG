#include "BattleTrigerReader.h"

#include <fstream>
#include <sstream>

BattleTrigerReader::BattleTrigerReader() = default;

void BattleTrigerReader::ReadTrigerFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        stripCarriageReturn(line);

        if (line.empty()) {
            continue;
        }

        std::istringstream ss(line);
        int x = 0;
        int y = 0;
        char comma = ',';
        std::string battleId;

        ss >> x >> comma >> y >> comma >> battleId;
        if (!ss.fail()) {
            m_battleTriggers[{x, y}] = battleId;
        }
    }
}

void BattleTrigerReader::stripCarriageReturn(std::string& line) {
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
}

std::optional<std::string> BattleTrigerReader::findKey(int x, int y) const {
    const auto it = m_battleTriggers.find({x, y});
    if (it == m_battleTriggers.end()) {
        return std::nullopt;
    }
    return it->second;
}
