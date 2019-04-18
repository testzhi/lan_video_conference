import QtQuick 2.0
import QtQuick.Controls 1.4
import Meeting 1.0

Rectangle {
    id: attendeeList
    signal refresh
    property bool begin: true
    property string companySelect: listAllNotChoose
    property var departmentSelect: []
    property var groupSelect: []
    property var groupName: []
    property var employeeID: []
    property var employeeSelect: []
    anchors.left: parent.left
    anchors.leftMargin: mainWindow.width * 0.05 + 50
    anchors.top: parent.top
    anchors.topMargin: mainWindow.height * 0.22
    width: mainWindow.width * 0.25
    height: mainWindow.height * 0.50
    border.color: {
        attendeeList.initListChoose()
        return "blue"
    }

    property Department dep
    property Group gro
    property Employee emp
    function initListChoose() {
        for (var a = 0; a !== company.departmentCount(); a++) {
            departmentSelect[a] = listAllNotChoose
            dep = company.getDepartment([a])
            for (var b = 0; b !== dep.groupCount(); b++) {
                groupSelect[groupSelect.length] = listAllNotChoose
                gro = dep.getGroup(b)
                groupName[groupName.length] = gro.groupName
                for (var c = 0; c !== gro.employeeCount(); c++) {
                    employeeSelect[employeeSelect.length] = false
                    emp = gro.getEmployee(c)
                    employeeID[employeeID.length] = emp.userID
                }
            }
        }
        //        console.log("department   ", departmentSelect.length)
        //        console.log("group   ", departmentSelect.length)
        //        console.log("employee   ", departmentSelect.length)
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
            target: attendeeList
            onRefresh: {
                begin = false
                attendeeLoader.sourceComponent = null
                attendeeLoader.sourceComponent = attendeeComponent
            }
        }
        Component {
            id: attendeeComponent
            ScrollView {
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
                                    if (companySelect == listAllNotChoose) {

                                        companySelect = listAllChoose
                                    } else {
                                        companySelect = listAllNotChoose
                                    }
                                    for (var i = 0; i != departmentSelect.length; i++) {
                                        departmentSelect[i] = companySelect
                                    }
                                    for (var i = 0; i != groupSelect.length; i++) {
                                        groupSelect[i] = companySelect
                                    }
                                    for (var i = 0; i != employeeSelect.length; i++) {
                                        if (companySelect === listAllChoose)
                                            employeeSelect[i] = true
                                        else
                                            employeeSelect[i] = false
                                    }

                                    refresh()
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
                    z: -1
                    id: allDepartment
                    anchors.fill: parent
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.top: parent.top
                    anchors.topMargin: mainWindow.height * 0.06
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
                                        property Group gro1
                                        property Employee emp1
                                        width: parent.height * 0.5
                                        height: parent.height * 0.5
                                        source: departmentSelect[index]

                                        anchors.verticalCenter: parent.verticalCenter
                                        MouseArea {
                                            anchors.fill: parent
                                            onClicked: {
                                                if (departmentSelect[index] === listAllNotChoose)
                                                    departmentSelect[index] = listAllChoose
                                                else
                                                    departmentSelect[index] = listAllNotChoose

                                                //                                                dep = company.getDepartment(
                                                //                                                            index)
                                                for (var a = 0; a
                                                     !== departmentSet.departments.groupCount(
                                                         ); a++) {
                                                    departmentChoose.gro1
                                                            = departmentSet.departments.getGroup(
                                                                a)
                                                    for (var b = 0; b != groupName.length; b++) {

                                                        if (departmentChoose.gro1.groupName
                                                                === groupName[b])
                                                            groupSelect[b] = departmentSelect[index]
                                                    }
                                                    for (var c = 0; c
                                                         !== departmentChoose.gro1.employeeCount(
                                                             ); c++) {
                                                        departmentChoose.emp1
                                                                = departmentChoose.gro1.getEmployee(
                                                                    c)
                                                        for (var b = 0; b
                                                             != employeeID.length; b++) {
                                                            if (departmentChoose.emp1.userID
                                                                    === employeeID[b])
                                                                if (departmentSelect[index]
                                                                        === listAllChoose)
                                                                    employeeSelect[b] = true
                                                                else
                                                                    employeeSelect[b] = false
                                                        }
                                                    }
                                                }
                                                refresh()
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
                                    Row {
                                        width: parent.width
                                        height: mainWindow.height * 0.06
                                        spacing: 10
                                        Image {
                                            id: groupChoose
                                            property Employee emp2
                                            width: parent.height * 0.5
                                            height: parent.height * 0.5
                                            anchors.verticalCenter: parent.verticalCenter
                                            source: {
                                                for (var i = 0; i != groupName.length; i++) {
                                                    if (groupSet.groups.groupName === groupName[i])
                                                        return groupSelect[i]
                                                }
                                            }
                                            MouseArea {
                                                anchors.fill: parent
                                                onClicked: {
                                                    for (var i = 0; i != groupName.length; i++) {
                                                        if (groupSet.groups.groupName
                                                                === groupName[i]) {
                                                            if (groupSelect[i] === listAllChoose)
                                                                groupSelect[i] = listAllNotChoose
                                                            else
                                                                groupSelect[i] = listAllChoose
                                                            for (var b = 0; b
                                                                 !== groupSet.groups.employeeCount(
                                                                     ); b++) {
                                                                groupChoose.emp2 = groupSet.groups.getEmployee(
                                                                            b)
                                                                for (var a = 0; a
                                                                     !== employeeID.length; a++) {
                                                                    if (groupChoose.emp2.userID === employeeID[a]) {
                                                                        employeeSelect[a] = groupSelect[i] === listAllChoose ? true : false
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                    refresh()
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
                                                        for (var i = 0; i
                                                             != employeeID.length; i++) {
                                                            if (employeeSet.employees.userID
                                                                    === employeeID[i])
                                                                return employeeSelect[i]
                                                        }
                                                    }
                                                    onClicked: {
                                                        for (var i = 0; i
                                                             != employeeID.length; i++) {
                                                            if (employeeSet.employees.userID
                                                                    === employeeID[i])
                                                                employeeSelect[i]
                                                                        = employeeChoose.checked
                                                        }
                                                        //                                                        refresh()
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
