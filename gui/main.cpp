#include "GameController.h"
#include "MapModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    MapModel mapModel;
    GameController gameController;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mapModel", &mapModel);
    engine.rootContext()->setContextProperty("gameController", &gameController);
    engine.loadFromModule("AntWar", "Main");
    return app.exec();
}
