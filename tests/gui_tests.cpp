#include "GameController.h"
#include "GameSession.h"
#include "MapModel.h"
#include "TestMapFactory.h"
#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <iostream>

int failures = 0;

void check(bool ok, const char* text, const char* file, int line)
{
    if (!ok) {
        std::cerr << file << ":" << line << ": failed: " << text << '\n';
        ++failures;
    }
}

#define test_(cond) check((cond), #cond, __FILE__, __LINE__)

void testMapModel()
{
    auto board = TestMapFactory::create();
    MapModel model(*board);

    test_(model.boardWidth() == 10);
    test_(model.boardHeight() == 8);
    test_(model.rowCount(QModelIndex()) == 80);
    test_(model.rowCount(model.index(0, 0)) == 0);

    const auto roles = model.roleNames();
    test_(roles.value(MapModel::XRole) == "x");
    test_(roles.value(MapModel::YRole) == "y");
    test_(roles.value(MapModel::TerrainTypeRole) == "terrainType");
    test_(roles.value(MapModel::UnitTypeRole) == "unitType");
    test_(roles.value(MapModel::OwnerColonyIdRole) == "ownerColonyId");

    QModelIndex origin = model.index(0, 0);
    test_(model.data(origin, MapModel::XRole).toInt() == 0);
    test_(model.data(origin, MapModel::YRole).toInt() == 0);
    test_(model.data(origin, MapModel::TerrainTypeRole).toString() == QStringLiteral("Grass"));
    test_(model.data(origin, MapModel::UnitTypeRole).toString().isEmpty());
    test_(model.data(origin, MapModel::OwnerColonyIdRole).toInt() == -1);

    QModelIndex rockIndex = model.index(23, 0);
    test_(model.data(rockIndex, MapModel::XRole).toInt() == 3);
    test_(model.data(rockIndex, MapModel::YRole).toInt() == 2);
    test_(model.data(rockIndex, MapModel::TerrainTypeRole).toString() == QStringLiteral("Rock"));

    test_(!model.data(QModelIndex(), MapModel::TerrainTypeRole).isValid());
    test_(!model.data(model.index(-1, 0), MapModel::TerrainTypeRole).isValid());
    test_(!model.data(model.index(80, 0), MapModel::TerrainTypeRole).isValid());

    int changedCount = 0;
    QObject::connect(&model, &QAbstractItemModel::dataChanged,
                     [&changedCount](const QModelIndex&, const QModelIndex&, const QList<int>&) {
                         ++changedCount;
                     });

    model.refreshTile(-1, 0);
    test_(changedCount == 0);

    model.refreshTile(0, 0);
    test_(changedCount == 1);

    model.refreshTiles(0, 0, 1, 0);
    test_(changedCount == 3);
}

void testGameSessionAndController()
{
    GameSession session;
    test_(session.mapModel().rowCount() == 80);
    test_(session.mapModel().boardWidth() == 10);
    test_(session.mapModel().boardHeight() == 8);

    GameController& controller = session.controller();
    test_(!controller.hasSelection());
    test_(controller.selectedX() == -1);
    test_(controller.selectedY() == -1);

    int selectionSignals = 0;
    int rejectionSignals = 0;
    QString lastRejection;

    QObject::connect(&controller, &GameController::selectionChanged,
                     [&selectionSignals]() { ++selectionSignals; });
    QObject::connect(&controller, &GameController::actionRejected,
                     [&rejectionSignals, &lastRejection](const QString& reason) {
                         ++rejectionSignals;
                         lastRejection = reason;
                     });

    controller.handleTileClick(3, 2);
    test_(controller.hasSelection());
    test_(controller.selectedX() == 3);
    test_(controller.selectedY() == 2);
    test_(selectionSignals == 1);

    controller.handleTileClick(3, 2);
    test_(selectionSignals == 1);

    controller.handleTileClick(-1, 2);
    controller.handleTileClick(10, 0);
    controller.handleTileClick(0, 8);
    test_(rejectionSignals == 3);
    test_(lastRejection == QStringLiteral("Políčko je mimo mapu."));

    test_(controller.hasSelection());
    test_(controller.selectedX() == 3);
    test_(controller.selectedY() == 2);
    test_(selectionSignals == 1);

    controller.handleTileClick(0, 0);
    test_(controller.selectedX() == 0);
    test_(controller.selectedY() == 0);
    test_(selectionSignals == 2);

    controller.clearSelection();
    test_(!controller.hasSelection());
    test_(controller.selectedX() == -1);
    test_(controller.selectedY() == -1);
    test_(selectionSignals == 3);

    controller.clearSelection();
    test_(selectionSignals == 3);
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    testMapModel();
    testGameSessionAndController();
    if (failures == 0) {
        std::cout << "all checks passed\n";
        return 0;
    }
    std::cerr << failures << " check(s) failed\n";
    return 1;
}
