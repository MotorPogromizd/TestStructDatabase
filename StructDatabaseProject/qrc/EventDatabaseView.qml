import QtQuick 2.11
import QtQml 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

Item {
    ListView {
        id: activationsListView
        model: eventDatabase.activations

        delegate: Rectangle {
            border.color: "red"
            implicitWidth: activationDelegateLabel.implicitWidth
            width: ListView.view.width
            implicitHeight: activationDelegateLabel.implicitHeight
            Label {
                id: activationDelegateLabel
                text: "" + index + "| "
                      + enableTime.toLocaleString(
                          Qt.locale("ru_RU"),
                          "dd/MM/yyyy HH:mm:ss.zzz"
                          )
                      + " - "
                      + disableTime.toLocaleString(
                          Qt.locale("ru_RU"),
                          "dd/MM/yyyy HH:mm:ss.zzz"
                          )
                      + ": " + activationId
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    eventDatabase.selectActivation(index);
                }
            }
        }
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
            right: parent.horizontalCenter
        }
    }

    ListView {
        id: dataListView
        model: eventDatabase.data
        delegate: Rectangle {
            border.color: "green"
            implicitWidth: eventDelegateLabel.implicitWidth
            width: ListView.view.width
            implicitHeight: eventDelegateLabel.implicitHeight
            Label {
                id: eventDelegateLabel
                text: index + ": " + "rowId: " + rowId + " / "
                      + number
                      + ": " + message
            }

        }
        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            left: parent.horizontalCenter
        }
        //anchors.fill: parent
    }
}
