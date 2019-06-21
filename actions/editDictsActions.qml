import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

Pane {
    background: Rectangle {
        id: rect
        radius: 4
        layer.enabled: true
        layer.effect: DropShadow {
            transparentBorder: true
            verticalOffset: 1
            horizontalOffset: 1
            color: "#80000000"
            radius: 4
        }
    }

    ColumnLayout {
        anchors.fill: parent
        width: parent.width
        Button {
            id: save
            text: qsTr("Сохарнить")
            implicitWidth: 130

            background: Rectangle {
                width: 130
                color: getButtonColor(save)
                radius: 4

            }
            onClicked: {
                console.log()
                dictWrap.saveFile(dictWrap.curFile, textEdit.text)
            }
        }
        Button {
            id: exit
            text: qsTr("Закрыть")
            implicitWidth: 130

            background: Rectangle {
                width: 130
                color: getButtonColor(exit)
                radius: 4

            }

            onClicked: {
                paneText.visible = false
                panePrText.visible = false
                paneItems.visible = true
                paneActions.source = "qrc:/actions/dictsActions.qml"
//                fileWrap.closeFile(fileWrap.curFile)
            }
        }
    }
}
