import QtQuick 2.0
import QtQuick.Controls 2.2
import Meeting 1.0

Item {
    anchors.fill: parent
    property var themes: []
    property var dates: []
    property var times: []
    property Meeting met
    function initMeetingMessage() {
        console.log("meeting count  ", conferenceUI.employee.meetingCount())
        for (var i = 0; i !== conferenceUI.employee.meetingCount(); i++) {
            met = conferenceUI.employee.getMeeting(i)
            themes[i] = met.theme
            dates[i] = met.date
            times[i] = met.time
        }
        console.log("Meeting counts  ", themes.length)
    }

    Loader {
        id: meetingLoader
        anchors.fill: parent
    }
    Connections {
        target: conferenceUI.employee
        onLoginSucceeded: {
            initMeetingMessage()
            meetingLoader.sourceComponent = null
            meetingLoader.sourceComponent = meetingComponent
        }
    }

    Component {
        id: meetingComponent
        ScrollView {
            anchors.fill: parent
            ListView {
                model: themes.length
                spacing: 0.1
                delegate: Rectangle {
                    width: mainWindow.width * 0.85
                    height: mainWindow.height * 0.10
                    border.width: 0.5
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: mainWindow.width * 0.01
                        text: themes[index] + "(" + dates[index] + "  " + times[index] + ")"
                    }
                }
            }
        }
    }
}
