import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import FileWrap 1.0
import DictWrap 1.0

Page {
    height: window.height
    width: parent.width
    property string fileName: ""
    property string fPath: ""
    property bool _clicked: false

    function getTextAreaHeight() {
        return window.height - window.header.height - 25
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
    function getWindowHeight() {
        return window.height
    }
    function getWindowWidth() {
        return window.width
    }
    FileWrap {
        id: fileWrap
    }

    Row {
        x: 10
        y: 5
        spacing: 10

        //список файлов
        Pane {
            id: paneItems
            height: getTextAreaHeight()
            width: getTextAreaWidth()

            Label {
                id: labelFiles
                leftPadding: 4
                bottomPadding: 10
                font.pixelSize: 20
                font.bold: true

                text: "Файлы"

                visible: fileWrap.dataList.length === 0 ? false : true
            }


            //альтернативный заголовок
            Label {
                id: label
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Загрузите или выберите файл для отображения."
//                text: paneActions.visible
                visible: fileWrap.dataList.length === 0 ? true : false
            }

            ScrollView {
//                id: textEdit
//                anchors.fill: parent
                anchors.top: labelFiles.bottom
                implicitHeight: getTextAreaHeight() - label.height - 25
                implicitWidth: getTextAreaWidth()-10
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
//                ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                clip: true

                visible: fileWrap.dataList.length !== 0 ? true : false

                ListView {
                    id: listView
                    width: getTextAreaWidth()
                    height: getTextAreaHeight()
                    spacing: 10
                    highlight: highlight
                        highlightFollowsCurrentItem: false

                    model: fileWrap.dataList
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
                                textEdit.text = fileWrap.getFileContent(path.text);
                                paneItems.visible = false
                                paneText.visible = true
                                paneActions.source = "qrc:/actions/editTextActions.qml"
                            }
                            onHoveredChanged: {
                                if (mArea.containsMouse) {
                                    rect.color = "#a9a9aa"
                                } else {
                                    rect.color = "#ffffff"
                                }
                            }
                            onClicked: {
                                fileWrap.curFile = path.text
                                if (mouse.button === Qt.LeftButton) {
                                    paneAnalysis.visible = true
                                    fName.text = name.text
                                }
                                if (mouse.button === Qt.RightButton) {
                                    contextMenu.popup()
                                }
                            }
                            Menu {
                                id: contextMenu
                                Action {
                                    text: "Удалить"
                                    onTriggered: {
                                        fileWrap.deleteFile(path.text)
                                    }
                                }
                                Action {
                                    text: "Словарь"
                                    onTriggered: {
                                        fPath = path.text
                                        dictsList.open()
//                                        dictDialog.open()
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
                    //height: getTextAreaHeight()
                    wrapMode: TextEdit.Wrap
                    selectionColor: "#535353"
                    selectByMouse: true
                    persistentSelection: true
                    font.pixelSize: 14

                    text: ""

                    MouseArea {
                        width: parent.width
                        height: getTextAreaHeight()
                        //hoverEnabled: true
                        acceptedButtons: Qt.RightButton
                        onClicked: {
                            textContextMenu.popup()
                        }
                        Menu {
                            id: textContextMenu
                            MenuItem {
                                text: "Копировать"
                                onTriggered: {
                                    textEdit.copy()
                                }
                            }
                            MenuItem  {
                                text: "Вставить"
                                onTriggered: {
                                    textEdit.paste()
                                }
                            }
                        }
                    }
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
                source: "qrc:/actions/textActions.qml"
            }
            //анализ
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
                        model: fileWrap.params
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
                                text: model.modelData.lexWealth
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
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton
                    onClicked: {
                        console.log("clicked")
                        bigAnalyse.visible = true
                    }
                }
            }
        }
        //анализ в большом окне
        Popup {
            id: bigAnalyse
            height: 400
            width: 600
            closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
            visible: false
            parent: Overlay.overlay

            x: Math.round((parent.width - width) / 2)
            y: Math.round((parent.height - height) / 2)
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
                id: fNameBig
//                        anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width
                wrapMode: Label.Wrap
                font.bold: true
                font.pixelSize: 14
                bottomPadding: 5
                text: fName.text
            }

            ScrollView {
//                        anchors.fill: parent
                anchors.top: fNameBig.bottom
                contentWidth: parent.width
//                        contentWidth: parent.height - fName.height
//                        contentHeight: parent.height
                implicitHeight: parent.height - fNameBig.height
                height: parent.height - fNameBig.height
                implicitWidth: parent.width
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                clip: true

                ListView {
                    width: parent.width - 10
//                            height:
                    implicitHeight: 200
                    model: fileWrap.params
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
                            text: "Коэфф. лекс. богаства: " + model.modelData.uniqVol + " / √" +
                                  model.modelData.textVol + " = " + model.modelData.lexWealth
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
                            text: "Позиция: " + model.modelData.textVol + " / 1.618 = " +
                                  model.modelData.hc1Pos
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
                            id: hc2Big
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
                            text: "Позиция: " + model.modelData.textVol + " - " +
                                  model.modelData.textVol + " / 1.618 = " +
                                  model.modelData.hc2Pos
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

    DictWrap {
        id: dictWrap
    }

    Popup {
        id: dictsList
        parent: Overlay.overlay

        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        ScrollView {
//            anchors.fill: parent
            implicitHeight: 300
            implicitWidth: 300
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            clip: true
            Label {
                id: dictsListLabel
                bottomPadding: 8
                text: "Выберите словарь: "
            }

            ListView {
                id: dictListView
                anchors.top: dictsListLabel.bottom
                width: 300
                height: 250
                spacing: 10
                highlight: highlight
                highlightFollowsCurrentItem: false

                model: dictWrap.dataList
                delegate: Rectangle {
                    id: dictRect
                    width: 300
                    height: 45
                    radius: 3

                    MouseArea {
                        id: _mArea
                        anchors.fill: parent
                        hoverEnabled: true
                        acceptedButtons: Qt.LeftButton | Qt.RightButton
                        Row {
                            anchors.centerIn: parent
                            Column {
                                width: 215
                                Label {
                                    id: dictName
                                    topPadding: 10
                                    text: model.modelData.name
                                    font.pixelSize: 15
                                }
                            }
                            Column {
                                Button {
                                    height: 40
                                    text: qsTr("Выбрать")
                                    font.pixelSize: 12

                                    onClicked: {
                                        //здесь я передала назваие словаря и путь к файлу
                                        fileWrap.countByDict(dictName.text, fileWrap.curFile)
                                        dictOk.open()
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    Dialog {
        id: dictOk
        standardButtons: Dialog.Ok

        Label {
            text: "Подсчет вхождений завершен успешно."
        }
    }
}
