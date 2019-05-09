import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.12
import QtQuick.Dialogs 1.2
import Meeting 1.0

Item {
    id: meeting
    signal meetingBack
    signal meetingExit
    property var meetingNotifications: []
    property string currentMeetingID: ""
    property real currentExitAttendeeNum: 0
    property var attendeeRealName: []
    property var attendeeID: []
    property var attendeeAvatar: []
    property var attendeeJurisdiction: []
    property var attendeeState: []
    property Attendee att

    function initAttendeeMessage() {
        for (var i = 0; i !== conferenceUI.employee.attendeeCount(); i++) {
            att = conferenceUI.employee.getAttendee(i)
            attendeeRealName.push(att.realName)
            attendeeID.push(att.userID)
            attendeeAvatar.push(att.avatar)
            attendeeJurisdiction.push(att.jurisdiction)
            attendeeState.push("true")
        }
    }
    function addAttendee() {
        att = conferenceUI.employee.getAttendee(
                    conferenceUI.employee.attendeeCount() - 1)
        attendeeRealName[attendeeRealName.length] = att.realName
        attendeeAvatar[attendeeAvatar.length] = att.avatar
        attendeeID[attendeeID.length] = att.userID
        attendeeJurisdiction[attendeeJurisdiction.length] = att.jurisdiction
        attendeeState[attendeeState.length] = "true"
    }
    function refreshAttendeeState() {
        var currentExitAttendee = 0
        for (var i = 0; i !== conferenceUI.employee.attendeeCount(); i++) {
            att = conferenceUI.employee.getAttendee(i)
            while (attendeeID[i + currentExitAttendee] !== att.userID) {
                console.log("employee not exit ID  ",
                            attendeeID[i + currentExitAttendee])
                currentExitAttendee += 1
                attendeeState[i + currentExitAttendee] = "false"
            }
        }
    }
    function clearAttendeeMessage() {
        while (attendeeRealName.length !== 0) {
            attendeeRealName.pop()
            attendeeID.pop()
            attendeeAvatar.pop()
            attendeeJurisdiction.pop()
            attendeeState.pop()
        }
    }

    Row {
        anchors.fill: parent
        Column {
            width: parent.width * 0.2
            height: parent.height
            Rectangle {
                width: parent.width
                height: parent.height / 2
                //                border.width: 1
                Loader {
                    id: currentMeetingAttendeeLoader
                    anchors.fill: parent
                    //                    sourceComponent: currentMeetingAttendeeComponent
                }
                Connections {
                    target: conferenceUI.employee
                    onLoginSucceeded: {
                        if (type === "AttendeeMessage") {
                            console.log("ssattendee message")
                            initAttendeeMessage()
                            currentMeetingAttendeeLoader.sourceComponent = null
                            currentMeetingAttendeeLoader.sourceComponent
                                    = currentMeetingAttendeeComponent
                        } else if (type === "AddAttendeeMessage") {
                            console.log("add attendee message")
                            addAttendee()
                            currentMeetingAttendeeLoader.sourceComponent = null
                            currentMeetingAttendeeLoader.sourceComponent
                                    = currentMeetingAttendeeComponent
                        } else if (type === "RefreshAttendeeState") {
                            console.log("refresh attendee state")
                            refreshAttendeeState()
                            currentMeetingAttendeeLoader.sourceComponent = null
                            currentMeetingAttendeeLoader.sourceComponent
                                    = currentMeetingAttendeeComponent
                            currentExitAttendeeNum += 1
                        }
                    }
                }

                Component {
                    id: currentMeetingAttendeeComponent
                    ScrollView {
                        id: attendeesScroll
                        property real exitAttendee: 0
                        anchors.fill: parent
                        ListView {
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            model: attendeeID.length - currentExitAttendeeNum
                            delegate: Rectangle {
                                width: meeting.width * 0.2
                                height: meeting.height * 0.06
                                //                                border.width: 1
                                Row {
                                    anchors.fill: parent
                                    spacing: 10
                                    Rectangle {
                                        id: img
                                        width: mainWindow.height * 0.03 - 5
                                        height: mainWindow.height * 0.03
                                        anchors.verticalCenter: parent.verticalCenter

                                        Image {
                                            id: _image
                                            smooth: true
                                            visible: false
                                            anchors.fill: parent
                                            source: "../resources/avatar.jpg"
                                            antialiasing: true
                                        }
                                        Rectangle {
                                            id: _mask
                                            color: "black"
                                            anchors.fill: parent
                                            radius: width / 2
                                            visible: false
                                            antialiasing: true
                                            smooth: true
                                        }
                                        OpacityMask {
                                            id: mask_image
                                            anchors.fill: _image
                                            source: _image
                                            maskSource: _mask
                                            visible: true
                                            antialiasing: true
                                        }
                                    }
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: {
                                            while (attendeeState[index + attendeesScroll.exitAttendee] === "false") {
                                                attendeesScroll.exitAttendee += 1
                                            }

                                            attendeeRealName[index + attendeesScroll.exitAttendee]
                                        }
                                    } //text
                                }
                            }
                        }
                    }
                }
            }
            Rectangle {
                width: parent.width
                height: 1
                color: "blue"
            }

            Rectangle {
                width: parent.width
                height: parent.height / 2 - 1
                Loader {
                    id: meetingNotificationLoader
                    anchors.fill: parent
                }
                Connections {
                    target: conferenceUI.employee
                    onRegisterSuccessfully: {
                        if (message !== "RegisterSuccess") {
                            console.log(message)
                            meeting.meetingNotifications[meeting.meetingNotifications.length]
                                    = message
                            meetingNotificationLoader.sourceComponent = null
                            meetingNotificationLoader.sourceComponent = meetingNotificationComponent
                        }
                    }
                }

                Component {
                    id: meetingNotificationComponent
                    ScrollView {
                        anchors.fill: parent
                        ListView {
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            model: meeting.meetingNotifications.length
                            delegate: Rectangle {
                                width: meeting.width * 0.2 - 5
                                height: meeting.height * 0.04
                                Text {
                                    anchors.verticalCenter: parent.verticalCenter
                                    text: meeting.meetingNotifications[index]
                                }
                            }
                        }
                    }
                }
            }
        }
        Rectangle {
            id: meetingScreen
            width: parent.width * 0.8
            height: parent.height
            border.width: 1
            XScreen {
                id: xvideoScreen
                //                visible: false
                anchors.fill: parent
                anchors.centerIn: parent
            }
            XVideo {
                id: xvideoCamera
                anchors.fill: parent
                anchors.centerIn: parent
            }
            XRecv {
                id:xRecv
                anchors.fill: parent
                anchors.centerIn: parent
            }
            XAudio{
                id:xaudio
            }

            Item {
                z: 1
                width: 40
                height: 40
                anchors.top: parent.top
                anchors.left: parent.left
                Image {
                    id: back
                    source: "../resources/back.png"
                    anchors.fill: parent
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            meetingBack()
                        }
                    }
                }
            }
            Switch {
                id: screenSwitch
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                z: 1
                checked: true
                visible: false
                onClicked: {
                    if (checked === false) {
                        xvideoCamera.pausePlay()
                        xvideoScreen.startPlay()
                    } else {
                        xvideoCamera.startPlay()
                        xvideoScreen.pausePlay()
                    }
                }
            }
            Item {
                id: meetingEnd
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                width: 60
                height: 40

                Image {
                    anchors.fill: parent
                    source: "../resources/closeMeeting.png"
                }
                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        meetingEnd.opacity = 0.5
                    }
                    onReleased: {
                        meetingEnd.opacity = 1
                    }
                    onClicked: {
                        xvideoScreen.pausePlay()
                        xvideoCamera.pausePlay()
                        xaudio.pausePlay()
                        xRecv.pausePlay()
                        screenSwitch.visible = false
                        while (meeting.meetingNotifications.length !== 0)
                            meeting.meetingNotifications.pop()
                        clearAttendeeMessage()
                        meetingExit()
                        conferenceUI.getStopMeetingMessage(currentMeetingID)
                        meetingList.currentMeeting = ""
                    }
                }
            }
            Item {
                id: voice
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 30
                width: 40
                height: 40
                Image {
                    anchors.fill: parent
                    source: "../resources/voiceClose.png"
                }
                MouseArea {
                    anchors.fill: parent
                    onPressed: {
                        voice.opacity = 0.5
                    }
                    onReleased: {
                        voice.opacity = 1
                    }
                }
            }
            MessageDialog {
                id: messageDialog
                title: "提醒"
                text: "该会议已结束."
                onAccepted: {
                    console.log("And of course you could only agree.")
                    xvideoScreen.pausePlay()
                    xvideoCamera.pausePlay()
                    xaudio.pausePlay()
                    xRecv.pausePlay()
                    meetingExit()
                    meetingList.currentMeeting = ""
                    screenSwitch.visible = false
                    while (meeting.meetingNotifications.length !== 0)
                        meeting.meetingNotifications.pop()
                    clearAttendeeMessage()
                    //                    Qt.quit()
                    meetingExit()
                }
                Component.onCompleted: visible = false
            }
        }
    }
    Connections {
        id: meetingConnect
        target: conferenceUI.employee
        property Meeting mee
        onLoginSucceeded: {
            if (type === "StartVideo") {
                console.log("start video")
                console.log(meetingScreen.width,"  ",meetingScreen.height)
                //xvideoScreen.setScale("2.4")
                //xvideoCamera.setScale("2.4")
                xvideoScreen.setScale("1.7")
                xvideoCamera.setScale("1.7")
                xvideoScreen.pausePlay()
                xvideoCamera.pausePlay()
                xaudio.pausePlay()
                conferenceUI.getStartVideoMessage(currentMeetingID)
                xvideoCamera.startPlay()
                xaudio.startPlay()
                screenSwitch.visible = true
            }
            else if(type === "StartRecv") {
                console.log("start recv")
                xRecv.setScale("1.7")
                xRecv.pausePlay()
                xRecv.startPlay()
            }
            else if (type === "Exit") {
                xvideoScreen.pausePlay()
                xvideoCamera.pausePlay()
                xaudio.pausePlay()
                xRecv.pausePlay()
            } else if (type === "MeetingEnd") {
                if (meeting.visible === true)
                    messageDialog.visible = true
            }
        }
    }
}
