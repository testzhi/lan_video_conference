import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    anchors.fill: parent
    ScrollView {
        anchors.fill: parent
        ListView {
            model: employee.meetingCount()
            delegate: Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                border.width: 1
                border.color: "blue"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: employee.getMeeting(index).theme
                    font.pixelSize: 15
                }
            }
        }
    }
}
