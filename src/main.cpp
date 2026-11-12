#include "GameSession.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    GameSession session;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("mapModel", &session.mapModel());
    engine.rootContext()->setContextProperty("gameController", &session.controller());
    engine.loadFromModule("AntWar", "Main");
    return app.exec();
}
