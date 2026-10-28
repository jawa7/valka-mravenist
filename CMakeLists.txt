cmake_minimum_required(VERSION 3.20)

project(valka_mravenist VERSION 0.1.0 LANGUAGES CXX)

add_executable(valka_mravenist
    src/main.cpp
)

target_compile_features(valka_mravenist PRIVATE cxx_std_20)
