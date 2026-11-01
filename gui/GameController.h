#pragma once

#include <QObject>

class GameController : public QObject {
    Q_OBJECT

public:
    Q_INVOKABLE int selectTile(int index);

private:
    int m_selectedIndex = -1;
};
