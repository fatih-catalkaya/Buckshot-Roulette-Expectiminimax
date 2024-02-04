#include <gtest/gtest.h>
#include "../src/Enums.hpp"
#include "../src/GameState.hpp"

TEST(SimpleTest, BasicAssertion) {
    GameState root = GameState(TurnEnum::PLAYER, 2, 1, 0, 0);
    const auto& result = root.ExpectedValues();
    for(const auto& entry : result){
        EXPECT_EQ(0, entry.second);
    }
}

TEST(SimpleTest2, BasicAssertion) {
    GameState root = GameState(TurnEnum::PLAYER, 3, 1, 0, 0);
    const auto& result = root.ExpectedValues();

    for(const auto& entry : result){
        if(entry.first == Action::SHOOT_OTHER){
            EXPECT_GT(entry.second, 0);
        }
        else{
            EXPECT_LT(entry.second, 0);
        }
    }
}
