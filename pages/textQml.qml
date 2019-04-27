import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import TextHandler 1.0

Page {
    height: window.height
    width: parent.width
    property string fileName: ""
    property string fPath: ""

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

    TextHandler {
        id: textHandler
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
                text: "Загрузите или выберите файл для отображения."
                visible: textHandler.dataList.length === 0 ? true : false
            }

            ScrollView {
//                id: textEdit
                anchors.fill: parent
                implicitHeight: getTextAreaHeight()
                implicitWidth: getTextAreaWidth()
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                clip: true

                visible: textHandler.dataList.length !== 0 ? true : false

                ListView {
                    id: listView
                    width: getTextAreaWidth()
                    height: getTextAreaHeight()
                    spacing: 10
                    highlight: highlight
                        highlightFollowsCurrentItem: false

                    model: textHandler.dataList
                    delegate: Rectangle {
                        id: rect
                        width: getTextAreaWidth() - 30
                        height: 100
                        radius: 6

                        MouseArea {
                            id: mArea
                            anchors.fill: parent
                            hoverEnabled: true
                            acceptedButtons: Qt.LeftButton | Qt.RightButton
                            onDoubleClicked: {
                                textEdit.text = textHandler.getFileContent(path.text);
                                paneItems.visible = false
                                paneText.visible = true
                                paneActions.source = "qrc:/actions/textActions.qml"
                            }
                            onHoveredChanged: {
                                if (mArea.containsMouse) {
                                    rect.color = "#a9a9aa"
                                } else {
                                    rect.color = "#ffffff"
                                }
                            }
                            onClicked: {
                                if (mouse.button === Qt.LeftButton) {
                                    paneAnalysis.visible = true
                                    textHandler.curFile = path.text
                                    fName.text = name.text
                                }
                                if (mouse.button === Qt.RightButton) {
                                    contextMenu.popup()
                                }
                            }
                            Menu {
                                id: contextMenu
//                                Action {
//                                    text: "Скопировать"
//                                    onTriggered: {
//                                        console.log("copy")
//                                    }
//                                }
                                Action {
                                    text: "Удалить"
                                    onTriggered: {
                                        textHandler.deleteFile(path.text)
                                    }
                                }
                                Action {
                                    text: "Словарь"
                                    onTriggered: {
                                        fPath = path.text
                                        dictDialog.open()
                                    }
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
                            id: path
                            leftPadding: 10
                            topPadding: 8
                            anchors.top: name.bottom
                            text: model.modelData.path
                        }
                        Text {
                            id: prDate
                            topPadding: 8
                            leftPadding: 10
                            anchors.top: path.bottom
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

                TextEdit {
                    id: textEdit
                    width: getTextAreaWidth() - 30
                    height: getTextAreaHeight()
                    wrapMode: TextEdit.Wrap
                    selectionColor: "#535353"
                    selectByMouse: true
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
                source: "qrc:/actions/mainActions.qml"
            }
                Pane {
                    id: paneAnalysis
                    width: parent.width
                    height: 300
                    visible: false

                    background: Rectangle {
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
                    Label {
                        id: fName
//                        anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width
                        wrapMode: Label.Wrap
                        font.bold: true
                        font.pixelSize: 14
                        bottomPadding: 5
                    }

                    ScrollView {
//                        anchors.fill: parent
                        anchors.top: fName.bottom
                        contentWidth: parent.width
//                        contentWidth: parent.height - fName.height
//                        contentHeight: parent.height
                        implicitHeight: parent.height - fName.height
                        height: parent.height - fName.height
                        implicitWidth: parent.width
                        ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                        clip: true

                        ListView {
                            width: parent.width - 10
//                            height:
                            implicitHeight: 200
                            model: textHandler.params
                            delegate: Column {
//                                id: rect
                                width: parent.width - 10
//                                height: 100

                                Label {
//                                    id: uVolume
//                                    anchors.top: fName.bottom
                                    width: parent.width - 10
                                    wrapMode: Label.Wrap
                                    font.pixelSize: 11
                                    topPadding: 2
                                    text: "Словник: " + model.modelData.uniqVol
                                }

                                Label {
//                                    id: lWealth
//                                    anchors.top: uVolume.bottom
                                    width: parent.width - 10
                                    wrapMode: Label.Wrap
                //                    font.bold: true
                                    font.pixelSize: 11
                                    topPadding: 3
                                    text: "Коэфф. лекс. богаства: " + model.modelData.lexWealth
                                    bottomPadding: 5
                                }
                                Label {
//                                    id: hc1
//                                    anchors.top: lWealth.bottom
                                    width: parent.width -10
                                    wrapMode: Label.Wrap
                                    font.bold: true
                                    font.pixelSize: 12
                                    topPadding: 7
                                    bottomPadding: 3
                                    text: "ГЦ1:"
                                }
                                Label {
//                                    id: hc1Pos
//                                    anchors.top: hc1.bottom
                                    width: parent.width - 10
                                    wrapMode: Label.Wrap
                //                    font.bold: true
                                    font.pixelSize: 11
                //                    bottomPadding: 5
                                    text: "Позиция: " + model.modelData.hc1Pos
                                }
                                Label {
                                    width: parent.width
                                    wrapMode: Label.Wrap
                                    font.pixelSize: 11
                                    text: "Слово: " + model.modelData.hc1Word
                                }
                                Label {
                                    width: parent.width - 15
                                    wrapMode: Label.Wrap
                //                    font.bold: true
                                    font.pixelSize: 11
                //                    bottomPadding: 5
                                    text: "Предложение: " + model.modelData.hc1Sent
                                }

                                Label {
                                    id: hc2
//                                    anchors.top: hc1Sent.bottom
                                    width: parent.width
                                    wrapMode: Label.Wrap
                                    font.bold: true
                                    font.pixelSize: 12
                                    topPadding: 7
                                    bottomPadding: 3
                                    text: "ГЦ2"
                                }
                                Label {
                                    width: parent.width
                                    wrapMode: Label.Wrap
                //                    font.bold: true
                                    font.pixelSize: 11
                //                    bottomPadding: 5
                                    text: "Позиция: " + model.modelData.hc2Pos
                                }
                                Label {
                                    width: parent.width - 10
                                    wrapMode: Label.Wrap
                //                    font.bold: true
                                    font.pixelSize: 11
                //                    bottomPadding: 5
                                    text: "Слово: " + model.modelData.hc2Word
                                }
                                Label {
//                                    anchors.top: hc2Word.bottom
                                    width: parent.width - 15
                                    wrapMode: Label.Wrap
                //                    font.bold: true
                                    font.pixelSize: 11
                //                    bottomPadding: 5
                                    text: "Предложение: " + model.modelData.hc2Sent
                                }
                            }
                        }
                    }
                }
            }
////        }
    }
    FileDialog {
        id: dictDialog
        title: "Выберите словарь"
        nameFilters: ["Текст (*.txt)"]
        onAccepted: {
//            console.log(fPath)
            textHandler.countByDict(dictDialog.fileUrl.toString(), fPath)
            dictOk.open()
        }
    }
//            }
    Dialog {
        id: dictOk
        standardButtons: Dialog.Ok
        Label {
            text: "Действие успешно завершено."
        }
    }
}

