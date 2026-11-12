import QtQuick
import QtQuick.Controls

Page {
    id: root

    signal newGameRequested()
    signal rulesRequested()
    signal quitRequested()

    background: Rectangle {
        color: "#f1f4ed"
    }

    Column {
        anchors.centerIn: parent
        width: 360
        spacing: 16

        Label {
            width: parent.width
            text: "Válka mravenišť"
            color: "#29452d"
            font.pixelSize: 34
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }

        Label {
            width: parent.width
            text: "Tahová strategie"
            color: "#526658"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
        }

        Item {
            width: parent.width
            height: 16
        }

        Button {
            width: parent.width
            height: 48
            text: "Nová hra"
            contentItem: Text {
                text: parent.text
                font.pixelSize: 16
                font.bold: true
                color: "#29452d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.down ? "#d0dbc5" : (parent.hovered ? "#e0ebd8" : "#ffffff")
                border.color: "#8fa391"
                border.width: 1
                radius: 6
            }
            onClicked: root.newGameRequested()
        }

        Button {
            width: parent.width
            height: 48
            text: "Pravidla"
            contentItem: Text {
                text: parent.text
                font.pixelSize: 16
                font.bold: true
                color: "#29452d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.down ? "#d0dbc5" : (parent.hovered ? "#e0ebd8" : "#ffffff")
                border.color: "#8fa391"
                border.width: 1
                radius: 6
            }
            onClicked: root.rulesRequested()
        }

        Button {
            width: parent.width
            height: 48
            text: "Ukončit"
            contentItem: Text {
                text: parent.text
                font.pixelSize: 16
                font.bold: true
                color: "#7a2a2a"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                color: parent.down ? "#ebd0d0" : (parent.hovered ? "#f5dfdf" : "#ffffff")
                border.color: "#b08585"
                border.width: 1
                radius: 6
            }
            onClicked: root.quitRequested()
        }
    }
}
