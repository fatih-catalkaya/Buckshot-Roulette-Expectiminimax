cmake_minimum_required(VERSION 3.27)
project(buckshot_roulette_expectiminmax_tests)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(buckshot_roulette_expectiminmax_tests_run SimpleTest.cpp
        ../src/GameState.hpp
        ../src/GameState.cpp
        ../src/Enums.hpp
)
target_link_libraries(buckshot_roulette_expectiminmax_tests_run gtest gtest_main)
