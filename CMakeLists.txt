cmake_minimum_required(VERSION 3.20)

project(valka_mravenist VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

include(CTest)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

# --- Backend: Map environment ---
add_library(map STATIC
    src/map/GrassTerrain.cpp
    src/map/RockTerrain.cpp
    src/map/Tile.cpp
    src/map/GameBoard.cpp
    src/map/TestMapFactory.cpp
)
target_include_directories(map PUBLIC src/map)
target_compile_features(map PUBLIC cxx_std_20)

# --- Presentation / GUI library ---
add_library(gui STATIC
    src/gui/MapModel.h
    src/gui/MapModel.cpp
    src/gui/GameController.h
    src/gui/GameController.cpp
)
target_include_directories(gui PUBLIC src/gui)
target_compile_features(gui PUBLIC cxx_std_20)
target_link_libraries(gui PUBLIC map Qt6::Quick)

# --- Main application ---
add_executable(valka_mravenist
    src/main.cpp
)

qt_add_qml_module(valka_mravenist
    URI AntWar
    VERSION 1.0
    QML_FILES src/gui/Main.qml
)

target_compile_features(valka_mravenist PRIVATE cxx_std_20)
target_link_libraries(valka_mravenist PRIVATE gui)

# --- Tests ---
if(BUILD_TESTING)
    add_executable(valka_mravenist_map_tests tests/map_tests.cpp)
    target_link_libraries(valka_mravenist_map_tests PRIVATE map)
    add_test(NAME map_tests COMMAND valka_mravenist_map_tests)

    add_executable(valka_mravenist_gui_tests tests/gui_tests.cpp)
    target_link_libraries(valka_mravenist_gui_tests PRIVATE gui Qt6::Core)
    add_test(NAME gui_tests COMMAND valka_mravenist_gui_tests)
endif()

