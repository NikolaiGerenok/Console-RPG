#pragma once


namespace battle {

inline constexpr int kApPerTurn = 6;
inline constexpr int kAttackApCost = 2;
inline constexpr int kMoveApCost = 1;
inline constexpr int kEnemyHealApCost = 2;
inline constexpr int kMapSize = 5;
inline constexpr int kPlayerStartX = 0;
inline constexpr int kPlayerStartY = 0;
inline constexpr int kEnemyStartX = 1;
inline constexpr int kEnemyStartY = 1;
inline constexpr int kHealingFlaskCount = 2;
inline constexpr float kHealHpFractionThreshold = 0.5f;
inline constexpr int kHealAmount = 15;
inline constexpr int kTurnOrderRollMin = 1;
inline constexpr int kTurnOrderRollMax = 20;
inline constexpr int kEnemyFirstMax = 10;
inline constexpr float kDelayAction = 0.3f;

} 
