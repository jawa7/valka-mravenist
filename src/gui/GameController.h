#pragma once

#include <QObject>
#include <QString>

class GameBoard;

class GameController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int selectedX READ selectedX NOTIFY selectionChanged)
    Q_PROPERTY(int selectedY READ selectedY NOTIFY selectionChanged)
    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectionChanged)

public:
    explicit GameController(const GameBoard& board, QObject* parent = nullptr);

    int selectedX() const;
    int selectedY() const;
    bool hasSelection() const;

    Q_INVOKABLE void handleTileClick(int x, int y);
    Q_INVOKABLE void clearSelection();
    Q_INVOKABLE void selectTile(int x, int y);

signals:
    void selectionChanged();
    void actionRejected(const QString& reason);

private:
    const GameBoard& m_board;
    int m_selectedX = -1;
    int m_selectedY = -1;
};

