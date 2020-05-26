import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import DictWrap 1.0

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

    property string infoMessage: ""
    function validate(name) {
        if (name.length === 0) {
            infoMessage = "Не введено название файла."
            return -1; //пустое название
        }
        name = name.split(".")
        //слишком много точек
        if (name.length > 2) {
            infoMessage = "Некорректное название файла. "
            return -2;
        }

        for(var i = 0; i < name[0].length; i++) {
            if (name[0][i] === "?" || name[0][i] === "\\" || name[0][i] === "/") {
                infoMessage = "Некорректное имя файла. \nНе должно содержать '?', '.', '\\', '/', '<', '>', '|', ':'."
                return -2; //некорректный символ в названиии файла
            } else if (name[0][i] === ":" || name[0][i] === "\"" || name[0][i] === "<") {
                infoMessage = "Некорректное имя файла. Не должно содержать '?', '.', '\\', '/', '<', '>', '|', ':'."
                return -2; //некорректный символ в названиии файла
            } else if (name[0][i] === ">" || name[0][i] === "|") {
                infoMessage = "Некорректное имя файла. Не должно содержать '?', '.', '\\', '/', '<', '>', '|', ':'."
                return -2; //некорректный символ в названиии файла
            }
        }
//        if (name[1] !== "txt") {
//            infoMessage = "Некорректное расширение файла. Необходим формат txt. "
//            return -3; //некорректное расширение
//        }
        return 0;
    }
    function getName(path) {
        arr = path.split("/")
        return arr[arr.length - 1]
    }

    ColumnLayout {
        anchors.fill: parent
        width: parent.width
        Button {
            id: addDict
            text: qsTr("Создать")
            implicitWidth: 130

            background: Rectangle {
                width: 130
                color: getButtonColor(addDict)
                radius: 4

            }

            onClicked: {
                dialogCreateName.open()
            }
        }
        Button {
            id: loadDict
            text: qsTr("Загрузить")
            implicitWidth: 130

            background: Rectangle {
                width: 130
                color: getButtonColor(loadDict)
                radius: 4

            }

            onClicked: {
                loadDialog.open()
            }
        }
    }
    Dialog {
        id: dialogCreateName
        standardButtons: Dialog.Ok | Dialog.Cancel
        Label {
            id: labelCreateName
            text: "Введите название для нового словаря:"
        }

        TextField {
            id: textField
            width: parent.width - 10
            anchors.top: labelCreateName.bottom
            wrapMode: TextField.Wrap
        }
        onAccepted: {
            if (validate(textField.text) === 0) {
                console.log(textField.text)
//                dictWrap.addToDicts(textField.text.split(".")[0])
                if (dictWrap.isDictCreated(textField.text.split(".")[0])) {
                    console.log("creates")
                    addRepeatDialog.open()
                } else {
                    dictWrap.addToDicts(textField.text.split(".")[0])
                }
            } else {
                infoDialog.open()
            }
        }
    }
    Dialog {
        id: infoDialog
        standardButtons: Dialog.Ok
        Label {
            text: infoMessage
        }
    }
    FileDialog {
        id: loadDialog
        folder: shortcuts.desktop
        nameFilters: ["Txt files (*.txt)"]
        selectMultiple: false

        onAccepted: {
            if (dictWrap.isDictCreated(loadDialog.fileUrls)) {
                loadRepeatDialog.open()
            } else {
                dictWrap.addToDicts(loadDialog.fileUrls)
            }
            loadDialog.close()
        }
    }
    Dialog {
        id: addRepeatDialog
        standardButtons: Dialog.Yes | Dialog.Cancel | Dialog.No
        Label {
            text: "Словарь с этим именем уже существует. \n" +
                  "Перезаписать?"
        }
        onYes: {
            dictWrap.addToDicts(textField.text)
        }
    }
    Dialog {
        id: loadRepeatDialog
        standardButtons: Dialog.Yes | Dialog.Cancel | Dialog.No
        Label {
            text: "Словарь с этим именем уже существует. \n" +
                  "Перезаписать?"
        }
        onYes: {
            dictWrap.addToDicts(loadDialog.fileUrls)
        }
    }
}
