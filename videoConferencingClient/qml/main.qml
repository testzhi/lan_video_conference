import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Meeting 1.0
import QtGraphicalEffects 1.0

Window {
    id: mainWindow
    property string listOpen: "../resources/1.png"
    property string listClose: "../resources/xly.png"
    property string listAllChoose: "../resources/1.png"
    property string listAllNotChoose: "../resources/xly.png"
    visible: true
    width: 640 * 1.5
    height: 480 * 1.3
    color: "black"

    Column {
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
                    width: mainWindow.height * 0.10
                    height: mainWindow.height * 0.10
                    anchors.verticalCenter: parent.verticalCenter
                    Image {
                        id: _image
                        smooth: true
                        visible: false
                        anchors.fill: parent
                        source: "../resources/xly.png"
                        //                        sourceSize: Qt.size(parent.size, parent.size)
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
                    text: employee.realName
                    font.pixelSize: 25
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
                                font.pointSize: 50
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            onClicked: {
                                if (index === 0) {
                                    meetingList.visible = true
                                    publishMeeting.visible = false
                                } else if (index === 1) {
                                    meetingList.visible = false
                                    publishMeeting.visible = true
                                } else if (index === 2) {
                                    meetingList.visible = false
                                    publishMeeting.visible = false
                                } else if (index === 3) {
                                    meetingList.visible = false
                                    publishMeeting.visible = false
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
                //                border.color: "blue"
                //                border.width: 2
                MeetingList {
                    id: meetingList
                    visible: false
                }
                PublishMeeting {
                    id: publishMeeting
                    visible: true
                }
            }
        }
    }
    //    Employee {
    //        userID: employee.userID
    //        meetings: [
    //            Meeting {
    //            },
    //            Meeting {
    //            }
    //        ]
    //    }
    //    Company {
    //        id: myCompany
    //        companyName: "tieto"
    //        departments: [
    //            Department {
    //                id: d1
    //                departmentName: "3G"
    //                groups: [
    //                    Group {
    //                        groupName: "Ginkgoes"
    //                        employees: [
    //                            Employee {
    //                                realName: "李章玉"
    //                            },
    //                            Employee {
    //                                realName: "雷娜"
    //                            }
    //                        ]
    //                    },
    //                    Group {
    //                        groupName: "SunBirds"
    //                    }
    //                ]
    //            },
    //            Department {
    //                id: d2
    //                departmentName: "4G"
    //            }
    //        ]
    //    }
}
