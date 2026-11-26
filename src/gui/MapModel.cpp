#include "MapModel.h"

#include <QString>
#include "GameBoard.h"
#include "Terrain.h"

MapModel::MapModel(const GameBoard& board, QObject* parent)
    : QAbstractListModel(parent), m_board(board)
{
}

int MapModel::boardWidth() const
{
    return m_board.getWidth();
}

int MapModel::boardHeight() const
{
    return m_board.getHeight();
}

int MapModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return m_board.getTileCount();
}

QVariant MapModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.column() != 0 || index.row() < 0 || index.row() >= m_board.getTileCount()) {
        return QVariant();
    }

    const int width = boardWidth();
    if (width <= 0) {
        return QVariant();
    }

    const int x = index.row() % width;
    const int y = index.row() / width;
    const Tile* tile = m_board.getTile(x, y);
    if (!tile) {
        return QVariant();
    }

    switch (role) {
    case XRole:
        return x;
    case YRole:
        return y;
    case TerrainTypeRole:
        switch (tile->getTerrain().getType()) {
        case TerrainType::Grass:
            return QStringLiteral("Grass");
        case TerrainType::Rock:
            return QStringLiteral("Rock");
        }
        return QStringLiteral("Unknown");
    case UnitTypeRole:
        return QString();
    case OwnerColonyIdRole:
        return -1;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> MapModel::roleNames() const
{
    return {
        {XRole, "x"},
        {YRole, "y"},
        {TerrainTypeRole, "terrainType"},
        {UnitTypeRole, "unitType"},
        {OwnerColonyIdRole, "ownerColonyId"}
    };
}

void MapModel::refreshTile(int x, int y)
{
    if (!m_board.isValidPosition(x, y) || boardWidth() <= 0) {
        return;
    }
    const int row = y * boardWidth() + x;
    const QModelIndex modelIdx = index(row, 0);
    emit dataChanged(modelIdx, modelIdx, {TerrainTypeRole, UnitTypeRole, OwnerColonyIdRole});
}

void MapModel::refreshTiles(int x1, int y1, int x2, int y2)
{
    refreshTile(x1, y1);
    if (x1 != x2 || y1 != y2) {
        refreshTile(x2, y2);
    }
}

