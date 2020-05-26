import QtQuick 2.0
import QtQuick.Controls 2.4

Page {
    height: window.height
    width: column.width
    ToolBar {
        id: header
        width: parent.width
//                parent: window.overlay

        Label {
            id: label
            anchors.centerIn: parent
            text: "Информация"
        }
    }

    Label {
        text: "Извините, страница находится в разработке"
        anchors.centerIn: parent
    }
}
