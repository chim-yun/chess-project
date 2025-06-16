import QtQuick 2.15
import QtQuick.Controls 2.15
import "../qt" as Ui

ApplicationWindow {
    id: root
    visible: true
    width: 1920
    height: 1080
    title: "Chess"

    property bool inGame: false

    Loader {
        id: pageLoader
        anchors.fill: parent
        sourceComponent: inGame ? gamePage : loginPage
    }

    Component {
        id: loginPage
        Ui.Screen01 {
            id: loginScreen
            login_button.onClicked: root.inGame = true
        }
    }

    Component {
        id: gamePage
        Ui.Game_board {
            anchors.fill: parent
        }
    }
}
