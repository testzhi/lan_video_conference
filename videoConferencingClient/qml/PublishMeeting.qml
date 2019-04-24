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
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    maximumLength: 10
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
                            //                            speakerList.currentEmployee =
                            //                            if (speakerLoader.sourceComponent === null)
                            //                                speakerLoader.sourceComponent = speakerComponent
                            //                            else
                            //                                speakerLoader.sourceComponent = null
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
                    text: "参会人员："
                    //                    font.pixelSize: 25
                }
                Rectangle {
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: mainWindow.width * 0.05 + 50
                    width: mainWindow.width * 0.25
                    height: mainWindow.height * 0.06
                    border.color: "blue"
                    border.width: 1
                    //                    TextField {
                    //                        id: speakerName
                    //                        anchors.fill: parent
                    //                        maximumLength: 10
                    //                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            attendeeList.visible = !attendeeList.visible
                        }
                    }
                }
            }
            Button {
                text: "确认发布"
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
    }

    //    }

    //    Rectangle {
    //        id: speakerList
    //        visible: false
    //        anchors.left: parent.left
    //        anchors.leftMargin: mainWindow.width * 0.25 + 50
    //        width: mainWindow.width * 0.3
    //        height: mainWindow.height /** 0.60*/
    //        border.color: "blue"
    //        //        border.width: 1
    //        Rectangle {
    //            width: parent.width - 2
    //            height: parent.height - 2
    //            anchors.centerIn: parent
    //            //            border.width: 1
    //            ScrollView {
    //                anchors.fill: parent
    //                Rectangle {
    //                    //                    z: -1
    //                    id: companySet
    //                    property var set: 0
    //                    width: parent.width
    //                    height: mainWindow.height * 0.06
    //                    Row {
    //                        anchors.fill: parent
    //                        spacing: 10
    //                        anchors.left: parent.left
    //                        anchors.leftMargin: 10
    //                        Image {
    //                            id: companyChoose
    //                            //                            signal companyChooseChanged
    //                            width: parent.height * 0.5
    //                            height: parent.height * 0.5
    //                            source: "../resources/1.png"
    //                            anchors.verticalCenter: parent.verticalCenter
    //                            MouseArea {
    //                                anchors.fill: parent
    //                                onClicked: {
    //                                    if (company.set === 0) {
    //                                        company.set = 1
    //                                        companyChoose.source = "../resources/1.png"
    //                                        allDepartment.visible = true
    //                                    } else {
    //                                        companyChoose.source = "../resources/xly.png"
    //                                        allDepartment.visible = false
    //                                        company.set = 0
    //                                    }
    //                                }
    //                            }
    //                        }
    //                        Text {
    //                            anchors.verticalCenter: parent.verticalCenter
    //                            text: qsTr(company.companyName)
    //                        }
    //                    }
    //                }
    //                ListView {
    //                    z: -1
    //                    id: allDepartment
    //                    anchors.fill: parent
    //                    anchors.left: parent.left
    //                    anchors.leftMargin: 20
    //                    anchors.top: parent.top
    //                    anchors.topMargin: mainWindow.height * 0.06
    //                    visible: {
    //                        if (companySet.set === 0)
    //                            return true
    //                        else
    //                            return false
    //                    }

    //                    model: company.departmentCount()
    //                    delegate: Rectangle {
    //                        z: -1
    //                        id: departmentSet
    //                        property Department departments: company.getDepartment(
    //                                                             index)
    //                        width: parent.width
    //                        height: {

    //                            var a = departments.groupCount()
    //                            var b = departments.employeeCount()
    //                            console.log("hhh   ", a + b + 1)
    //                            mainWindow.height * 0.06 * (a + b + 1)
    //                        }
    //                        //                        border.width: 1
    //                        //                        border.color: "yellow"
    //                        Column {
    //                            anchors.fill: parent
    //                            Item {
    //                                width: parent.width
    //                                height: mainWindow.height * 0.06
    //                                Row {
    //                                    anchors.fill: parent
    //                                    spacing: 10
    //                                    Image {
    //                                        id: departmentChoose
    //                                        width: parent.height * 0.5
    //                                        height: parent.height * 0.5
    //                                        source: "../resources/1.png"
    //                                        anchors.verticalCenter: parent.verticalCenter
    //                                        MouseArea {
    //                                            anchors.fill: parent
    //                                            onClicked: {
    //                                                if (allGroup.visible === true) {
    //                                                    allGroup.visible = false
    //                                                    departmentSet.height = mainWindow.height * 0.06
    //                                                    departmentChoose.source = "../resources/xly.png"
    //                                                } else {
    //                                                    allGroup.visible = true
    //                                                    departmentSet.height = mainWindow.height * 0.06 * (departments.groupCount() + 1 + departmentSet.departments.employeeCount())
    //                                                    departmentChoose.source = "../resources/1.png"
    //                                                }
    //                                            }
    //                                        }
    //                                    }
    //                                    Text {
    //                                        anchors.verticalCenter: parent.verticalCenter
    //                                        text: {
    //                                            return departmentSet.departments.departmentName
    //                                        }
    //                                    } //text
    //                                } //row
    //                            } //item
    //                            ListView {
    //                                id: allGroup
    //                                anchors.left: parent.left
    //                                anchors.leftMargin: 10
    //                                width: parent.width - 10
    //                                height: mainWindow.height * 0.06
    //                                        * (departmentSet.departments.groupCount(
    //                                               ) + departmentSet.departments.employeeCount(
    //                                               ))
    //                                model: departmentSet.departments.groupCount()

    //                                delegate: Rectangle {
    //                                    id: groupSet
    //                                    property Group groups: departmentSet.departments.getGroup(
    //                                                               index)
    //                                    width: parent.width
    //                                    height: mainWindow.height * 0.06 * (groups.employeeCount(
    //                                                                            ) + 1)
    //                                    //                                    border.width: 1
    //                                    Row {
    //                                        width: parent.width
    //                                        height: mainWindow.height * 0.06
    //                                        spacing: 10
    //                                        Image {
    //                                            id: groupChoose
    //                                            width: parent.height * 0.5
    //                                            height: parent.height * 0.5
    //                                            source: "../resources/1.png"
    //                                            anchors.verticalCenter: parent.verticalCenter
    //                                            MouseArea {
    //                                                anchors.fill: parent
    //                                                onClicked: {
    //                                                    if (allEmployee.visible === true) {
    //                                                        allEmployee.visible = false
    //                                                        groupSet.height = mainWindow.height * 0.06
    //                                                        departmentSet.height -= mainWindow.height * 0.06 * groupSet.groups.employeeCount()
    //                                                        groupChoose.source = "../resources/xly.png"
    //                                                    } else {
    //                                                        allEmployee.visible = true
    //                                                        groupSet.height = mainWindow.height * 0.06
    //                                                                * (groups.employeeCount(
    //                                                                       ) + 1)
    //                                                        departmentSet.height += mainWindow.height * 0.06 * groupSet.groups.employeeCount()

    //                                                        groupChoose.source = "../resources/1.png"
    //                                                    }
    //                                                }
    //                                            }
    //                                        }
    //                                        Text {
    //                                            anchors.verticalCenter: parent.verticalCenter
    //                                            text: {
    //                                                return groupSet.groups.groupName
    //                                            }
    //                                        } //text
    //                                    } //row
    //                                    ListView {
    //                                        id: allEmployee
    //                                        anchors.left: parent.left
    //                                        anchors.leftMargin: 10
    //                                        anchors.top: parent.top
    //                                        anchors.topMargin: mainWindow.height * 0.06
    //                                        width: parent.width - 10
    //                                        height: mainWindow.height * 0.06
    //                                                * (groupSet.groups.employeeCount(
    //                                                       ) + 1)
    //                                        model: groupSet.groups.employeeCount()
    //                                        delegate: Rectangle {
    //                                            id: employeeSet
    //                                            property Employee employees: groupSet.groups.getEmployee(index)
    //                                            width: parent.width - 10
    //                                            height: mainWindow.height * 0.06
    //                                            Row {
    //                                                width: parent.width
    //                                                height: mainWindow.height * 0.06
    //                                                spacing: 10
    //                                                CheckBox {
    //                                                    id: employeeChoose
    //                                                    checked: {
    //                                                        if (employeeSet.employees.userID
    //                                                                === speakerID.text)
    //                                                            return true
    //                                                        else
    //                                                            return false
    //                                                    }
    //                                                    onClicked: {
    //                                                        speakerList.visible = false
    //                                                        speakerID.text
    //                                                                = employeeSet.employees.userID
    //                                                        speakerName.text
    //                                                                = employeeSet.employees.realName
    //                                                    }

    //                                                    anchors.verticalCenter: parent.verticalCenter
    //                                                }
    //                                                Text {
    //                                                    anchors.verticalCenter: parent.verticalCenter
    //                                                    text: {
    //                                                        return employeeSet.employees.realName
    //                                                    }
    //                                                } //text
    //                                            } //row
    //                                        }
    //                                    }
    //                                } //delegate
    //                            } //listView
    //                        } //column
    //                    } //delegate
    //                } //listView
    //                //                    }
    //                //                }
    //            } //scrollView
    //        }
    //    }
}
