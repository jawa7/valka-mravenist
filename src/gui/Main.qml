import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 520
    height: 440
    visible: true
    title: "Válka mravenišť"

    property bool inGame: false
    readonly property int bWidth: mapModel ? mapModel.boardWidth : 10
    readonly property int bHeight: mapModel ? mapModel.boardHeight : 8

    Button {
        anchors.centerIn: parent
        visible: !window.inGame
        text: "Nová hra"
        onClicked: window.inGame = true
    }

    GridView {
        id: grid
        anchors.centerIn: parent
        visible: window.inGame
        width: window.bWidth * 42
        height: window.bHeight * 42
        cellWidth: 42
        cellHeight: 42
        interactive: false

        model: mapModel

        delegate: Rectangle {
            width: 40
            height: 40
            radius: 3
            readonly property bool selected: gameController.selectedX === model.x
                                             && gameController.selectedY === model.y
            color: selected ? "yellow" : (model.terrainType === "Rock" ? "#9e9e9e" : "#8fd18b")

            MouseArea {
                anchors.fill: parent
                onClicked: gameController.selectTile(model.x, model.y)
            }
        }
    }
}

