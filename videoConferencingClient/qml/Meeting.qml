import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.12
import Meeting 1.0

Item {
    id: meeting
    signal meetingBack
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

    Rectangle {
        width: 20
        height: 20
        anchors.top: parent.top
        anchors.right: parent.right
        Image {
            id: back
            source: "../resources/1.png"
            anchors.fill: parent
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    meetingBack()
                }
            }
        }
    }
    Rectangle {
        width: 20
        height: 20
        anchors.top: parent.top
        anchors.right: parent.right
        z: 1
        Image {
            id: changeScreen
            property string screenType: "0"
            source: "../resources/1.png"
            anchors.fill: parent
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (changeScreen.screenType === "0") {
                        xvideoCamera.pausePlay()
                        xvideoScreen.startPlay()
                        changeScreen.screenType = "1"
                    } else {
                        xvideoCamera.startPlay()
                        xvideoScreen.pausePlay()
                        changeScreen.screenType = "0"
                    }
                }
            }
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
                                            source: "../resources/xly.png"
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

            Rectangle {

                width: parent.width
                height: parent.height / 2 - 1
                //                border.width: 1
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
            Connections {
                target: conferenceUI.employee
                //                property Attendee att
                onLoginSucceeded: {
                    if (type === "BeginMeeting") {
                        console.log("begin meeting")
                        meeting.att = conferenceUI.employee.getAttendee(0)
                        //                        att.camera("./")
                        console.log("xvideo width height", meetingScreen.width,
                                    meetingScreen.height)
                        xvideoScreen.setScale("2.5")
                        xvideoCamera.setScale("2.5")
                        //                        xvideoScreen.startPlay()
                        xvideoCamera.startPlay()
                    } else if (type === "Exit") {
                        xvideoScreen.pausePlay()
                        xvideoCamera.pausePlay()
                        //                        if (changeScreen.screenType === "0") {
                        //                            xvideoCamera.pausePlay()
                        //                        } else {
                        //                            xvideoScreen.pausePlay()
                        //                        }
                    }
                }
            }
        }
    }
}
