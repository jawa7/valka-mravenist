import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    signal backRequested()

    background: Rectangle {
        color: "#f1f4ed"
    }

    ScrollView {
        anchors.fill: parent
        contentWidth: availableWidth

        ColumnLayout {
            x: Math.max(20, (root.width - width) / 2)
            width: Math.min(Math.max(0, root.width - 40), 600)
            spacing: 14

            Item {
                Layout.preferredHeight: 16
            }

            Label {
                text: qsTr("Pravidla hry")
                font.pixelSize: 28
                font.bold: true
                color: "#29452d"
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Dvě nebo více mravenčích kolonií soupeří o území zahrady.")
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Jednotky se pohybují po mapě s různými druhy terénu. Tráva, písek, kamení, listí a louže mohou ovlivnit jejich vlastnosti i průchodnost.")
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Dělnice sbírají potravu. Za potravu se pořizují nové jednotky a stavějí komory mraveniště.")
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Počasí mění herní mapu. Déšť může zaplavit nízko položená políčka, která později znovu vyschnou.")
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Vyhrává kolonie, která odstraní všechny nepřátelské jednotky a komory.")
                wrapMode: Text.WordWrap
                Layout.fillWidth: true
            }

            Button {
                text: qsTr("Zpět do menu")
                Layout.alignment: Qt.AlignHCenter
                onClicked: root.backRequested()
            }

            Item {
                Layout.preferredHeight: 16
            }
        }
    }
}
