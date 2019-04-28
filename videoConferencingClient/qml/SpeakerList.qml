import QtQuick 2.0
import QtQuick.Controls 1.4
import Meeting 1.0

Rectangle {
    id: speakerList
    property var currentEmployee
    signal refresh
    signal speakerChoose(var userID, var realName)
    property bool begin: true

    property string companySelect
    property string companyName
    property var companyDepartmentNum
    property var departmentSelect: []
    property var departmentName: []
    property var departmentGroupNum: []
    property var departmentEmployeeNum: []

    property var groupSelect: []
    property var groupName: []
    property var groupEmployeeNum: []

    property var employeeSelect: []
    property var employeeRealName: []
    property var employeeUserID: []

    anchors.left: parent.left
    anchors.leftMargin: mainWindow.width * 0.05 + 50
    anchors.top: parent.top
    anchors.topMargin: mainWindow.height * 0.12
    width: mainWindow.width * 0.25
    height: mainWindow.height * 0.50
    border.color: "blue"

    property Department dep
    property Group gro
    property ConciseEmployee emp
    function initListChoose() {
        companyName = conferenceUI.employee.companys.companyName
        companySelect = listOpen
        companyDepartmentNum = conferenceUI.employee.companys.departmentCount()
        for (var a = 0; a !== conferenceUI.employee.companys.departmentCount(
                 ); a++) {
            departmentSelect[a] = listOpen
            dep = conferenceUI.employee.companys.getDepartment(a)
            departmentName[a] = dep.departmentName
            departmentGroupNum[a] = dep.groupCount()
            departmentEmployeeNum[a] = dep.employeesNumber
            console.log("departmentGroupNUmber  ", dep.groupCount())
            for (var b = 0; b !== dep.groupCount(); b++) {
                groupSelect[groupSelect.length] = listOpen
                gro = dep.getGroup(b)
                groupName[groupName.length] = gro.groupName
                groupEmployeeNum[groupEmployeeNum.length] = gro.conciseEmployeeCount()
                for (var c = 0; c !== gro.conciseEmployeeCount(); c++) {
                    employeeSelect[employeeSelect.length] = false
                    emp = gro.getConciseEmployee(c)
                    employeeRealName[employeeRealName.length] = emp.realName
                    employeeUserID[employeeUserID.length] = emp.userID
                }
            }
        }
        for (var i = 0; i != groupName.length; i++) {
            console.log("groupName  ", groupName[i])
            console.log("groupEmployeeNum  ", groupEmployeeNum[i])
        }

        console.log("companyDepartmentNum  ", companyDepartmentNum)
    }

    Rectangle {
        width: parent.width - 2
        height: parent.height - 2
        anchors.centerIn: parent
        Loader {
            id: attendeeLoader
            anchors.fill: parent

            sourceComponent: attendeeComponent
        }
        Connections {
            target: speakerList
            onRefresh: {
                attendeeLoader.sourceComponent = null
                attendeeLoader.sourceComponent = attendeeComponent
            }
        }
        Connections {
            target: conferenceUI.employee
            onLoginSucceeded: {
                if (type === "CompanyMessage") {
                    console.log("speaker init company message")
                    initListChoose()
                    refresh()
                }
            }
        }

        Component {
            id: attendeeComponent

            ScrollView {
                id: scroll
                anchors.fill: parent
                Rectangle {
                    z: 1
                    id: companySet
                    width: parent.width
                    height: mainWindow.height * 0.06
                    Row {
                        anchors.fill: parent
                        spacing: 10
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        Image {
                            id: companyChoose
                            width: parent.height * 0.5
                            height: parent.height * 0.5
                            source: companySelect
                            anchors.verticalCenter: parent.verticalCenter
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    if (companySelect === listOpen) {
                                        companySelect = listClose
                                        companyChoose.source = listClose
                                        allDepartment.visible = false
                                    } else {
                                        companyChoose.source = listOpen
                                        companySelect = listOpen
                                        allDepartment.visible = true
                                    }

                                    //                                    refresh()
                                }
                            }
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: qsTr(companyName)
                        }
                    }
                }

                ListView {
                    z: -1
                    id: allDepartment
                    anchors.fill: parent
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.top: parent.top
                    anchors.topMargin: mainWindow.height * 0.06
                    model: companyDepartmentNum
                    delegate: Rectangle {
                        //                        border.width: 1
                        z: -1
                        id: departmentSet
                        width: parent.width
                        height: {
                            var l = 0
                            l += departmentGroupNum[index] - '0'
                            l += departmentEmployeeNum[index] - '0'
                            l += 1
                            console.log("department length  ", l,
                                        "  index", index)
                            return mainWindow.height * 0.06 * l
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
                                        source: departmentSelect[index]

                                        anchors.verticalCenter: parent.verticalCenter
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                if (departmentSelect[index] === listOpen) {
                                                    departmentSelect[index] = listClose
                                                    departmentChoose.source = listClose
                                                    allGroup.visible = false
                                                    departmentSet.height = mainWindow.height * 0.06
                                                } else {
                                                    departmentSelect[index] = listOpen
                                                    departmentChoose.source = listOpen
                                                    allGroup.visible = true
                                                    var l = 0
                                                    l += departmentGroupNum[index] - '0'
                                                    var gl = 0
                                                    for (var i = 0; i != index; i++) {
                                                        gl += departmentGroupNum[i] - '0'
                                                    }
                                                    for (var a = 0; a != departmentGroupNum[index]
                                                         - '0'; a++) {
                                                        if (groupSelect[gl + a] === listOpen)
                                                            l += groupEmployeeNum[gl + a] - '0'
                                                    }

                                                    //                                                    l += departmentEmployeeNum[index] - '0'
                                                    l += 1
                                                    departmentSet.height
                                                            = mainWindow.height * 0.06 * l
                                                }
                                            }
                                        }
                                    }
                                    Text {
                                        anchors.verticalCenter: parent.verticalCenter
                                        text: {
                                            console.log("scroll.departmentNum  ",
                                                        scroll.departmentNum,
                                                        "  departmentName  ",
                                                        departmentName[index])

                                            return departmentName[index]
                                        }
                                    } //text
                                } //row
                            } //item
                            ListView {
                                id: allGroup
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                width: parent.width - 10
                                property var beforeGroup: {
                                    var gl = 0
                                    for (var i = 0; i != index; i++) {
                                        gl += departmentGroupNum[i] - '0'
                                    }
                                    return gl
                                }
                                property var beforeEmployee1: {
                                    var el = 0
                                    for (var i = 0; i != index; i++) {
                                        el += departmentEmployeeNum[i] - '0'
                                    }
                                    return el
                                }

                                height: {
                                    var l = 0
                                    l += departmentGroupNum[index] - '0'
                                    l += departmentEmployeeNum[index] - '0'
                                    return mainWindow.height * 0.06 * l
                                }
                                model: {
                                    console.log("departmentGroupNUm  ",
                                                departmentGroupNum[index])
                                    departmentGroupNum[index]
                                }

                                delegate: Rectangle {
                                    id: groupSet
                                    width: parent.width
                                    height: {
                                        var l = 0

                                        l += groupEmployeeNum[allGroup.beforeGroup + index] - '0'

                                        l += 1
                                        console.log("groupLength  ", l,
                                                    "  groupindex  ", index)
                                        mainWindow.height * 0.06 * l
                                    }
                                    Row {
                                        width: parent.width
                                        height: mainWindow.height * 0.06
                                        spacing: 10
                                        Image {
                                            id: groupChoose
                                            width: parent.height * 0.5
                                            height: parent.height * 0.5
                                            anchors.verticalCenter: parent.verticalCenter
                                            source: groupSelect[allGroup.beforeGroup + index]
                                            MouseArea {
                                                anchors.fill: parent
                                                onClicked: {
                                                    if (groupSelect[allGroup.beforeGroup + index]
                                                            === listOpen) {
                                                        groupSelect[allGroup.beforeGroup + index]
                                                                = listClose
                                                        groupChoose.source = listClose
                                                        allEmployee.visible = false
                                                        groupSet.height = mainWindow.height * 0.06
                                                        var l = 0

                                                        l += groupEmployeeNum[allGroup.beforeGroup + index] - '0'
                                                        departmentSet.height
                                                                -= mainWindow.height * 0.06 * l
                                                    } else {
                                                        groupSelect[allGroup.beforeGroup + index]
                                                                = listOpen
                                                        groupChoose.source = listOpen
                                                        allEmployee.visible = true
                                                        l = 0

                                                        l += groupEmployeeNum[allGroup.beforeGroup + index] - '0'
                                                        departmentSet.height
                                                                += mainWindow.height * 0.06 * l

                                                        l += 1
                                                        groupSet.height = mainWindow.height
                                                                * 0.06 * l
                                                    }

                                                    //                                                    refresh()
                                                }
                                            }
                                        }
                                        Text {
                                            anchors.verticalCenter: parent.verticalCenter
                                            text: groupName[allGroup.beforeGroup + index]
                                        } //text
                                    } //row
                                    ListView {
                                        id: allEmployee
                                        property var beforeEmployee2: {
                                            var el = 0
                                            for (var i = 0; i != index; i++) {
                                                el += groupEmployeeNum[allGroup.beforeGroup + i]
                                            }
                                            return el
                                        }

                                        anchors.left: parent.left
                                        anchors.leftMargin: 10
                                        anchors.top: parent.top
                                        anchors.topMargin: mainWindow.height * 0.06
                                        width: parent.width - 10
                                        height: {
                                            var l = 0
                                            l += groupEmployeeNum[allGroup.beforeGroup
                                                                  + index] - '0'
                                            l += 1
                                            return mainWindow.height * 0.06 * l
                                        }
                                        model: groupEmployeeNum[allGroup.beforeGroup + index]

                                        delegate: Rectangle {
                                            id: employeeSet
                                            //                                            property ConciseEmployee employees: groupSet.groups.getConciseEmployee(index)
                                            width: parent.width - 10
                                            height: mainWindow.height * 0.06
                                            Row {
                                                width: parent.width
                                                height: mainWindow.height * 0.06
                                                spacing: 10
                                                CheckBox {
                                                    id: employeeChoose
                                                    checked: {
                                                        if (speakerID.text === employeeUserID[allGroup.beforeEmployee1 + allEmployee.beforeEmployee2 + index]) {
                                                            employeeSelect[allGroup.beforeEmployee1 + allEmployee.beforeEmployee2 + index] = true
                                                        } else
                                                            employeeSelect[allGroup.beforeEmployee1 + allEmployee.beforeEmployee2 + index] = false
                                                        return employeeSelect[allGroup.beforeEmployee1 + allEmployee.beforeEmployee2 + index]
                                                    }
                                                    onClicked: {
                                                        speakerChoose(
                                                                    employeeUserID[allGroup.beforeEmployee1 + allEmployee.beforeEmployee2 + index], employeeRealName[allGroup.beforeEmployee1 + allEmployee.beforeEmployee2 + index])
                                                        refresh()
                                                    }

                                                    anchors.verticalCenter: parent.verticalCenter
                                                }
                                                Text {
                                                    anchors.verticalCenter: parent.verticalCenter
                                                    text: employeeRealName[allGroup.beforeEmployee1 + allEmployee.beforeEmployee2 + index]
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
