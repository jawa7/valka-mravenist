#pragma once

#include <QAbstractListModel>
#include <QString>
#include <vector>

class MapModel : public QAbstractListModel {
    Q_OBJECT

public:
    int rowCount(const QModelIndex&) const;
    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const;

private:
    std::vector<QString> m_terrain = {"grass", "rock", "grass", "grass"};
};
