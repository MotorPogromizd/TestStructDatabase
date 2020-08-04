import QtQuick 2.11
import QtQml 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

GridLayout {
    columns: 2
    Label {
        text: "Запуски"
        padding: 6
    }
    Label {
        text: "События"
        padding: 6
    }

    ListView {
        id: activationsListView
        model: eventDatabase.activations

        delegate: AbstractButton {
            background: Rectangle {
                height: 1
                color: eventDatabase.currentActivation === index ? "green" : "lightgray"
                anchors.bottom: parent.bottom
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.left: parent.left
                anchors.right: parent.right
            }

//            implicitWidth: activationDelegateLabel.implicitWidth
            width: ListView.view.width
//            implicitHeight: activationDelegateLabel.implicitHeight
            padding: 6
            topPadding: 4
            bottomPadding: 4
            onClicked: {
                eventDatabase.selectActivation(index);
                console.log('clicked')
            }
            contentItem: ColumnLayout {
                Label {
                    id: activationDelegateLabel
                    text: enableTime.toLocaleString(
                              Qt.locale("ru_RU"),
                              "dd/MM/yyyy HH:mm:ss.zzz"
                              )
                          + " - "
                          + disableTime.toLocaleString(
                              Qt.locale("ru_RU"),
                              "dd/MM/yyyy HH:mm:ss.zzz"
                              )
                }
                Label {
                    id: captionLabel
                    text: "" + index + " | "
                          + activationId
                    color: "gray"
                    font.pointSize: 10
                }

            }

        }
        Layout.fillHeight: true
        Layout.fillWidth: true
    }

    ListView {
        id: dataListView
        model: eventDatabase.data
        delegate: Pane {

            background: Rectangle {
                height: 1
                color: "lightgray"
                anchors.bottom: parent.bottom
                anchors.leftMargin: 4
                anchors.rightMargin: 4
                anchors.left: parent.left
                anchors.right: parent.right
            }
            width: ListView.view.width
            Label {
                id: eventDelegateLabel
                text: index + ": " + "rowId: " + rowId + " / "
                      + number
                      + ": " + message
            }

        }
        Layout.fillHeight: true
        Layout.fillWidth: true
//        anchors {
//            right: parent.right
//            top: parent.top
//            bottom: parent.bottom
//            left: parent.horizontalCenter
//        }
        //anchors.fill: parent
    }
}
