#pragma once

#include <QAbstractListModel>
#include <QVariant>
#include "GameBoard.h"

class GameBoardModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int boardWidth READ boardWidth CONSTANT)
    Q_PROPERTY(int boardHeight READ boardHeight CONSTANT)

public:
    enum Role {
        XRole = Qt::UserRole + 1,
        YRole,
        TerrainTypeRole,
        UnitTypeRole,
        OwnerColonyIdRole
    };

    explicit GameBoardModel(const GameBoard& board, QObject* parent = nullptr);

    int boardWidth() const;
    int boardHeight() const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void refreshTile(int x, int y);
    void refreshTiles(int firstX, int firstY, int secondX, int secondY);

private:
    const GameBoard& m_board;
};
