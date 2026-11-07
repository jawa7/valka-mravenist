cmake_minimum_required(VERSION 3.20)

project(valka_mravenist VERSION 0.1.0 LANGUAGES CXX)

add_library(map STATIC
    src/map/GrassTerrain.cpp
    src/map/RockTerrain.cpp
    src/map/Tile.cpp
    src/map/GameBoard.cpp
    src/map/TestMapFactory.cpp
)
target_include_directories(map PUBLIC src/map)
target_compile_features(map PUBLIC cxx_std_20)

add_executable(valka_mravenist
    src/main.cpp
)

target_compile_features(valka_mravenist PRIVATE cxx_std_20)
target_link_libraries(valka_mravenist PRIVATE map)

add_executable(valka_mravenist_map_tests tests/map_tests.cpp)
target_link_libraries(valka_mravenist_map_tests PRIVATE map)

include(CTest)
if(BUILD_TESTING)
    add_test(NAME map_tests COMMAND valka_mravenist_map_tests)
endif()

find_package(Qt6 6.2 QUIET COMPONENTS Quick QuickControls2)
if(Qt6_FOUND)
    add_library(presentation_map STATIC
        src/presentation/GameBoardModel.cpp
        src/presentation/GameBoardModel.h
        src/presentation/GameController.cpp
        src/presentation/GameController.h
        src/presentation/GameSession.cpp
        src/presentation/GameSession.h
    )
    set_target_properties(presentation_map PROPERTIES AUTOMOC ON)
    target_include_directories(presentation_map PUBLIC src/presentation)
    target_link_libraries(presentation_map PUBLIC map Qt6::Core)

    add_executable(valka_mravenist_presentation_preview
        src/presentation/board_preview_main.cpp
    )
    target_link_libraries(valka_mravenist_presentation_preview PRIVATE
        presentation_map Qt6::Quick Qt6::QuickControls2)
    target_compile_definitions(valka_mravenist_presentation_preview PRIVATE
        PRESENTATION_QML_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/tests/qml\")

    if(BUILD_TESTING)
        add_executable(valka_mravenist_presentation_model_tests
            tests/presentation_model_tests.cpp
        )
        target_link_libraries(valka_mravenist_presentation_model_tests PRIVATE presentation_map)
        add_test(NAME presentation_model_tests COMMAND valka_mravenist_presentation_model_tests)

        add_executable(valka_mravenist_presentation_controller_tests
            tests/presentation_controller_tests.cpp
        )
        target_link_libraries(valka_mravenist_presentation_controller_tests PRIVATE presentation_map)
        add_test(NAME presentation_controller_tests COMMAND valka_mravenist_presentation_controller_tests)
    endif()
endif()
