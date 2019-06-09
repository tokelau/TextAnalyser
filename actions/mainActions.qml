import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4

import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2

Pane {
//    id: paneActions
//    width: 150
    property string infoMessage: ""
    function info(message, flag) {
        informationText = message;
        if (flag === "O") {
            information.background.color = "#e0aa27"
        }
        if (flag === "G") {
            information.background.color = "#87b34d"
        }
        if (flag === "B") {
            information.background.color = "#5bc0de"
        }
        if (flag === "R") {
            information.background.color = "#bb2124"
        }
    }
    function validate(name) {
        if (name.length === 0) {
            infoMessage = "Введите название файла."
            return -1; //пустое название
        }
        name = name.split(".")
        //слишком много точек
        if (name.length > 2) {
            infoMessage = "Некорректное название файла. "
            return -2;
        } else if (name.length < 2) { //нет ни одной точки, без расширения
            infoMessage = "Необходимо указать расширение файла."
            return -4;
        }

        for(var i = 0; i < name[0].length; i++) {
            if (name[0][i] === "?" || name[0][i] === "\\" || name[0][i] === "/") {
                infoMessage = "Некорректное имя файла. Не должно содержать '?', '.', '\\', '/', '<', '>', '|', ':'."
                return -2; //некорректный символ в названиии файла
            } else if (name[0][i] === ":" || name[0][i] === "\"" || name[0][i] === "<") {
                infoMessage = "Некорректное имя файла. Не должно содержать '?', '.', '\\', '/', '<', '>', '|', ':'."
                return -2; //некорректный символ в названиии файла
            } else if (name[0][i] === ">" || name[0][i] === "|") {
                infoMessage = "Некорректное имя файла. Не должно содержать '?', '.', '\\', '/', '<', '>', '|', ':'."
                return -2; //некорректный символ в названиии файла
            }
        }
        if (name[1] !== "txt") {
            infoMessage = "Некорректное расширение файла. Необходим формат txt. "
            return -3; //некорректное расширение
        }
        return 0;
    }

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
            id: create
            text: qsTr("Создать новый")
            implicitWidth: 130

            background: Rectangle {
                width: 130
                color: getButtonColor(create)
                radius: 4

            }
            onClicked: {
                createFileDialog.open()
            }
        }

        Button {
            id: loadButton
            text: qsTr("Загрузить файл")
            implicitWidth: 130

            background: Rectangle {
                width: 130
                color: getButtonColor(loadButton)
                radius: 4

            }
            onClicked: {
                addFileDialog.open()
            }
        }
//        Button {
//            id: remove
//            text: qsTr("Удалить")
//            background: Rectangle {
//                width: 130
//                color: getButtonColor(remove)
//                radius: 4

//            }
//        }
    }

    FileDialog {
        id: addFileDialog
        title: "Выберите файл"
        folder: StandardPaths.standardLocations(StandardPaths.DocumentsLocation)[0]
        nameFilters: ["Текст (*.txt)"]
        onAccepted: {
//            console.log(addFileDialog.fileUrl)
            textEdit.text = textHandler.addFile(addFileDialog.fileUrl.toString());
        }
    }
    FolderDialog {
        id: createFileDialog
        title: "Выберите папку"
        folder: StandardPaths.standardLocations(StandardPaths.DocumentsLocation)[0]
        onAccepted: {
//            textEdit.text = textHandler.addFile(createFileDialog.currentFolder);
//            console.log(createFileDialog.currentFolder)
            dialogCreateName.open()

        }
    }

    Dialog {
        id: dialogCreateName
        standardButtons: Dialog.Ok | Dialog.Cancel
        Label {
            id: labelCreateName
            text: "Введите название файла:"
        }

        TextField {
            id: textField
            width: parent.width - 10
            anchors.top: labelCreateName.bottom
            wrapMode: TextField.Wrap
        }
        onAccepted: {
            if (validate(textField.text) === 0) {
//                info("Файл не создан. \n Пустое название файла", "R")
                if (textHandler.isFileCreated(createFileDialog.currentFolder, textField.text)) {
                    createInfoDialog.open()
                }
                else {
                    textEdit.text = textHandler.addFile(createFileDialog.currentFolder + "/" + textField.text )
                }
//                console.log(createFileDialog.currentFolder + "/" + textField.text)
            } else {
                infoDialog.open()
            }

//            info(validate(textField.text))
//            console.log(validate(textField.text))
        }
    }
    Dialog {
        id: createInfoDialog
        standardButtons: Dialog.Yes | Dialog.Cancel | Dialog.No
        Label {
            text: "Файл с этим именем уже есть в папке. \n" +
                  "Добавить его?"
        }
        onYes: {
            textEdit.text = textHandler.addFile(createFileDialog.currentFolder + "/" + textField.text )
        }
    }
    Dialog {
        id: infoDialog
        standardButtons: Dialog.Ok
        Label {
            text: infoMessage
        }
    }
}


