import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.12
import Meeting 1.0

Item {
    anchors.fill: parent
    signal exit
    property var newMessage: [false, false, false, false]
    property real currentChooseMeeting: -1
    property Meeting mee
    onCurrentChooseMeetingChanged: {
        meeting.currentMeetingID = currentChooseMeeting
    }

    Column {
        id: mainPage
        anchors.fill: parent
        Rectangle {
            height: mainWindow.height * 0.12
            width: mainWindow.width
            z: 1
            Image {
                id: background
                anchors.fill: parent
                source: "../resources/background2.jpg"
            }
            Row {
                anchors.fill: parent
                anchors.left: parent.left
                anchors.leftMargin: mainWindow.width * 0.03
                spacing: mainWindow.width * 0.03
                Item {
                    id: img
                    width: mainWindow.height * 0.07
                    height: mainWindow.height * 0.07
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
                    text: conferenceUI.employee.realName
                    //                    font.pixelSize: 25
                }
            }

            Item {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: 40
                height: 40
                Image {
                    //                    id: exit
                    anchors.fill: parent
                    source: "../resources/exit.ico"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        conferenceUI.getExitMessage()
                        exit()
                    }
                }
            }
        }
        Rectangle {
            width: mainWindow.width
            height: 1
            color: "blue"
        }
        MyMeeting {
            id: meeting
            height: mainWindow.height * 0.88
            width: parent.width
            visible: false
            onMeetingBack: {
                employeeMessage.visible = true
                meeting.visible = false
            }
            onMeetingExit: {
                employeeMessage.visible = true
                meeting.visible = false
                meetingList.currentMeeting = ""
            }
        }
        Row {
            id: employeeMessage
            visible: true
            Loader {
                id: buttonListLoader
                height: mainWindow.height * 0.88
                width: mainWindow.width * 0.15
                sourceComponent: buttonListComponent
            }
            Connections {
                target: conferenceUI.employee
                onLoginSucceeded: {
                    if (type === "MeetingListRefresh") {
                        home.newMessage[0] = true
                    } else if (type === "NotificationListRefresh") {
                        home.newMessage[2] = true
                    }
                    buttonListLoader.sourceComponent = null
                    buttonListLoader.sourceComponent = buttonListComponent
                }
            }

            Component {
                id: buttonListComponent
                Rectangle {
                    height: mainWindow.height * 0.88
                    width: mainWindow.width * 0.15
                    color: "white"
                    Column {
                        id: tabbarColumn
                        anchors.fill: parent
                        spacing: parent.height * 0.05
                        Repeater {
                            model: ["会议列表", "会议发布", "通知", "个人资料"]
                            Button {
                                width: tabbarColumn.width
                                height: tabbarColumn.height * 0.85 / 4
                                Text {
                                    text: qsTr(modelData)
                                    //                                font.pointSize: 50
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                                Rectangle {
                                    width: 10
                                    height: 10
                                    radius: width / 2
                                    color: "red"
                                    anchors.right: parent.right
                                    anchors.rightMargin: 10
                                    //                                anchors.top: parent.top
                                    //                                anchors.topMargin: 10
                                    anchors.verticalCenter: parent.verticalCenter
                                    visible: newMessage[index]
                                }

                                onClicked: {
                                    if (index === 0) {
                                        meetingList.visible = true
                                        publishMeeting.visible = false
                                        notification.visible = false
                                        personalData.visible = false
                                    } else if (index === 1) {
                                        meetingList.visible = false
                                        publishMeeting.visible = true
                                        notification.visible = false
                                        personalData.visible = false
                                    } else if (index === 2) {
                                        meetingList.visible = false
                                        publishMeeting.visible = false
                                        notification.visible = true
                                        personalData.visible = false
                                    } else if (index === 3) {
                                        meetingList.visible = false
                                        publishMeeting.visible = false
                                        notification.visible = false
                                        personalData.visible = true
                                    }
                                    home.newMessage[index] = false
                                    buttonListLoader.sourceComponent = null
                                    buttonListLoader.sourceComponent = buttonListComponent
                                }
                            }
                        }
                    }
                }
            }
            Rectangle {
                width: 1
                height: mainWindow.width * 0.85
                border.color: "blue"
                border.width: 1
                color: "blue"
            }

            Rectangle {
                height: mainWindow.height * 0.88 - 1
                width: mainWindow.width * 0.85
                MeetingList {
                    id: meetingList
                    visible: true
                    onBeginMeeting: {
                        //                        mee = conferenceUI.employee.getMeeting(index)
                        //                        meeting.currentMeetingID = mee.meetingID
                        currentChooseMeeting = meetingID[index]
                        employeeMessage.visible = false
                        meeting.visible = true
                    }
                    onComeBackMeeting: {
                        employeeMessage.visible = false
                        meeting.visible = true
                    }

                    onAttendMeeting: {
                        currentChooseMeeting = meetingID[index]
                        //                        mee = conferenceUI.employee.getMeeting(index)
                        //                        meeting.currentMeetingID = mee.meetingID
                        employeeMessage.visible = false
                        meeting.visible = true
                    }
                    onRecordMeeting: {

                    }
                }
                PublishMeeting {
                    id: publishMeeting
                    visible: false
                }
                NotificationList {
                    id: notification
                    visible: false
                }

                PersonalData {
                    id: personalData
                    visible: false
                }
            }
            //            }
        }
    }
}
