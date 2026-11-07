#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>

#include "GameSession.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    GameSession session;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gameMapModel", &session.mapModel());
    engine.rootContext()->setContextProperty("sessionController", &session.controller());
    engine.load(QUrl::fromLocalFile(
        QStringLiteral(PRESENTATION_QML_DIR "/LiveBoardPreview.qml")));

    if (engine.rootObjects().isEmpty()) {
        return 1;
    }
    return app.exec();
}
