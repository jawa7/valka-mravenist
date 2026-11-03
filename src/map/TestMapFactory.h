#pragma once

#include <memory>
#include "GameBoard.h"

class TestMapFactory {
private:
    static void placeRocks(GameBoard& board);

public:
    static std::unique_ptr<GameBoard> create();
};
