#include "GameSession.h"

#include "TestMapFactory.h"

GameSession::GameSession()
    : m_board(TestMapFactory::create()),
      m_mapModel(*m_board),
      m_controller(*m_board) {}

GameBoardModel& GameSession::mapModel() {
    return m_mapModel;
}

GameController& GameSession::controller() {
    return m_controller;
}
