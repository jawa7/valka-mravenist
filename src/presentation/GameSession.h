#pragma once

#include <memory>

#include "GameBoard.h"
#include "GameBoardModel.h"
#include "GameController.h"

class GameSession final {
public:
    GameSession();

    GameBoardModel& mapModel();
    GameController& controller();

private:
    std::unique_ptr<GameBoard> m_board;
    GameBoardModel m_mapModel;
    GameController m_controller;
};
