cmake_minimum_required(VERSION 3.27)
project(buckshot_roulette_expectiminmax)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()
IF(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_executable(buckshot_roulette_expectiminmax src/main.cpp
        src/GameState.cpp
        src/GameState.hpp
        src/Enums.hpp
)
