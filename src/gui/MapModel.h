#pragma once

#include <QAbstractListModel>
#include <QByteArray>
#include <QHash>
#include <QModelIndex>
#include <QVariant>

class GameBoard;

class MapModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int boardWidth READ boardWidth CONSTANT)
    Q_PROPERTY(int boardHeight READ boardHeight CONSTANT)

public:
    enum Roles {
        XRole = Qt::UserRole + 1,
        YRole,
        TerrainTypeRole,
        UnitTypeRole,
        OwnerColonyIdRole
    };

    explicit MapModel(const GameBoard& board, QObject* parent = nullptr);

    int boardWidth() const;
    int boardHeight() const;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void refreshTile(int x, int y);
    void refreshTiles(int x1, int y1, int x2, int y2);

private:
    const GameBoard& m_board;
};

