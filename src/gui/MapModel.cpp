#include "MapModel.h"

int MapModel::rowCount(const QModelIndex&) const
{
    return int(m_terrain.size());
}

QVariant MapModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::UserRole) {
        return m_terrain[index.row()];
    }
    return QVariant();
}

QHash<int, QByteArray> MapModel::roleNames() const
{
    return {{Qt::UserRole, "terrainType"}};
}
