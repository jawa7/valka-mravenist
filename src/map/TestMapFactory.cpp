#include "TestMapFactory.h"

#include <array>
#include <utility>
#include "RockTerrain.h"

std::unique_ptr<GameBoard> TestMapFactory::create() {
    auto board = std::make_unique<GameBoard>(10, 8);
    placeRocks(*board);
    return board;
}

void TestMapFactory::placeRocks(GameBoard& board) {
    static const std::array<std::pair<int, int>, 6> rocks{{
        {3, 2}, {3, 3}, {4, 3}, {6, 5}, {7, 5}, {7, 6}
    }};

    for (const auto& [x, y] : rocks) {
        board.setTerrain(x, y, std::make_unique<RockTerrain>());
    }
}
