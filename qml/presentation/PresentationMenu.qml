import QtQuick
import QtQuick.Controls

Item {
    id: root

    signal newGameRequested()
    signal quitRequested()

    StackView {
        id: pages
        anchors.fill: parent
        initialItem: homePage
    }

    Component {
        id: homePage

        MenuHomePage {
            onNewGameRequested: root.newGameRequested()
            onRulesRequested: pages.push(rulesPage)
            onQuitRequested: root.quitRequested()
        }
    }

    Component {
        id: rulesPage

        MenuRulesPage {
            onBackRequested: pages.pop()
        }
    }
}
