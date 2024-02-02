#pragma once
#include "Enums.hpp"
#include <vector>
#include <unordered_map>
#include <utility>


class GameState {
private:
    GameState ComputeStateGivenActionAndBulletType(Action action, BulletType bulletType) const;

protected:
    TurnEnum playerToAct;
    int totalBullets;
    int liveBullets;
    std::vector<Action> ComputeAvailableActions() const;
    std::pair<Action, double> ComputeBestAction() const;
public:
    GameState(TurnEnum playerToAct, int totalBullets, int liveBullets);
    std::unordered_map<Action, double> ExpectedValues() const;
};