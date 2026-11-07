#include "GameBoardModel.h"

#include <QString>
#include "Terrain.h"

GameBoardModel::GameBoardModel(const GameBoard& board, QObject* parent)
    : QAbstractListModel(parent), m_board(board) {}

int GameBoardModel::boardWidth() const {
    return m_board.getWidth();
}

int GameBoardModel::boardHeight() const {
    return m_board.getHeight();
}

int GameBoardModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : m_board.getTileCount();
}

QVariant GameBoardModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.column() != 0 ||
        index.row() < 0 || index.row() >= m_board.getTileCount()) {
        return {};
    }

    const int x = index.row() % boardWidth();
    const int y = index.row() / boardWidth();
    const Tile* tile = m_board.getTile(x, y);

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
        return {};
    case UnitTypeRole:
        return QString();
    case OwnerColonyIdRole:
        return -1;
    default:
        return {};
    }
}

QHash<int, QByteArray> GameBoardModel::roleNames() const {
    return {
        {XRole, "x"},
        {YRole, "y"},
        {TerrainTypeRole, "terrainType"},
        {UnitTypeRole, "unitType"},
        {OwnerColonyIdRole, "ownerColonyId"}
    };
}

void GameBoardModel::refreshTile(int x, int y) {
    if (!m_board.isValidPosition(x, y)) {
        return;
    }

    const QModelIndex tileIndex = index(y * boardWidth() + x, 0);
    emit dataChanged(tileIndex, tileIndex,
                     {TerrainTypeRole, UnitTypeRole, OwnerColonyIdRole});
}

void GameBoardModel::refreshTiles(int firstX, int firstY,
                                  int secondX, int secondY) {
    refreshTile(firstX, firstY);
    if (firstX != secondX || firstY != secondY) {
        refreshTile(secondX, secondY);
    }
}
