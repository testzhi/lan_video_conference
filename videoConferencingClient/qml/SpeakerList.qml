import QtQuick 2.0
import QtQuick.Controls 1.4
import Meeting 1.0

Rectangle {
    id: speakerList
    property var currentEmployee
    signal speakerChoose(var userID, var realName)
    anchors.left: parent.left
    anchors.leftMargin: mainWindow.width * 0.05 + 50
    anchors.top: parent.top
    anchors.topMargin: mainWindow.height * 0.12
    width: mainWindow.width * 0.25
    height: mainWindow.height * 0.50
    border.color: "blue"
    Rectangle {
        width: parent.width - 2
        height: parent.height - 2
        anchors.centerIn: parent
        Loader {
            id: speakerLoader
            anchors.fill: parent

            sourceComponent: speakerComponent
        }

        Connections {
            target: speakerList
            onCurrentEmployeeChanged: {
                speakerLoader.sourceComponent = null
                speakerLoader.sourceComponent = speakerComponent
            }
        }
        Component {
            id: speakerComponent
            ScrollView {
                anchors.fill: parent
                Rectangle {
                    z: 1
                    id: companySet
                    property var set: 0
                    width: parent.width
                    height: mainWindow.height * 0.06
                    Row {
                        anchors.fill: parent
                        spacing: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        Image {
                            id: companyChoose
                            //                            signal companyChooseChanged
                            width: parent.height * 0.5
                            height: parent.height * 0.5
                            source: listOpen
                            anchors.verticalCenter: parent.verticalCenter
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (company.set === 0) {
                                        company.set = 1
                                        companyChoose.source = listOpen
                                        allDepartment.visible = true
                                    } else {
                                        companyChoose.source = listClose
                                        allDepartment.visible = false
                                        company.set = 0
                                    }
                                }
                            }
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr(company.companyName)
                        }
                    }
                }

                ListView {
                    id: allDepartment
                    z: -1
                    anchors.fill: parent
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.top: parent.top
                    anchors.topMargin: mainWindow.height * 0.06
                    visible: {
                        if (companySet.set === 0)
                            return true
                        else
                            return false
                    }

                    model: company.departmentCount()
                    delegate: Rectangle {
                        z: -1
                        id: departmentSet
                        property Department departments: company.getDepartment(
                                                             index)
                        width: parent.width
                        height: {

                            var a = departments.groupCount()
                            var b = departments.employeeCount()
                            //                            console.log("hhh   ", a + b + 1)
                            mainWindow.height * 0.06 * (a + b + 1)
                        }
                        Column {
                            anchors.fill: parent
                            Item {
                                width: parent.width
                                height: mainWindow.height * 0.06
                                Row {
                                    anchors.fill: parent
                                    spacing: 10
                                    Image {
                                        id: departmentChoose
                                        width: parent.height * 0.5
                                        height: parent.height * 0.5
                                        source: listOpen
                                        anchors.verticalCenter: parent.verticalCenter
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                if (allGroup.visible === true) {
                                                    allGroup.visible = false
                                                    departmentSet.height = mainWindow.height * 0.06
                                                    departmentChoose.source = listClose
                                                } else {
                                                    allGroup.visible = true
                                                    departmentSet.height = mainWindow.height * 0.06 * (departments.groupCount() + 1 + departmentSet.departments.employeeCount())
                                                    departmentChoose.source = listOpen
                                                }
                                            }
                                        }
                                    }
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: {
                                            return departmentSet.departments.departmentName
                                        }
                                    } //text
                                } //row
                            } //item
                            ListView {
                                id: allGroup
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                width: parent.width - 10
                                height: mainWindow.height * 0.06
                                        * (departmentSet.departments.groupCount(
                                               ) + departmentSet.departments.employeeCount(
                                               ))
                                model: departmentSet.departments.groupCount()

                                delegate: Rectangle {
                                    id: groupSet
                                    property Group groups: departmentSet.departments.getGroup(
                                                               index)
                                    width: parent.width
                                    height: mainWindow.height * 0.06 * (groups.employeeCount(
                                                                            ) + 1)
                                    //                                    border.width: 1
                                    Row {
                                        width: parent.width
                                        height: mainWindow.height * 0.06
                                        spacing: 10
                                        Image {
                                            id: groupChoose
                                            width: parent.height * 0.5
                                            height: parent.height * 0.5
                                            source: listOpen
                                            anchors.verticalCenter: parent.verticalCenter
                                            MouseArea {
                                                anchors.fill: parent
                                                onClicked: {
                                                    if (allEmployee.visible === true) {
                                                        allEmployee.visible = false
                                                        groupSet.height = mainWindow.height * 0.06
                                                        departmentSet.height -= mainWindow.height * 0.06 * groupSet.groups.employeeCount()
                                                        groupChoose.source = listClose
                                                    } else {
                                                        allEmployee.visible = true
                                                        groupSet.height = mainWindow.height * 0.06
                                                                * (groups.employeeCount(
                                                                       ) + 1)
                                                        departmentSet.height = departmentSet.height + mainWindow.height * 0.06 * groupSet.groups.employeeCount()

                                                        groupChoose.source = listOpen
                                                    }
                                                }
                                            }
                                        }
                                        Text {
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: {
                                                return groupSet.groups.groupName
                                            }
                                        } //text
                                    } //row
                                    ListView {
                                        id: allEmployee
                                        anchors.left: parent.left
                                        anchors.leftMargin: 10
                                        anchors.top: parent.top
                                        anchors.topMargin: mainWindow.height * 0.06
                                        width: parent.width - 10
                                        height: mainWindow.height * 0.06
                                                * (groupSet.groups.employeeCount(
                                                       ) + 1)
                                        model: groupSet.groups.employeeCount()
                                        delegate: Rectangle {
                                            id: employeeSet
                                            property Employee employees: groupSet.groups.getEmployee(index)
                                            width: parent.width - 10
                                            height: mainWindow.height * 0.06
                                            Row {
                                                width: parent.width
                                                height: mainWindow.height * 0.06
                                                spacing: 10
                                                CheckBox {
                                                    id: employeeChoose
                                                    checked: {
                                                        if (employeeSet.employees.userID
                                                                === speakerID.text)
                                                            return true
                                                        else
                                                            return false
                                                    }
                                                    onClicked: {

                                                        speakerChoose(
                                                                    employeeSet.employees.userID,
                                                                    employeeSet.employees.realName)
                                                        //                                                        speakerLoader.sourceComponent = null
                                                        //                                                        speakerLoader.sourceComponent
                                                        //                                                                = speakerComponent
                                                    }

                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                                Text {
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    text: {
                                                        return employeeSet.employees.realName
                                                    }
                                                } //text
                                            } //row
                                        }
                                    }
                                } //delegate
                            } //listView
                        } //column
                    } //delegate
                } //listView
            }
            //                    }
            //                }
        } //scrollView
    }
}
