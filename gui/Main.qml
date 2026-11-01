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

        highlight: Rectangle {
            width: grid.cellWidth
            height: grid.cellHeight
            color: "yellow"
        }

        delegate: Rectangle {
            width: 80
            height: 80
            color: terrainType === "rock" ? "gray" : "lightgreen"

            MouseArea {
                anchors.fill: parent
                onClicked: grid.currentIndex = index
            }
        }
    }
}
