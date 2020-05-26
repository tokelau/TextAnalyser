import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import DictWrap 1.0

Page {
    height: window.height
    width: parent.width
    property string fileName: ""

    function getTextAreaHeight() {
        return window.height - window.header.height - 10
    }
    function getTextAreaWidth() {
        if (window.width >= 600) {
            return parent.width - paneActions.width - 30;
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

    DictWrap {
        id: dictWrap
    }

    Row {
        x: 10
        y: 5
        spacing: 10

        //словари
        Pane {
            id: paneItems
            height: getTextAreaHeight()
            width: getTextAreaWidth()

            Label {
                id: labelDicts
                leftPadding: 4
                bottomPadding: 10
                font.pixelSize: 20
                font.bold: true

                text: "Словари"

                visible: dictWrap.dataList.length === 0 ? false : true
            }

            //альтернативный заголовок
            Label {
                id: label
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Обработанных словарей пока нет."
                visible: dictWrap.dataList.length === 0 ? true : false
            }

            ScrollView {
                anchors.top: labelDicts.bottom
                implicitHeight: getTextAreaHeight() - labelDicts.height - 25
                implicitWidth: getTextAreaWidth() - 10
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                clip: true

                visible: dictWrap.dataList.length !== 0 ? true : false

                ListView {
                    id: listView
                    width: getTextAreaWidth()
                    height: getTextAreaHeight()
                    spacing: 10
                    highlight: highlight
                    highlightFollowsCurrentItem: false

                    model: dictWrap.dataList
                    delegate: Rectangle {
                        id: rect
                        implicitWidth: getTextAreaWidth() - 30
                        width: getTextAreaWidth() - 30
                        height: dictWrap.getButtonList(name.text).length !== 0 ? 105 : 70 //может, какую-то функцию другую сюда?
                        radius: 6

                        MouseArea {
                            id: mArea
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            onDoubleClicked: {
                                paneItems.visible = false
                                paneText.visible = true
                                paneActions.source = "qrc:/actions/editDictsActions.qml"
                                textEdit.text = dictWrap.getFileContent(name.text)
//                                console.log(dictWrap.curFile)
                            }
//                            onHoveredChanged: {
//                                if (mArea.containsMouse) {
//                                    rect.color = "#a9a9aa"
//                                } else {
//                                    rect.color = "#ffffff"
//                                }
//                            }
                            onClicked: {
                                dictWrap.curFile = name.text
//                                console.log(dictWrap.curFile)
                                if (mouse.button === Qt.RightButton) {
                                    contextMenu.popup()
                                }
                            }

                            Menu {
                                id: contextMenu
                                Action {
                                    text: "Удалить"
                                    onTriggered: {
                                        dictWrap.deleteDict(name.text)
                                    }
                                }

                            }
                        }
                        Label {
                            id: name
                            topPadding: 12
                            leftPadding: 15
                            font.bold: true
                            text: model.modelData.name

                        }
                        Text {
                            id: prDate
                            topPadding: 8
                            leftPadding: 15
                            bottomPadding: 8
                            anchors.top: name.bottom
                            text: model.modelData.prDate
                        }

                        //кнопки
                        ListView {
                            id: filesList
                            anchors.top: prDate.bottom
                            leftMargin: 15
                            width: parent.width - 50
                            height: 40
                            spacing: 8
                            highlight: highlight
                            highlightFollowsCurrentItem: false
                            orientation: Qt.Horizontal

                            model: dictWrap.getButtonList(name.text)
                            delegate: Rectangle {
                                id: dictRect
                                width: 110
                                height: 40
//                                radius: 3

                                Button {
                                    id: btn
                                    anchors.fill: parent
                                    anchors.centerIn: parent
                                    text: model.modelData.fName
                                    font.pixelSize: 10

                                    onClicked: {
                                        console.log(name.text + "/files/" + btn.text)
                                        paneItems.visible = false
                                        panePrText.visible = true
                                        paneActions.source = "qrc:/actions/editDictsActions.qml"
                                        console.log(dictWrap.getPrFileContent(name.text + "/files/" + btn.text))
                                        txt.text = dictWrap.getPrFileContent(name.text + "/files/" + btn.text)
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }

        //текст словаря
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

                TextEdit {
                    id: textEdit
                    width: getTextAreaWidth() - 30
                    //height: getTextAreaHeight()
                    wrapMode: TextEdit.Wrap
                    selectionColor: "#535353"
                    selectByMouse: true
                    persistentSelection: true
                    font.pixelSize: 14

                    text: ""
                 }
             }

            background: Rectangle {
                height: parent.height
                width: parent.width

            }
        }

        //текст обработанный
        Pane {
            id: panePrText
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
                    id: txt
                    width: getTextAreaWidth() - 30
                    //height: getTextAreaHeight()
                    wrapMode: Text.Wrap
                    font.pixelSize: 14

                    text: "123"
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
                visible: true
            }
         }
    }
}
