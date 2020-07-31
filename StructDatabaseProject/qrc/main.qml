import QtQuick 2.11
import QtQml 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 480
    title: qsTr("Stack")

    header: ToolBar {
        contentHeight: 20//toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: drawer.open()

        }

        Label {
            text: "kek"//stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Drawer {
        id: drawer
        width: window.width * 0.33
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Page 1")
                width: parent.width
                onClicked: {
                    stackView.currentIndex = 0;
                    drawer.close()
                }
            }
            ItemDelegate {
                text: qsTr("Page 2")
                width: parent.width
                onClicked: {
                    stackView.currentIndex = 1;
                    drawer.close()
                }
            }
        }
    }



    StackLayout {
        id: stackView
        anchors.fill: parent
        ListView {
            id: listView
            model: databaseModel

            delegate: Label {
                text: index + ": "
                      + date.toLocaleString(
                            Qt.locale("ru_RU"),
                            "HH:mm:ss.zzz"
                            )
                      + ": " + message
            }
            //anchors.fill: parent
        }
        EventDatabaseView {

        }
    }
}
