import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: root

    signal newGameRequested()
    signal rulesRequested()
    signal quitRequested()

    background: Rectangle {
        color: "#f1f4ed"
    }

    ColumnLayout {
        anchors.centerIn: parent
        width: Math.min(Math.max(0, root.width - 40), 400)
        spacing: 14

        Label {
            text: qsTr("Válka mravenišť")
            color: "#29452d"
            font.pixelSize: 34
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

        Label {
            text: qsTr("Tahová strategie")
            color: "#526658"
            font.pixelSize: 16
            horizontalAlignment: Text.AlignHCenter
            Layout.fillWidth: true
        }

        Item {
            Layout.preferredHeight: 16
        }

        Button {
            text: qsTr("Nová hra")
            Layout.fillWidth: true
            Layout.preferredHeight: 46
            onClicked: root.newGameRequested()
        }

        Button {
            text: qsTr("Pravidla")
            Layout.fillWidth: true
            Layout.preferredHeight: 46
            onClicked: root.rulesRequested()
        }

        Button {
            text: qsTr("Ukončit")
            Layout.fillWidth: true
            Layout.preferredHeight: 46
            onClicked: root.quitRequested()
        }
    }
}
