import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    property var boardModel: null
    property int boardWidth: 0
    property int boardHeight: 0
    property int selectedX: -1
    property int selectedY: -1

    signal backRequested()
    signal tileClicked(int x, int y)

    background: Rectangle {
        color: "#f1f4ed"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 12

        RowLayout {
            Layout.fillWidth: true
            spacing: 12

            Button {
                text: qsTr("Zpět do menu")
                onClicked: root.backRequested()
            }

            Label {
                text: qsTr("Herní mapa")
                font.pixelSize: 22
                font.bold: true
                color: "#29452d"
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 12

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#e5eadd"
                radius: 6

                BoardGrid {
                    anchors.fill: parent
                    anchors.margins: 12
                    boardModel: root.boardModel
                    boardWidth: root.boardWidth
                    boardHeight: root.boardHeight
                    selectedX: root.selectedX
                    selectedY: root.selectedY

                    onTileClicked: function(x, y) {
                        root.selectedX = x
                        root.selectedY = y
                        root.tileClicked(x, y)
                    }
                }

                Label {
                    anchors.centerIn: parent
                    visible: root.boardModel === null || root.boardWidth <= 0 || root.boardHeight <= 0
                    text: qsTr("Mapový model není připojen.")
                    color: "#526658"
                }
            }

            Rectangle {
                Layout.preferredWidth: 205
                Layout.fillHeight: true
                color: "#ffffff"
                radius: 6

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    Label {
                        text: qsTr("Vybrané políčko")
                        font.bold: true
                        font.pixelSize: 17
                        color: "#29452d"
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                    }

                    Label {
                        text: root.selectedX < 0
                              ? qsTr("Klikněte na políčko mapy.")
                              : qsTr("Souřadnice: %1, %2").arg(root.selectedX).arg(root.selectedY)
                        color: "#526658"
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                    }

                    Item {
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}
