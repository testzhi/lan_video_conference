import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.12
import QtQuick.Dialogs 1.2
import Meeting 1.0

Item {
    id: meeting
    signal meetingBack()
    signal meetingExit()
    property var meetingNotifications: []
    property string currentMeetingID: ""
    property var attendeeRealName: []
    property var attendeeID: []
    property var attendeeAvatar: []
    property var attendeeJurisdiction: []
    property Attendee att
    function initAttendeeMessage() {
        for (var i = 0; i !== conferenceUI.employee.attendeeCount(); i++) {
            att = conferenceUI.employee.getAttendee(i)
            attendeeRealName[i] = att.realName
            attendeeID[i] = att.userID
            attendeeAvatar[i] = att.avatar
            attendeeJurisdiction[i] = att.jurisdiction
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
                        }
                    }
                }

                Component {
                    id: currentMeetingAttendeeComponent
                    ScrollView {
                        anchors.fill: parent
                        ListView {

                            model: attendeeID.length
                            delegate: Rectangle {
                                width: meeting.width * 0.2
                                height: meeting.height * 0.08
                                //                                border.width: 1
                                Row {
                                    anchors.fill: parent
                                    spacing: 10
                                    Rectangle {
                                        id: img
                                        width: mainWindow.height * 0.03
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
                                        text: attendeeRealName[index]
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

            Loader {
                id:meetingNotificationLoader
                width: parent.width
                height: parent.height / 2 - 1
            }
            Connections {
                target: conferenceUI.employee
                onRegisterSuccessfully:{
                    if (message !== "RegisterSuccess") {
                        meeting.meetingNotifications[meeting.meetingNotifications.length] = message
                        meetingNotificationLoader.sourceComponent = null
                        meetingNotificationLoader.sourceComponent = meetingNotificationComponent
                    }
                }
            }

            Component {
                id: meetingNotificationComponent
                Rectangle {
                    width: parent.width
                    height: parent.height / 2 - 1
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
                        screenSwitch.visible = false
                        while(meeting.meetingNotifications.length !== 0)
                            meeting.meetingNotifications.pop()
                        meetingExit()
                        conferenceUI.getStopMeetingMessage(
                                    meetingList.currentMeeting)
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
                    meetingExit()
//                    meetingList.currentMeeting = ""
                    screenSwitch.visible = false
                    while(meeting.meetingNotifications.length !== 0)
                        meeting.meetingNotifications.pop()
                    Qt.quit()
                }
                Component.onCompleted: visible = false
            }

            Connections {
                id: meetingConnect
                target: conferenceUI.employee
                property Meeting mee
                onLoginSucceeded: {
                    if (type === "BeginMeeting") {
                        console.log("begin meeting")
                        for (var i = 0; i !== conferenceUI.employee.meetingCount(
                                 ); i++) {
                            meetingConnect.mee = conferenceUI.employee.getMeeting(
                                        i)
                            console.log("meetingID  + currentMeetingID  ",
                                        meetingConnect.mee.meetingID, "  s  ",
                                        meeting.currentMeetingID)
                            if (meetingConnect.mee.meetingID === meeting.currentMeetingID) {
                                console.log("speaker + userID",
                                            meetingConnect.mee.speaker, "  ",
                                            conferenceUI.employee.userID)
                                if (conferenceUI.employee.userID === meetingConnect.mee.speaker) {
                                    xvideoScreen.setScale("2.4")
                                    xvideoCamera.setScale("2.4")
                                    xvideoCamera.startPlay()
                                    screenSwitch.visible = true
                                }
                            }
                        }
                    } else if (type === "Exit") {
                        xvideoScreen.pausePlay()
                        xvideoCamera.pausePlay()
                    } else if (type === "MeetingEnd") {
                        messageDialog.visible = true
                    }
                }
                onAddAttendeeMessage: {
                    console.log(message)
                }
            }
        }
    }
}
