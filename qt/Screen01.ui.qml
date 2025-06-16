

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import User_GUI
import QtQuick3D.Helpers 6.8
import QtQuick.Studio.MultiText

Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor
    states: [
        State {
            name: "clicked"
            when: login_button.checked
        }
    ]

    BorderImage {
        id: borderImage
        x: 0
        y: -6
        width: 1920
        height: 1086
        source: "../../../assets/다운로드.jfif"

        Rectangle {
            id: rectangle1
            x: 690
            y: 422
            width: 483
            height: 232
            color: "#ffffff"
            border.color: "#02820e"
            border.width: 20

            Button {
                id: login_button
                x: 171
                y: 18
                width: 110
                height: 38
                visible: true
                text: qsTr("Log in")
                anchors.verticalCenter: parent.verticalCenter
                icon.cache: false
                icon.source: "images/king_b.png"
                transformOrigin: Item.Center
                icon.color: "#ffffff"
                clip: true
                font.pointSize: 15
                highlighted: true
                flat: false
                enabled: true
                anchors.verticalCenterOffset: 143
                anchors.horizontalCenterOffset: 52
                checkable: true
                anchors.horizontalCenter: parent.horizontalCenter

                Connections {
                    target: login_button
                    onClicked: animation.start()
                }
            }

            Button {
                id: signin_button
                x: 355
                y: 240
                width: 128
                height: 38
                visible: true
                text: qsTr("sign in")
                font.letterSpacing: 0
                layer.enabled: false
                leftPadding: 0
                icon.source: "images/king_b.png"
                clip: true
                icon.height: 24
                icon.width: 24
                icon.color: "#000000"
                font.pointSize: 15
                highlighted: true
            }

            TextInput {
                id: id_input
                x: 70
                y: 70
                width: 343
                height: 40
                font.pixelSize: 25
                echoMode: TextInput.Normal
                passwordCharacter: ""
                inputMask: ""
                overwriteMode: true
                readOnly: false
                selectedTextColor: "#ffffff"
            }

            TextInput {
                id: password_input
                x: 70
                y: 130
                width: 343
                height: 31
                font.pixelSize: 25
                inputMask: ""
                echoMode: TextInput.PasswordEchoOnEdit
                readOnly: false
                cursorVisible: false
                overwriteMode: true
            }
        }

        Text {
            id: welcom
            x: 690
            y: 337
            width: 432
            height: 79
            color: "#ffffff"
            text: qsTr("welcome ")
            font.pixelSize: 50
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            clip: false
            font.styleName: "Regular"
            font.bold: true
            layer.enabled: false
            font.weight: Font.Normal
        }
    }
}
