#include "GameController.h"

int GameController::selectedX() const
{
    return m_selectedX;
}

int GameController::selectedY() const
{
    return m_selectedY;
}

void GameController::selectTile(int x, int y)
{
    if (m_selectedX == x && m_selectedY == y) {
        return;
    }
    m_selectedX = x;
    m_selectedY = y;
    emit selectionChanged();
}
