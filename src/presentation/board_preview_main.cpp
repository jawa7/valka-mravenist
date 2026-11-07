#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>

#include "GameBoardModel.h"
#include "TestMapFactory.h"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    auto board = TestMapFactory::create();
    GameBoardModel model(*board);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("gameMapModel", &model);
    engine.load(QUrl::fromLocalFile(
        QStringLiteral(PRESENTATION_QML_DIR "/LiveBoardPreview.qml")));

    if (engine.rootObjects().isEmpty()) {
        return 1;
    }
    return app.exec();
}
