#pragma once

#include <map>
#include <optional>
#include <string>

class BattleTrigerReader {
public:
    struct BattleTriger {
        int x{};
        int y{};
        std::string battleMap;
    };

    BattleTrigerReader();
    ~BattleTrigerReader() = default;

    void ReadTrigerFromFile(const std::string& path);
    std::optional<std::string> findKey(int x, int y) const;

private:
    void stripCarriageReturn(std::string& line);

    std::map<std::pair<int, int>, std::string> m_battleTriggers;
};
