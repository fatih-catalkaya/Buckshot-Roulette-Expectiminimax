cmake_minimum_required(VERSION 3.27)
project(buckshot_roulette_expectiminmax)

set(CMAKE_CXX_STANDARD 17)

add_executable(buckshot_roulette_expectiminmax main.cpp
        GameState.cpp
        GameState.hpp
        Enums.hpp
)
