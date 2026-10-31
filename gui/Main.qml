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

    Grid {
        anchors.centerIn: parent
        visible: window.inGame
        columns: 2
        spacing: 4

        Repeater {
            model: 4

            Rectangle {
                width: 80
                height: 80
                color: "lightgreen"
            }
        }
    }
}
