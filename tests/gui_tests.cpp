#include "GameController.h"
#include "MapModel.h"
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
    MapModel model;
    test_(model.rowCount(QModelIndex()) == 4);
    test_(model.data(model.index(0, 0), Qt::UserRole).toString() == QStringLiteral("grass"));
    test_(model.data(model.index(1, 0), Qt::UserRole).toString() == QStringLiteral("rock"));
}

void testSelection()
{
    GameController controller;
    int changes = 0;
    QObject::connect(&controller, &GameController::selectionChanged, [&changes] { ++changes; });

    test_(controller.selectedX() == -1);
    test_(controller.selectedY() == -1);

    controller.selectTile(1, 0);
    test_(controller.selectedX() == 1);
    test_(controller.selectedY() == 0);
    test_(changes == 1);

    controller.selectTile(1, 0);
    test_(changes == 1);

    controller.selectTile(0, 1);
    test_(controller.selectedX() == 0);
    test_(controller.selectedY() == 1);
    test_(changes == 2);
}

int main()
{
    testMapModel();
    testSelection();
    if (failures == 0) {
        std::cout << "all checks passed\n";
        return 0;
    }
    std::cerr << failures << " check(s) failed\n";
    return 1;
}
