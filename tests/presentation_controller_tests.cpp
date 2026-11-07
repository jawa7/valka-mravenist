#include <QCoreApplication>
#include <QObject>
#include <QString>

#include "GameController.h"
#include "GameSession.h"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);
    GameSession session;
    GameController& controller = session.controller();

    if (session.mapModel().rowCount() != 80 ||
        session.mapModel().boardWidth() != 10 ||
        session.mapModel().boardHeight() != 8 ||
        controller.hasSelection() ||
        controller.selectedX() != -1 || controller.selectedY() != -1) {
        return 1;
    }

    int selectionSignals = 0;
    int rejectionSignals = 0;
    QString lastError;

    QObject::connect(&controller, &GameController::selectionChanged,
                     [&selectionSignals]() { ++selectionSignals; });
    QObject::connect(&controller, &GameController::actionRejected,
                     [&rejectionSignals, &lastError](const QString& reason) {
                         ++rejectionSignals;
                         lastError = reason;
                     });

    controller.handleTileClick(3, 2);
    if (!controller.hasSelection() || controller.selectedX() != 3 ||
        controller.selectedY() != 2 || selectionSignals != 1) {
        return 2;
    }

    controller.handleTileClick(3, 2);
    if (selectionSignals != 1) {
        return 3;
    }

    controller.handleTileClick(-1, 2);
    controller.handleTileClick(10, 0);
    controller.handleTileClick(0, 8);
    if (rejectionSignals != 3 || lastError.isEmpty() ||
        controller.selectedX() != 3 || controller.selectedY() != 2 ||
        selectionSignals != 1) {
        return 4;
    }

    controller.handleTileClick(0, 0);
    if (controller.selectedX() != 0 || controller.selectedY() != 0 ||
        selectionSignals != 2) {
        return 5;
    }

    controller.clearSelection();
    if (controller.hasSelection() || controller.selectedX() != -1 ||
        controller.selectedY() != -1 || selectionSignals != 3) {
        return 6;
    }

    controller.clearSelection();
    if (selectionSignals != 3) {
        return 7;
    }

    return 0;
}
