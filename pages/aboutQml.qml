import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import FileWrap 1.0

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
            return parent.width - 30;
        }
        return column.width - 20;
    }

    FileWrap {
        id: fileWrap
    }

    Row {
        x: 10
        y: 5
        spacing: 10

        //текст
        Pane {
            id: paneText
            height: getTextAreaHeight()
            width: getTextAreaWidth()

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
                    textFormat: Text.StyledText
                    font.pixelSize: 14

                    text: fileWrap.getAboutContent()
                 }
             }

        }
    }
}



