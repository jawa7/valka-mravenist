cmake_minimum_required(VERSION 3.20)

project(valka_mravenist VERSION 0.1.0 LANGUAGES CXX)

include(CTest)

add_library(map STATIC
    src/map/GrassTerrain.cpp
    src/map/RockTerrain.cpp
    src/map/Tile.cpp
    src/map/GameBoard.cpp
    src/map/TestMapFactory.cpp
)
target_include_directories(map PUBLIC src/map)
target_compile_features(map PUBLIC cxx_std_20)

add_library(units STATIC
    src/units/Unit.cpp
    src/units/WorkerAnt.cpp
)
target_include_directories(units PUBLIC src/units)
target_compile_features(units PUBLIC cxx_std_20)
target_link_libraries(units PUBLIC map)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(units PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(valka_mravenist src/main.cpp)
target_compile_features(valka_mravenist PRIVATE cxx_std_20)
target_link_libraries(valka_mravenist PRIVATE units)

# Standalone C++ demonstration without interfering with the QML team's main.
add_executable(valka_mravenist_unit_demo examples/unit_demo.cpp)
target_link_libraries(valka_mravenist_unit_demo PRIVATE units)

if(BUILD_TESTING)
    add_executable(valka_mravenist_map_tests tests/map_tests.cpp)
    target_link_libraries(valka_mravenist_map_tests PRIVATE units)
    add_test(NAME map_tests COMMAND valka_mravenist_map_tests)

    add_executable(valka_mravenist_unit_tests tests/unit_tests.cpp)
    target_link_libraries(valka_mravenist_unit_tests PRIVATE units)
    add_test(NAME unit_tests COMMAND valka_mravenist_unit_tests)
endif()
