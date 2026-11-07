#include "GameController.h"

#include "GameBoard.h"

GameController::GameController(const GameBoard& board, QObject* parent)
    : QObject(parent), m_board(board) {}

int GameController::selectedX() const {
    return m_selectedX;
}

int GameController::selectedY() const {
    return m_selectedY;
}

bool GameController::hasSelection() const {
    return m_selectedX >= 0;
}

void GameController::handleTileClick(int x, int y) {
    if (!m_board.isValidPosition(x, y)) {
        emit actionRejected(QStringLiteral("Políčko je mimo mapu."));
        return;
    }

    if (m_selectedX == x && m_selectedY == y) {
        return;
    }

    m_selectedX = x;
    m_selectedY = y;
    emit selectionChanged();
}

void GameController::clearSelection() {
    if (!hasSelection()) {
        return;
    }

    m_selectedX = -1;
    m_selectedY = -1;
    emit selectionChanged();
}
