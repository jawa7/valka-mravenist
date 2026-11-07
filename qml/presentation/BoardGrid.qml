import QtQuick

Item {
    id: root

    property var boardModel: null
    property int boardWidth: 0
    property int boardHeight: 0
    property int selectedX: -1
    property int selectedY: -1

    signal tileClicked(int x, int y)

    readonly property real tileSize: Math.max(1, Math.min(56, Math.floor(Math.min(
        width / Math.max(1, boardWidth),
        height / Math.max(1, boardHeight)))))

    GridView {
        id: grid
        anchors.centerIn: parent
        width: root.boardWidth * root.tileSize
        height: root.boardHeight * root.tileSize
        cellWidth: root.tileSize
        cellHeight: root.tileSize
        interactive: false
        clip: true
        model: root.boardModel

        delegate: BoardTile {
            width: grid.cellWidth
            height: grid.cellHeight
            tileX: model.x
            tileY: model.y
            terrainType: model.terrainType
            unitType: model.unitType
            ownerColonyId: model.ownerColonyId
            highlighted: tileX === root.selectedX && tileY === root.selectedY
            onTileClicked: root.tileClicked(tileX, tileY)
        }
    }
}
