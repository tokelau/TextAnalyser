import QtQuick 2.0
import QtQuick.Controls 2.4

Page {
    height: window.height
    width: column.width

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

            text: "амчапир"
         }
     }
}
