import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.3

ApplicationWindow {
    id: window
    visible: true
    width: 900
    height: 600
    minimumWidth: 900
    minimumHeight: 600
    maximumHeight: 900
    maximumWidth: 600
    title: qsTr("Text analyser")

    readonly property bool inPortrait: window.width < 600
    property bool dVisible: true

    function push_page(source) {
        loader.source = source;
    }


    Action {
        id: action
        onTriggered: drawer.visible ? drawer.close() : drawer.open()
    }
    header: ToolBar {
        height: 40
        leftPadding: 5
        ToolButton {
            anchors.verticalCenter: parent.verticalCenter
            action: action
            icon.source: "qrc:/icons/icons8-menu-24.png"
        }

        Label {
            anchors.centerIn: parent
//            text: "Информация"
        }

    }

    Drawer {
        id: drawer
        width: 70
        height: window.height

        modal: false
        interactive: inPortrait
        visible: !inPortrait
        background: Rectangle {
            height: parent.height
            width: parent.width
            color: "#f6f6f6"
        }
        ListModel {
            id: menuItem
            ListElement {
                name: "Файлы"
                source: "qrc:/pages/textQml.qml"
                iconSource: "qrc:/icons/icons8-file-24.png"
            }
            ListElement {
                name: "Словари"
                source: "qrc:/pages/dictQml.qml"
                iconSource: "qrc:/icons/icons8-news-24.png"
            }
//            ListElement {
//                name: "Медиа"
//                source: "qrc:/pages/mediaQml.qml"
//                iconSource: "qrc:/icons/icons8-music-24.png"
//            }
            ListElement {
                name: "Справка"
                source: "qrc:/pages/aboutQml.qml"
                iconSource: "qrc:/icons/icons8-bookmark-24.png"
            }
//            ListElement {
//                name: "Настройки"
//                source: "qrc:/pages/settingsQml.qml"
//                iconSource: "qrc:/icons/icons8-services-24.png"
//            }

        }

        ListView {
            anchors.fill: parent
            model: menuItem
            delegate: ItemDelegate {
                width: parent.width
                Column {
                    anchors.centerIn: parent
                    topPadding: 5
                    bottomPadding: 5
                    Image {
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: iconSource
                    }
                    Text {
                        anchors.horizontalCenter: parent.horizontalCenter
                        topPadding: 3
                        text: name
                    }
                }

                onClicked: push_page(source)

            }

            ScrollIndicator.vertical: ScrollIndicator { }
         }
    }

    Column {
        id: column
        anchors.fill: parent
        anchors.leftMargin: !inPortrait ? drawer.width : undefined

        Loader {
            id: loader
            width: parent.width
            source: "qrc:/pages/textQml.qml"
        }
    }
}
