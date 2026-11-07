#include <QCoreApplication>
#include <QModelIndex>
#include <QObject>

#include <memory>

#include "GameBoardModel.h"
#include "RockTerrain.h"
#include "TestMapFactory.h"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    auto board = TestMapFactory::create();
    GameBoardModel model(*board);

    if (model.boardWidth() != 10 || model.boardHeight() != 8 ||
        model.rowCount() != 80 || model.rowCount(model.index(0, 0)) != 0) {
        return 1;
    }

    const auto roles = model.roleNames();
    if (roles.value(GameBoardModel::XRole) != "x" ||
        roles.value(GameBoardModel::YRole) != "y" ||
        roles.value(GameBoardModel::TerrainTypeRole) != "terrainType" ||
        roles.value(GameBoardModel::UnitTypeRole) != "unitType" ||
        roles.value(GameBoardModel::OwnerColonyIdRole) != "ownerColonyId") {
        return 2;
    }

    const QModelIndex rock = model.index(2 * model.boardWidth() + 3, 0);
    if (model.data(rock, GameBoardModel::XRole).toInt() != 3 ||
        model.data(rock, GameBoardModel::YRole).toInt() != 2 ||
        model.data(rock, GameBoardModel::TerrainTypeRole).toString() != "Rock" ||
        model.data(rock, GameBoardModel::UnitTypeRole).toString() != "" ||
        model.data(rock, GameBoardModel::OwnerColonyIdRole).toInt() != -1 ||
        model.data(QModelIndex(), GameBoardModel::TerrainTypeRole).isValid()) {
        return 3;
    }

    int changedCount = 0;
    QObject::connect(&model, &QAbstractItemModel::dataChanged,
                     [&changedCount](const QModelIndex&, const QModelIndex&,
                                     const QList<int>&) { ++changedCount; });

    model.refreshTile(-1, 0);
    if (changedCount != 0) {
        return 4;
    }

    board->setTerrain(0, 0, std::make_unique<RockTerrain>());
    model.refreshTile(0, 0);
    if (changedCount != 1 ||
        model.data(model.index(0, 0), GameBoardModel::TerrainTypeRole).toString() != "Rock") {
        return 5;
    }

    model.refreshTiles(0, 0, 1, 0);
    if (changedCount != 3) {
        return 6;
    }
    return 0;
}
