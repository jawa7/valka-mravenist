#include "GameSession.h"
#include "TestMapFactory.h"

GameSession::GameSession()
    : m_board(TestMapFactory::create()),
      m_mapModel(*m_board),
      m_controller(*m_board)
{
}

MapModel& GameSession::mapModel()
{
    return m_mapModel;
}

GameController& GameSession::controller()
{
    return m_controller;
}

const GameBoard& GameSession::board() const
{
    return *m_board;
}
