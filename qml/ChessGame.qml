import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: root
    visible: true
    width: 480
    height: 480
    title: "Chess"

    property int whiteTime: 600
    property int blackTime: 600

    Timer {
        id: turnTimer
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            if (game.sideToMove === "White")
                whiteTime--
            else
                blackTime--
            if (whiteTime <= 0 || blackTime <= 0) {
                turnTimer.stop()
                game.timeOut()
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        Text { text: "White: " + whiteTime }
        Text { text: "Black: " + blackTime }
        Button { text: "Resign"; onClicked: game.resign() }
    }
}
