import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 400
    height: 300
    visible: true
    title: "Válka mravenišť"

    property bool inGame: false

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
        width: 2 * 84
        height: 2 * 84
        cellWidth: 84
        cellHeight: 84
        interactive: false

        model: mapModel

        delegate: Rectangle {
            width: 80
            height: 80
            readonly property bool selected: gameController.selectedX === index % 2
                                             && gameController.selectedY === Math.floor(index / 2)
            color: selected ? "yellow" : (terrainType === "rock" ? "gray" : "lightgreen")

            MouseArea {
                anchors.fill: parent
                onClicked: gameController.selectTile(index % 2, Math.floor(index / 2))
            }
        }
    }
}
