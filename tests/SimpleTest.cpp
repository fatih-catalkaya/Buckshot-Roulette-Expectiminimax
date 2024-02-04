#include <gtest/gtest.h>
#include "../src/Enums.hpp"

TEST(SimpleTest, BasicAssertion) {
    EXPECT_EQ(Action::SHOOT_SELF, 0);
}