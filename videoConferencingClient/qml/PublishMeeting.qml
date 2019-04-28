import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import Meeting 1.0

Item {
    height: mainWindow.height * 0.88
    width: mainWindow.width * 0.85
    ScrollView {
        anchors.fill: parent
        Column {
            z: 1
            anchors.fill: parent
            Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: "会议主题："
                    //                    font.pixelSize: 25
                }
                TextField {
                    id: subject
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    maximumLength: 10
                }
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.31
                    anchors.verticalCenter: parent.verticalCenter
                    text: "  *"
                    color: "red"
                    visible: subject.text.length === 0
                }
            }
            Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.20
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: "会议说明："
                    //                    font.pixelSize: 25
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    width: parent.width * 0.87
                    height: parent.height * 0.9
                    //                    border.color: "blue"
                    border.width: 1
                    ScrollView {
                        anchors.fill: parent
                        TextArea {
                            id: remark
                        }
                    }
                }
            }
            Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: "会议类别："
                    //                    font.pixelSize: 25
                }
                ComboBox {
                    id: category
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    //                    font.pixelSize: 25
                    visible: true
                    onCurrentIndexChanged: {
                        if (category.currentIndex === 1) {
                            miniPeople.visible = true
                        } else
                            miniPeople.visible = false
                    }

                    //                    onCurrentIndexChanged:
                    model: ["讨论类", "分享类"]
                }
                Item {
                    id: miniPeople
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: mainWindow.width * 0.40
                        text: "最低人数限制："
                        //                        font.pixelSize: 25
                    }
                    SpinBox {
                        id: scale
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: mainWindow.width * 0.55
                        from: 0
                        to: 1000
                        value: 10
                        editable: true
                        stepSize: 1
                    }
                }
            }
            Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: "会议日期："
                    //                    font.pixelSize: 25
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    width: mainWindow.width * 0.25
                    height: mainWindow.height * 0.06
                    border.color: "blue"
                    TextField {
                        id: currentDate
                        property var selectDate
                        anchors.fill: parent
                        maximumLength: 10
                    }

                    border.width: 1
                    MouseArea {
                        anchors.fill: parent
                        onClicked: calendar.visible = !calendar.visible
                        //                        onFocusChanged: calendar.visible = false
                        //                        onWheel: calendar.visible = false
                    }
                }
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.36
                    anchors.verticalCenter: parent.verticalCenter
                    text: "  *"
                    color: "red"
                    visible: currentDate.text.length === 0
                }
            }
            Rectangle {
                id: chooseTime
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                property var currentTime: new Date()
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: "会议时间："
                    //                    font.pixelSize: 25
                }
                SpinBox {
                    id: hour
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    from: 0
                    to: 24
                    value: chooseTime.currentTime.getHours()
                    editable: true
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 215
                    text: ":"
                    font.bold: true
                }

                SpinBox {
                    id: minute
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 250
                    from: 0
                    to: 59
                    value: chooseTime.currentTime.getMinutes()
                    editable: true
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.55
                    text: "预期时长："
                    //                    font.pixelSize: 25
                }
                SpinBox {
                    id: dura
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.55 + 80
                    from: 0
                    to: 480
                    value: 30
                    editable: true
                    stepSize: 5
                }
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.55 + 230
                    text: "分钟"
                    //                    font.pixelSize: 25
                }
            }
            Rectangle {
                //                z: 10
                id: speaker
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: "主讲人员："
                    //                    font.pixelSize: 25
                    //                    maximumLength: 10
                }
                TextField {
                    id: speakerID
                    visible: false
                }

                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    width: mainWindow.width * 0.25
                    height: mainWindow.height * 0.06
                    border.color: "blue"
                    border.width: 1
                    TextField {
                        id: speakerName
                        anchors.fill: parent
                        maximumLength: 10
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            speakerList.visible = !speakerList.visible
                        }
                    }
                }
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.36
                    anchors.verticalCenter: parent.verticalCenter
                    text: "  *"
                    color: "red"
                    visible: speakerID.text.length === 0
                }
            }

            Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.10
                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.01
                    text: "参会人员："
                    //                    font.pixelSize: 25
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    width: mainWindow.width * 0.50
                    height: mainWindow.height * 0.06
                    border.width: 1
                    ScrollView {
                        anchors.fill: parent
                        TextArea {
                            id: attendeeID
                            property var attendeeUserID: []
                            wrapMode: Text.Wrap
                        }
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            attendeeList.visible = !attendeeList.visible
                        }
                    }
                }
                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.61
                    anchors.verticalCenter: parent.verticalCenter
                    text: "  *"
                    color: "red"
                    visible: attendeeID.text.length === 0
                }
            }
            Rectangle {
                width: mainWindow.width * 0.85
                height: mainWindow.height * 0.06
                Button {
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    //                highlighted: true
                    text: "确认发布"
                    onClicked: {
                        var currDate = new Date
                        var date = new Date()
                        date = currentDate.selectDate
                        date.setHours(hour.value)
                        date.setMinutes(minute.value)
                        console.log("selectDate  ", date)
                        if (subject.text.length === 0
                                || currentDate.text.length === 0
                                || speakerID.text.length === 0
                                || attendeeID.text.length === 0) {
                            mistake.text = "信息未填写完整"
                        } else if (currDate > date) {
                            mistake.text = "无效的会议日期时间"
                        } else {
                            mistake.text = ""
                            var scaleNum = 0
                            if (category.currentIndex === 1)
                                scaleNum = scale.value
                            var time = hour.value.toString(
                                        ) + ":" + minute.value.toString()
                            console.log(scaleNum, "  ", time)
                            for (var i = 0; i != attendeeID.attendeeUserID.length; i++)
                                console.log("attendee userid  ",
                                            attendeeID.attendeeUserID[i])
                            conferenceUI.getLaunchMeetingMessage(
                                        speakerID.text, currentDate.text, time,
                                        category.currentIndex.toString(),
                                        subject.text, scaleNum.toString(),
                                        dura.value.toString(), remark.text,
                                        attendeeID.attendeeUserID)
                        }
                    }
                }
                Text {
                    id: mistake
                    color: "red"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.3
                }
            }
        }
    }
    Connections {
        target: conferenceUI.employee
        onLoginSucceeded: {
            if (type === "PublishSucceed") {
                mistake.text = "会议发布成功"
                subject.text = remark.text = currentDate.text = speakerID.text
                        = speakerName.text = attendeeID.text = ""
                speakerList.refresh()
                attendeeList.refreshChoose()
                attendeeList.refresh()
            }
        }
    }

    Calendar {
        id: calendar
        visible: false
        weekNumbersVisible: true
        anchors.top: parent.top
        anchors.topMargin: mainWindow.height * 0.48
        anchors.left: parent.left
        anchors.leftMargin: mainWindow.width * 0.05 + 50
        onClicked: {
            var s = selectedDate
            var time = new Date()
            currentDate.text = selectedDate
            currentDate.selectDate = selectedDate
            calendar.visible = false
        }
    }
    SpeakerList {
        id: speakerList

        visible: false
        onSpeakerChoose: {
            speakerList.visible = false
            speakerID.text = qsTr(userID)
            speakerName.text = qsTr(realName)
            currentEmployee = qsTr(userID)
        }
    }
    AttendeeList {
        id: attendeeList
        visible: false
        onRefresh: {
            attendeeID.attendeeUserID.length = 0
            var s = ""
            for (var i = 0; i != employeeSelect.length; i++) {
                if (employeeSelect[i] === true) {
                    s += employeeRealName[i] + " / "
                    attendeeID.attendeeUserID[attendeeID.attendeeUserID.length] = employeeUserID[i]
                }
            }

            attendeeID.text = s
        }
    }
}
