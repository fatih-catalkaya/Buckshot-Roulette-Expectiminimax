#include "GameState.hpp"
#include <algorithm>
#include <limits>

GameState::GameState(TurnEnum playerToAct, int totalBullets, int liveBullets, int numPlayerShot, int numDaemonShot)
        : playerToAct(playerToAct),
          totalBullets(totalBullets),
          liveBullets(liveBullets),
          numPlayerShot(numPlayerShot),
          numDaemonShot(numDaemonShot) {}

GameState GameState::NewStateAfterShootAction(Action action, BulletType bulletType) const {
    // This procedure creates the state which follows the current state
    // a given action and a given bullet type, which would be shot
    int newTotalBullets = totalBullets - 1;
    int newLiveBullets = liveBullets - (bulletType == LIVE ? 1 : 0);
    int newNumPlayerShot;
    int newNumDaemonShot;
    TurnEnum newPlayerToAct;
    if (action == SHOOT_SELF && bulletType == BLANK) {
        newPlayerToAct = playerToAct;
    } else {
        newPlayerToAct = playerToAct == PLAYER ? DAEMON : PLAYER;
    }
    return GameState(newPlayerToAct, newTotalBullets, newLiveBullets, numPlayerShot, numDaemonShot);
}

std::pair<Action, double> GameState::ComputeBestAction() const {
    const std::unordered_map<Action, double> expectedValuesMap = this->ExpectedValues();
    Action action;

    // If playerToAct is PLAYER than this node is currently
    // a MAX-node else it is a MIN-node
    double expectedValue =
            playerToAct == PLAYER ? std::numeric_limits<double>::min() : std::numeric_limits<double>::max();

    // Iterate the expectedValuesMap
    for (const auto &entry: expectedValuesMap) {
        if (playerToAct == PLAYER) {
            // If the player to act is PLAYER than we choose
            // the action with the highest expected value
            if (entry.second > expectedValue) {
                action = entry.first;
                expectedValue = entry.second;
            }
        } else {
            // If the player to act is DAEMON than we choose
            // the action with the lowest expected value
            if (entry.second < expectedValue) {
                action = entry.first;
                expectedValue = entry.second;
            }
        }
    }

    return std::make_pair(action, expectedValue);
}

std::vector<Action> GameState::ComputeAvailableActions() const {
    // This function calculates the set of all possible moves
    // for the player whose turn it is at the moment. Currently,
    // there are no items available, therefore, the result of this
    // function is always to shoot yourself or to shoot the opponent
    return std::vector<Action>{SHOOT_SELF, SHOOT_OTHER};
}

std::unordered_map<Action, double> GameState::ExpectedValues() const {
    if (totalBullets == 1) {
        // If there is only one round left in the shotgun,
        // we assume, that both players will play optimal
        // and shoot the opposite player, maximizing
        // the utility value
        bool liveLeft = liveBullets == 1;

        switch (playerToAct) {
            case PLAYER:
                return std::unordered_map<Action, double>{{SHOOT_SELF,  (numDaemonShot - (numPlayerShot + liveLeft))},
                                                          {SHOOT_OTHER, (numDaemonShot + liveLeft - numPlayerShot)}};
            case DAEMON:
                return std::unordered_map<Action, double>{{SHOOT_SELF,  (numPlayerShot - (numDaemonShot + liveLeft))},
                                                          {SHOOT_OTHER, (numPlayerShot + liveLeft - numDaemonShot)}};
        }
    }

    const std::vector<Action> availableActions = ComputeAvailableActions();
    std::unordered_map<Action, double> expectedValuesGivenAction;

    // Compute the probability, that the next bullet in the shotgun chamber is a live one
    const double probLiveBullet = (double) liveBullets / (double) totalBullets;

    for (const auto &action: availableActions) {
        // For each action, we compute the state of the game,
        // assuming, the next bullet is either a live or a blank one
        const GameState liveBullet = this->NewStateAfterShootAction(action, BulletType::LIVE);
        const auto liveBulletBestAction = liveBullet.ComputeBestAction();

        const GameState blankBullet = this->NewStateAfterShootAction(action, BulletType::BLANK);
        const auto blankBulletBestAction = blankBullet.ComputeBestAction();

        // We compute the expected value, of the current action and add it to our map
        expectedValuesGivenAction[action] =
                probLiveBullet * liveBulletBestAction.second + (1 - probLiveBullet) * blankBulletBestAction.second;
    }

    return expectedValuesGivenAction;
}
