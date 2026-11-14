import QtQuick
import QtQuick.Controls

Page {
    id: root

    signal backRequested()

    background: Rectangle {
        color: "#f1f4ed"
    }

    ScrollView {
        anchors.fill: parent
        contentWidth: availableWidth

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            width: Math.min(Math.max(300, root.width - 40), 600)
            spacing: 14

            Item {
                width: parent.width
                height: 20
            }

            Label {
                text: "Pravidla hry"
                font.pixelSize: 26
                font.bold: true
                color: "#29452d"
            }

            Label {
                width: parent.width
                text: "Dvě nebo více mravenčích kolonií soupeří o území zahrady."
                color: "#2b3d2d"
                font.pixelSize: 15
                wrapMode: Text.WordWrap
            }

            Label {
                width: parent.width
                text: "Jednotky se pohybují po mapě s různými druhy terénu. Tráva, písek, kamení, listí a louže ovlivňují pohyb a obranu."
                color: "#2b3d2d"
                font.pixelSize: 15
                wrapMode: Text.WordWrap
            }

            Label {
                width: parent.width
                text: "Dělnice (D / d) sbírají potravu pro stavbu nových komor mraveniště a líheň dalších kast."
                color: "#2b3d2d"
                font.pixelSize: 15
                wrapMode: Text.WordWrap
            }

            Label {
                width: parent.width
                text: "Počasí může zaplavit nízko položená políčka, která po dešti opět vysychají."
                color: "#2b3d2d"
                font.pixelSize: 15
                wrapMode: Text.WordWrap
            }

            Label {
                width: parent.width
                text: "Cílem hry je ovládnout zahradu a zničit nepřátelské kolonie."
                color: "#2b3d2d"
                font.pixelSize: 15
                wrapMode: Text.WordWrap
            }

            Item {
                width: parent.width
                height: 12
            }

            Button {
                height: 42
                text: "Zpět do menu"
                contentItem: Text {
                    text: parent.text
                    font.pixelSize: 15
                    font.bold: true
                    color: "#29452d"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
                background: Rectangle {
                    implicitWidth: 140
                    color: parent.down ? "#d0dbc5" : (parent.hovered ? "#e0ebd8" : "#ffffff")
                    border.color: "#8fa391"
                    border.width: 1
                    radius: 6
                }
                onClicked: root.backRequested()
            }

            Item {
                width: parent.width
                height: 20
            }
        }
    }
}
