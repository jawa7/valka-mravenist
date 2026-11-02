#pragma once

#include <QObject>

class GameController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int selectedX READ selectedX NOTIFY selectionChanged)
    Q_PROPERTY(int selectedY READ selectedY NOTIFY selectionChanged)

public:
    int selectedX() const;
    int selectedY() const;
    Q_INVOKABLE void selectTile(int x, int y);

signals:
    void selectionChanged();

private:
    int m_selectedX = -1;
    int m_selectedY = -1;
};
