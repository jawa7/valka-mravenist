#include "MapModel.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    MapModel mapModel;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mapModel", &mapModel);
    engine.loadFromModule("AntWar", "Main");
    return app.exec();
}
