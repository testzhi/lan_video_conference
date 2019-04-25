import QtQuick 2.0
import QtQuick.Controls 2.2
import Meeting 1.0

Item {
    anchors.fill: parent
    property var themes: []
    property var dates: []
    property var times: []
    property var category: []
    property var speakerID: []
    property var speakerName: []
    property var initiatorName: []
    property var initiatorID: []
    property Meeting met
    property Department dep
    property Group gro
    property Employee emp
    function initMeetingMessage() {
        console.log("meeting count  ", conferenceUI.employee.meetingCount())
        for (var i = 0; i !== conferenceUI.employee.meetingCount(); i++) {
            met = conferenceUI.employee.getMeeting(i)
            themes[i] = met.theme
            dates[i] = met.date
            times[i] = met.time
            category[i] = met.category
            speakerID[i] = met.speaker
            initiatorID[i] = met.initiator
        }
        for (var a = 0; a !== speakerID.length; a++) {

            for (var b = 0; b !== conferenceUI.employee.companys.departmentCount(
                     ); b++) {
                dep = conferenceUI.employee.companys.getDepartment(b)
                for (var c = 0; c !== dep.groupCount(); c++) {
                    gro = dep.getGroup(c)
                    for (var d = 0; d !== gro.conciseEmployeeCount(); d++) {
                        emp = gro.getConciseEmployee(d)
                    }
                }
            }
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
            if (type === "MeetingMessage") {
                initMeetingMessage()
                meetingLoader.sourceComponent = null
                meetingLoader.sourceComponent = meetingComponent
            }
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
                        text: {
                            var s = category === 0 ? "讨论会" : "分享会"
                            return themes[index] + s + "---" + dates[index] + "  " + times[index]
                                    + "  发起人: " + initiatorID[index] + "  主讲人：" + speakerID[index]
                        }
                    }
                }
            }
        }
    }
}
