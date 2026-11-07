import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../../qml/presentation" as Presentation

ApplicationWindow {
    visible: true
    width: 920
    height: 600
    title: qsTr("Válka mravenišť – náhled")

    StackLayout {
        id: pages
        anchors.fill: parent
        currentIndex: 0

        Presentation.PresentationMenu {
            onNewGameRequested: {
                sessionController.clearSelection()
                pages.currentIndex = 1
            }
            onQuitRequested: Qt.quit()
        }

        Presentation.BoardPage {
            boardModel: gameMapModel
            boardWidth: gameMapModel.boardWidth
            boardHeight: gameMapModel.boardHeight
            controller: sessionController
            onBackRequested: pages.currentIndex = 0
        }
    }
}
