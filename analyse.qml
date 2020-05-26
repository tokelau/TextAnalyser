import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

//боковая панель
Page{
Column {
    id: analyse
    spacing: 6
    height: 600
        Pane {
            id: paneAnalysis
            anchors.centerIn: parent
            width: 600
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
                width: parent.width
                wrapMode: Label.Wrap
                font.bold: true
                font.pixelSize: 14
                bottomPadding: 5
            }

            ScrollView {
                anchors.top: fName.bottom
                contentWidth: parent.width
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
}
