#include <iostream>
#include "GameState.hpp"
#include "Enums.hpp"

int main() {
    GameState root = GameState(TurnEnum::PLAYER, 2, 1);
    const auto& result = root.ExpectedValues();
    for(const auto& entry : result){
        std::cout << "Action " << (entry.first == SHOOT_SELF ? "SHOOT SELF" : "SHOOT OTHER") << ": " << entry.second << "\n";
    }
    std::cout << std::endl;
    return 0;
}
