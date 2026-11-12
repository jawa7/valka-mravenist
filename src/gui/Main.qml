import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: window
    width: 760
    height: 540
    minimumWidth: 620
    minimumHeight: 460
    visible: true
    title: "Válka mravenišť"
    color: "#f1f4ed"

    palette.window: "#f1f4ed"
    palette.windowText: "#222222"
    palette.base: "#ffffff"
    palette.text: "#222222"
    palette.button: "#ffffff"
    palette.buttonText: "#29452d"

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: homePage
    }

    Component {
        id: homePage

        MenuHomePage {
            onNewGameRequested: stack.push(boardPage)
            onRulesRequested: stack.push(rulesPage)
            onQuitRequested: Qt.quit()
        }
    }

    Component {
        id: rulesPage

        MenuRulesPage {
            onBackRequested: stack.pop()
        }
    }

    Component {
        id: boardPage

        BoardPage {
            boardModel: mapModel
            controller: gameController
            onBackRequested: stack.pop()
        }
    }
}


