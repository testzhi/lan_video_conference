import QtQuick 2.0
import QtQuick.Controls 2.2
import Meeting 1.0

Item {
    anchors.fill: parent
    ScrollView {
        id: notificationList
        anchors.fill: parent
        ListView {
            model: conferenceUI.employee.notificationCount()
            spacing: 0.1
            delegate: Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                border.width: 0.5
                //                border.color: "blue"
                Text {
                    property Notification notification: conferenceUI.employee.getNotification(
                                                            index)
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: notification.notificationMessage
//                    font.pixelSize: 15
                }
                Row {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    spacing: 10
                    Button {
                        text: "同意"
                    }
                    Button {
                        text: "拒绝"
                        onClicked: {
                            refuse.visible = true
                            notificationList.opacity = 0.5
                        }
                    }
                }
            }
        }
    }
    Rectangle {
        id: refuse
        visible: false
        anchors.centerIn: parent
        width: mainWindow.width * 0.4
        height: mainWindow.height * 0.50
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
                        refuse.visible = false
                        notificationList.opacity = 1
                        mistake.text = ""
                    }
                }
            }
        }
        Column {
            anchors.fill: parent
            spacing: 10
            Text {
                text: "请填写无法参会理由"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Rectangle {
                width: mainWindow.width * 0.40
                height: mainWindow.height * 0.30
                anchors.horizontalCenter: parent.horizontalCenter
                border.width: 1
                ScrollView {
                    anchors.fill: parent
                    TextArea {
                        id: refuseText
                    }
                }
            }
            Button {
                text: "确定"
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    if (refuseText.text.length !== 0) {
                        notificationList.opacity = 1
                        refuse.visible = false
                        mistake.text = ""
                        refuseText.text = ""
                    } else
                        mistake.text = "无法参会原因不能为空"
                }
            }
            Text {
                id: mistake
                anchors.horizontalCenter: parent.horizontalCenter
                color: "red"
            }
        }
    }
}