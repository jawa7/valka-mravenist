import QtQuick

Rectangle {
    id: root

    property int tileX: -1
    property int tileY: -1
    property string terrainType: "Grass"
    property string unitType: ""
    property int ownerColonyId: -1
    property bool highlighted: false

    signal tileClicked(int x, int y)

    readonly property bool isRock: terrainType === "Rock" || terrainType === "rock"
    readonly property color terrainColor: isRock ? "#9e9e9e" : "#8fd18b"
    readonly property string unitSymbol: unitType === "Worker" || unitType === "worker" ? "D" : ""

    color: terrainColor
    radius: 3
    border.color: highlighted ? "#e5a322" : "#628064"
    border.width: highlighted ? 3 : 1

    Text {
        anchors.centerIn: parent
        text: root.unitSymbol !== "" ? root.unitSymbol : (root.isRock ? "#" : ".")
        color: root.unitSymbol !== "" ? (root.ownerColonyId === 2 ? "#23558b" : "#8b2929") : (root.isRock ? "#555555" : "#5d8b59")
        font.bold: true
        font.pixelSize: Math.max(12, Math.min(root.width, root.height) * 0.45)
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.tileClicked(root.tileX, root.tileY)
    }
}
