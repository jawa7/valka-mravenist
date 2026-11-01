#include "GameController.h"

int GameController::selectedIndex() const
{
    return m_selectedIndex;
}

void GameController::selectTile(int index)
{
    if (m_selectedIndex == index) {
        return;
    }
    m_selectedIndex = index;
    emit selectedIndexChanged();
}
