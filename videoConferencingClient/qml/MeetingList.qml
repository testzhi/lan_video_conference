import QtQuick 2.0
import QtQuick.Controls 2.2
import Meeting 1.0

Item {
    anchors.fill: parent
    property string currentMeeting: ""
    signal beginMeeting(var index)
    signal attendMeeting(var index)
    signal recordMeeting(var index)
    signal comeBackMeeting
    property var themes: []
    property var dates: []
    property var times: []
    property var category: []
    property var speakerID: []
    property var speakerName: []
    property var initiatorName: []
    property var initiatorID: []
    property var meetingState: []
    property var meetingID: []
    property var currentEmployeeID
    property Meeting met
    property Department dep
    property Group gro
    property ConciseEmployee emp
    function initMeetingMessage() {
        while (themes.length !== 0) {
            themes.pop()
            dates.pop()
            times.pop()
            category.pop()
            speakerID.pop()
            speakerName.pop()
            initiatorID.pop()
            initiatorName.pop()
            meetingState.pop()
            meetingID.pop()
        }
        currentEmployeeID = conferenceUI.employee.userID
        console.log("meeting count  ", conferenceUI.employee.meetingCount())
        for (var i = 0; i !== conferenceUI.employee.meetingCount(); i++) {
            console.log("current index  ", i)
            met = conferenceUI.employee.getMeeting(i)
            console.log(met.theme, "  ", met.date, "  ", met.time, "  ",
                        met.category, "  ", met.speaker, "  ",
                        met.initiator, "  ", met.state)

            themes[i] = met.theme
            dates[i] = met.date
            times[i] = met.time
            category[i] = met.category
            speakerID[i] = met.speaker
            initiatorID[i] = met.initiator
            meetingState[i] = met.state
            meetingID[i] = met.meetingID
        }
    }

    Loader {
        id: meetingLoader
        anchors.fill: parent
    }
    Connections {
        target: conferenceUI.employee
        onLoginSucceeded: {
            //            console.log(type)
            if (type === "MeetingMessage") {
                console.log("refresh meeting list")
                initMeetingMessage()
                meetingLoader.sourceComponent = null
                meetingLoader.sourceComponent = meetingComponent
            } else if (type === "RefreshMeetingID") {
                console.log("refresh meetingID")
                for (var i = 0; i !== conferenceUI.employee.meetingCount(
                         ); i++) {
                    met = conferenceUI.employee.getMeeting(i)
                    if (meetingID[i] !== met.meetingID) {
                        meetingID[i] = met.meetingID
                    }
                }
            }
        }
    }

    Component {
        id: meetingComponent
        ScrollView {
            anchors.fill: parent
            ListView {
                model: dates.length
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
                            var s = category === 0 ? "分享会" : "讨论会"
                            return themes[index] + s + "---" + dates[index] + "  " + times[index]
                                    + "  发起人: " + initiatorID[index] + "  主讲人：" + speakerID[index]
                        }
                    }
                    Row {
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        Button {
                            text: "开始会议"
                            visible: (currentEmployeeID === initiatorID[index]
                                      || currentEmployeeID === speakerID[index])
                                     && meetingState[index] === "0"
                            && currentMeeting !== meetingID[index]
                            onClicked: {
                                beginMeeting(index)
                                conferenceUI.getStartMeetingMessage(
                                            meetingID[index])
                                meetingList.currentMeeting = meetingID[index]
                            }
                        }
                        Button {
                            visible: currentMeeting === meetingID[index]
                            text: "回到会议"
                            onClicked: {
                                comeBackMeeting()
                            }
                        }

                        Button {
                            visible: meetingState[index] === "1"
                                     && currentMeeting !== meetingID[index]
                            text: "加入会议"
                            onClicked: {
                                attendMeeting(index)
                                conferenceUI.getAttendMeetingMessage(
                                            meetingID[index])
                            }
                        }
                        Button {
                            text: "记载会议"
                            visible: meetingState[index] === "2"
                                     && currentMeeting !== meetingID[index]
                                     && initiatorID[index] === currentEmployeeID
                            onClicked: {
                                recordMeeting(index)
                            }
                        }
                    }
                }
            }
        }
    }
}
