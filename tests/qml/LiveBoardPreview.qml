import QtQuick
import QtQuick.Controls
import "../../qml/presentation" as Presentation

ApplicationWindow {
    visible: true
    width: 920
    height: 600
    title: qsTr("Válka mravenišť – mapa z C++")

    Presentation.BoardPage {
        anchors.fill: parent
        boardModel: gameMapModel
        boardWidth: gameMapModel.boardWidth
        boardHeight: gameMapModel.boardHeight
        onBackRequested: Qt.quit()
    }
}
