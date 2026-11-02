cmake_minimum_required(VERSION 3.20)

project(valka_mravenist VERSION 0.1.0 LANGUAGES CXX)

add_library(map STATIC
    src/map/GrassTerrain.cpp
)
target_include_directories(map PUBLIC src/map)
target_compile_features(map PUBLIC cxx_std_20)

add_executable(valka_mravenist
    src/main.cpp
)

target_compile_features(valka_mravenist PRIVATE cxx_std_20)
target_link_libraries(valka_mravenist PRIVATE map)