import QtQuick
import QtQuick.Controls
import "../../qml/presentation" as Presentation

ApplicationWindow {
    visible: true
    width: 850
    height: 560
    title: "Náhled herní mapy"

    ListModel {
        id: previewTiles

        ListElement { x: 0; y: 0; terrainType: "Grass"; unitType: "Worker"; ownerColonyId: 1 }
        ListElement { x: 1; y: 0; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 2; y: 0; terrainType: "Rock"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 3; y: 0; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 4; y: 0; terrainType: "Grass"; unitType: "Soldier"; ownerColonyId: 2 }
        ListElement { x: 0; y: 1; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 1; y: 1; terrainType: "Rock"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 2; y: 1; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 3; y: 1; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 4; y: 1; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 0; y: 2; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 1; y: 2; terrainType: "Grass"; unitType: "Shooter"; ownerColonyId: 1 }
        ListElement { x: 2; y: 2; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 3; y: 2; terrainType: "Rock"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 4; y: 2; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 0; y: 3; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 1; y: 3; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 2; y: 3; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 3; y: 3; terrainType: "Grass"; unitType: ""; ownerColonyId: -1 }
        ListElement { x: 4; y: 3; terrainType: "Grass"; unitType: "WaterBeetle"; ownerColonyId: 2 }
    }

    Presentation.BoardPage {
        anchors.fill: parent
        boardModel: previewTiles
        boardWidth: 5
        boardHeight: 4
        onBackRequested: Qt.quit()
    }
}
