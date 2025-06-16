/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 1920
    height: 1080
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

    BorderImage {
        id: borderImage
        x: 0
        y: 0
        width: 1920
        height: 1080
        source: "../../../assets/다운로드.jfif"

        BorderImage {
            id: borderImage1
            x: 508
            y: 129
            width: 800
            height: 800
            source: "../../../assets/chess board.png"

            Image {
                id: rook_w_r
                x: 700
                y: 700
                width: 100
                source: "images/rook_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: knight_w_l
                x: 100
                y: 700
                width: 100
                source: "images/knight_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: bishop_w_l
                x: 200
                y: 700
                width: 100
                source: "images/bishop_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rook_w_l
                x: 0
                y: 700
                width: 100
                height: 100
                source: "images/rook_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: bishop_w_r
                x: 500
                y: 700
                width: 100
                source: "images/bishop_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: knight_w_r
                x: 600
                y: 700
                width: 100
                source: "images/knight_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: king_w
                x: 400
                y: 700
                width: 100
                source: "images/king_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: queen_w
                x: 300
                y: 700
                width: 100
                source: "images/queen_w.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_b_1
                x: 0
                y: 100
                width: 100
                height: 96
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_b_2
                x: 100
                y: 100
                width: 100
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_b_3
                x: 200
                y: 100
                width: 100
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_b_4
                x: 300
                y: 100
                width: 100
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_b_5
                x: 400
                y: 100
                width: 100
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_b_6
                x: 500
                y: 100
                width: 100
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }


            Image {
                id: pawn_b_7
                x: 600
                y: 100
                width: 100
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_b_8
                x: 700
                y: 100
                width: 100
                source: "images/black_pawn_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: bishop_b_l
                x: 200
                y: 0
                width: 100
                source: "images/black_bishop_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: bishop_b_r
                x: 500
                y: 0
                width: 100
                source: "images/black_bishop_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: knight_b_l
                x: 100
                y: 0
                width: 100
                source: "images/black_knight_outlined.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: knight_b_r
                x: 600
                y: 0
                width: 100
                source: "images/black_knight_outlined.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rook_b_l
                x: 0
                y: 0
                width: 100
                source: "images/black_rook_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: rook_b_r
                x: 700
                y: 0
                width: 100
                source: "images/black_rook_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: king_b
                x: 400
                y: 0
                width: 100
                source: "images/ChatGPT Image 2025년 6월 17일 오전 01_06_54.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: queen_b
                x: 300
                y: 0
                width: 100
                source: "images/black_queen_outlined_fixed.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_1
                x: 0
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_2
                x: 100
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_3
                x: 200
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_4
                x: 300
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_5
                x: 400
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_6
                x: 500
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_7
                x: 600
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: pawn_w_8
                x: 700
                y: 600
                width: 100
                source: "images/white_pawn_outer_transparent_only.png"
                fillMode: Image.PreserveAspectFit
            }

        }
    }

    Column {
        id: timerDisplay
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 20
        spacing: 4
        Text { text: "White: " + whiteTime }
        Text { text: "Black: " + blackTime }
    }

    Button {
        id: resignButton
        text: qsTr("Resign")
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        onClicked: {
            turnTimer.stop()
            game.resign()
        }
    }
}
