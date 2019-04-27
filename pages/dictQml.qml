import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import DictHandler 1.0

Page {
    height: window.height
    width: parent.width
    property string fileName: ""

    function getTextAreaHeight() {
        return window.height - window.header.height - 10
    }
    function getTextAreaWidth() {
        if (window.width >= 600) {
            if (paneText.visible) {
                return parent.width - paneActions.width - 30;
            } else {
                return parent.width - 30;
            }
        }
        return column.width - 20;
    }
    function getButtonColor(idButton) {
        if (idButton.pressed) {
            return "#706f6fe";
        }
        if (idButton.hovered) {
            return "#9e9e9e";
        } else {
            return "#d6d6d6";
        }
    }

    DictHandler {
        id: dictHandler
    }

    Row {
        x: 10
        y: 5
        spacing: 10

        Pane {
            id: paneItems
            height: getTextAreaHeight()
            width: getTextAreaWidth()

            //альтернативный заголовок
            Label {
                id: label
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Обработанных словарей пока нет."
                visible: dictHandler.dataList.length === 0 ? true : false
            }

            ScrollView {
//                id: textEdit
                anchors.fill: parent
                implicitHeight: getTextAreaHeight()
                implicitWidth: getTextAreaWidth()
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                clip: true

                visible: dictHandler.dataList.length !== 0 ? true : false

                ListView {
                    id: listView
                    width: getTextAreaWidth()
                    height: getTextAreaHeight()
                    spacing: 10
                    highlight: highlight
                    highlightFollowsCurrentItem: false

                    model: dictHandler.dataList
                    delegate: Rectangle {
                        id: rect
                        width: getTextAreaWidth() - 30
                        height: 70
                        radius: 6

                        MouseArea {
                            id: mArea
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            onDoubleClicked: {
//                                textEdit.text = textHandler.getFileContent(path.text);
                                paneItems.visible = false
                                paneText.visible = true
                                paneActions.visible = true
                                textEdit.text = dictHandler.getFileContent(name.text)
                            }
                            onHoveredChanged: {
                                if (mArea.containsMouse) {
                                    rect.color = "#a9a9aa"
                                } else {
                                    rect.color = "#ffffff"
                                }
                            }
                            Menu {
                                id: contextMenu
                                Action {
                                    text: "Удалить"
//                                    onTriggered: {
//                                        textHandler.deleteFile(path.text)
//                                    }
                                }

                            }
                        }
                        Label {
                            id: name
                            topPadding: 12
                            leftPadding: 10
                            font.bold: true
                            text: model.modelData.name
                        }
                        Text {
                            id: prDate
                            topPadding: 8
                            leftPadding: 10
                            anchors.top: name.bottom
                            text: model.modelData.prDate
                        }

                    }
                }
            }
        }

        //текст
        Pane {
            id: paneText
            height: getTextAreaHeight()
            width: getTextAreaWidth()
            visible: false

            ScrollView {
                anchors.fill: parent
                implicitHeight: getTextAreaHeight()
                implicitWidth: getTextAreaWidth()
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                clip: true

                Text {
                    id: textEdit
                    width: getTextAreaWidth() - 30
                    height: getTextAreaHeight()
                    wrapMode: Text.Wrap
                    font.pixelSize: 14

                    text: ""
                 }
             }

            background: Rectangle {
                height: parent.height
                width: parent.width

            }
        }
        //боковая панель
        Column {
            id:col
            spacing: 6
            height: getTextAreaHeight()
            Loader {
                id: paneActions
                width: 150
                source: "qrc:/actions/dictsActions.qml"
                visible: false
            }
         }
    }
}
