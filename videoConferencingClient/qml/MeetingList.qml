import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    anchors.fill: parent
    ScrollView {
        anchors.fill: parent
        ListView {
            model: conferenceUI.employee.meetingCount()
            spacing: 0.1
            delegate: Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                border.width: 0.5
                //                border.color: "blue"
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: conferenceUI.employee.getMeeting(
                              index).theme + "(" + conferenceUI.employee.getMeeting(
                              index).date + "  " + conferenceUI.employee.getMeeting(
                              index).time + ")"
                }
            }
        }
    }
}
