#pragma once

#include <memory>
#include "GameBoard.h"
#include "GameController.h"
#include "MapModel.h"

class GameSession {
public:
    GameSession();

    MapModel& mapModel();
    GameController& controller();
    const GameBoard& board() const;

private:
    std::unique_ptr<GameBoard> m_board;
    MapModel m_mapModel;
    GameController m_controller;
};
