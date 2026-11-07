import QtQuick

Rectangle {
    id: root

    property int tileX: -1
    property int tileY: -1
    property var terrainType: "Grass"
    property var unitType: ""
    property int ownerColonyId: -1
    property bool highlighted: false

    signal tileClicked(int x, int y)

    readonly property bool isRock: terrainType === 1 || terrainType === "Rock"
    readonly property color terrainColor: colorForTerrain(terrainType)
    readonly property string unitSymbol: symbolForUnit(unitType)

    function colorForTerrain(type) {
        if (type === 1 || type === "Rock") return "#a5a9ab"
        if (type === "Sand") return "#e9d49c"
        if (type === "Leaves") return "#bc9566"
        if (type === "Puddle") return "#80b9d4"
        if (type === "Lowland") return "#83b992"
        return "#acd39d"
    }

    function symbolForUnit(type) {
        switch (type) {
        case 0: case "Worker": return "D"
        case 1: case "Soldier": return "V"
        case 2: case "Shooter": return "S"
        case 3: case "Winged": return "L"
        case 4: case "WaterBeetle": return "B"
        default: return ""
        }
    }

    color: terrainColor
    radius: 3
    border.color: highlighted ? "#e5a322" : "#678269"
    border.width: highlighted ? 3 : 1

    Text {
        anchors.centerIn: parent
        text: root.unitSymbol !== "" ? root.unitSymbol : (root.isRock ? "#" : "")
        color: root.unitSymbol === "" ? "#566266" : (root.ownerColonyId === 2 ? "#23558b" : "#8b2929")
        font.bold: true
        font.pixelSize: Math.max(12, Math.min(root.width, root.height) * 0.47)
    }

    MouseArea {
        anchors.fill: parent
        onClicked: root.tileClicked(root.tileX, root.tileY)
    }
}
