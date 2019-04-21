import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.12

Item {
    anchors.fill: parent
    Column {
        id: mainPage
        Rectangle {
            height: mainWindow.height * 0.12
            width: mainWindow.width
            z: 1
            Row {
                anchors.fill: parent
                anchors.left: parent.left
                anchors.leftMargin: mainWindow.width * 0.03
                spacing: mainWindow.width * 0.03
                Rectangle {
                    id: img
                    width: mainWindow.height * 0.07
                    height: mainWindow.height * 0.07
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
                    text: conferenceUI.employee.realName
                    //                    font.pixelSize: 25
                }
            }
        }
        Rectangle {
            width: mainWindow.width
            height: 1
            color: "blue"
        }

        Row {
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
                }
                PublishMeeting {
                    id: publishMeeting
                    visible: false
                }
                Notification {
                    id: notification
                    visible: false
                }
                PersonalData {
                    id: personalData
                    visible: false
                }
            }
        }
    }
}
