import QtQuick
import QtQuick.Controls

Page {
    id: root

    property var boardModel: null
    property var controller: null
    property string errorMessage: ""

    signal backRequested()

    Connections {
        target: root.controller

        function onActionRejected(reason) {
            root.errorMessage = reason
        }

        function onSelectionChanged() {
            root.errorMessage = ""
        }
    }

    background: Rectangle {
        color: "#f1f4ed"
    }

    Item {
        id: topBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 52
        anchors.margins: 12

        Button {
            id: backBtn
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            height: 38
            text: "Zpět do menu"
            contentItem: Text {
                text: parent.text
                font.pixelSize: 14
                font.bold: true
                color: "#29452d"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            background: Rectangle {
                implicitWidth: 120
                color: parent.down ? "#d0dbc5" : (parent.hovered ? "#e0ebd8" : "#ffffff")
                border.color: "#8fa391"
                border.width: 1
                radius: 6
            }
            onClicked: {
                if (root.controller) {
                    root.controller.clearSelection()
                }
                root.errorMessage = ""
                root.backRequested()
            }
        }

        Label {
            anchors.left: backBtn.right
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            text: "Herní mapa (10×8)"
            font.pixelSize: 20
            font.bold: true
            color: "#29452d"
        }
    }

    Item {
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 12

        Rectangle {
            id: boardContainer
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: sidePanel.left
            anchors.rightMargin: 12
            color: "#e5eadd"
            radius: 6

            BoardGrid {
                anchors.fill: parent
                anchors.margins: 12
                boardModel: root.boardModel
                boardWidth: root.boardModel ? root.boardModel.boardWidth : 10
                boardHeight: root.boardModel ? root.boardModel.boardHeight : 8
                selectedX: root.controller ? root.controller.selectedX : -1
                selectedY: root.controller ? root.controller.selectedY : -1

                onTileClicked: function(x, y) {
                    if (root.controller) {
                        root.controller.handleTileClick(x, y)
                    }
                }
            }
        }

        Rectangle {
            id: sidePanel
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            width: 210
            color: "#ffffff"
            radius: 6

            Column {
                anchors.fill: parent
                anchors.margins: 14
                spacing: 12

                Label {
                    text: "Vybrané políčko"
                    font.bold: true
                    font.pixelSize: 16
                    color: "#29452d"
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    color: "#526658"
                    font.pixelSize: 14
                    text: {
                        if (!root.controller || !root.controller.hasSelection) {
                            return "Klikněte na políčko mapy."
                        }
                        return "Souřadnice: [" + root.controller.selectedX + ", " + root.controller.selectedY + "]"
                    }
                }

                Button {
                    width: parent.width
                    height: 38
                    text: "Zrušit výběr"
                    visible: root.controller && root.controller.hasSelection
                    contentItem: Text {
                        text: parent.text
                        font.pixelSize: 14
                        font.bold: true
                        color: "#29452d"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        color: parent.down ? "#d0dbc5" : (parent.hovered ? "#e0ebd8" : "#f1f4ed")
                        border.color: "#8fa391"
                        border.width: 1
                        radius: 6
                    }
                    onClicked: {
                        if (root.controller) {
                            root.controller.clearSelection()
                        }
                    }
                }

                Item {
                    width: parent.width
                    height: 8
                }

                Label {
                    width: parent.width
                    wrapMode: Text.WordWrap
                    color: "#a23d30"
                    font.bold: true
                    font.pixelSize: 14
                    visible: root.errorMessage !== ""
                    text: root.errorMessage
                }
            }
        }
    }
}
