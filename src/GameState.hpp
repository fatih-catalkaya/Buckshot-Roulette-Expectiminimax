#pragma once
#include "Enums.hpp"
#include <vector>
#include <unordered_map>
#include <utility>


class GameState {
private:
    [[nodiscard]] GameState NewStateAfterShootAction(Action action, BulletType bulletType) const;

protected:
    TurnEnum playerToAct;
    int totalBullets;
    int liveBullets;
    int numPlayerShot;
    int numDaemonShot;
    [[nodiscard]] std::vector<Action> ComputeAvailableActions() const;
    [[nodiscard]] std::pair<Action, double> ComputeBestAction() const;

public:
    GameState(TurnEnum playerToAct, int totalBullets, int liveBullets, int numPlayerShot, int numDaemonShot);
    [[nodiscard]] std::unordered_map<Action, double> ExpectedValues() const;
};