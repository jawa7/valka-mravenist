cmake_minimum_required(VERSION 3.20)

project(valka_mravenist VERSION 0.1.0 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
set(CMAKE_AUTOMOC ON)

add_executable(valka_mravenist
    src/main.cpp
)

target_compile_features(valka_mravenist PRIVATE cxx_std_20)

add_executable(valka_mravenist_gui
    gui/main.cpp
    gui/MapModel.h
    gui/MapModel.cpp
    gui/GameController.h
    gui/GameController.cpp
)

qt_add_qml_module(valka_mravenist_gui
    URI AntWar
    VERSION 1.0
    QML_FILES gui/Main.qml
)

target_compile_features(valka_mravenist_gui PRIVATE cxx_std_20)
target_link_libraries(valka_mravenist_gui PRIVATE Qt6::Quick)

add_executable(valka_mravenist_gui_tests
    tests/gui_tests.cpp
    gui/MapModel.h
    gui/MapModel.cpp
    gui/GameController.h
    gui/GameController.cpp
)

target_include_directories(valka_mravenist_gui_tests PRIVATE gui)
target_compile_features(valka_mravenist_gui_tests PRIVATE cxx_std_20)
target_link_libraries(valka_mravenist_gui_tests PRIVATE Qt6::Core)
