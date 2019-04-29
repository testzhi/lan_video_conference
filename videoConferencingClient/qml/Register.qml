import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.12
import QtQuick.Dialogs 1.1

Item {
    signal back
    signal registerSuccess(var userID)
    anchors.fill: parent
    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        width: 30
        height: 30
        Image {
            anchors.fill: parent
            source: "../resources/back.png"
            MouseArea {
                anchors.fill: parent
                onClicked: back()
            }
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  头像      : "
            }
            Item {
                width: mainWindow.width * 0.3
                height: mainWindow.height * 0.08
                Rectangle {
                    id: img
                    width: mainWindow.height * 0.08
                    height: mainWindow.height * 0.08
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
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
            }
            Button {
                anchors.verticalCenter: parent.verticalCenter
                width: 60
                height: 30
                text: "……"
                onClicked: fileDialog.open()
                FileDialog {
                    id: fileDialog
                    nameFilters: [qsTr(
                            "PNG files(*.png) JPG files(*.jpg) JPEG files(*.jpeg) SVG files(*.svg) BMP files(*.bmp) JIF files(*.jif) PSD files(*.psd) TIFF files(*.tiff)"), qsTr(
                            "All files(*.*)")]
                    onAccepted: {
                        _image.source = fileDialog.fileUrl
                    }
                }
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "真实姓名："
            }
            TextField {
                id: name
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  *"
                color: "red"
                visible: name.text.length === 0
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  密码      : "
            }
            TextField {
                id: password
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  *"
                color: "red"
                visible: password.text.length === 0
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "确认密码："
            }
            TextField {
                id: confirm
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  *"
                color: "red"
                visible: confirm.text.length === 0
                         || confirm.text != password.text
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "所在公司："
            }
            TextField {
                id: company
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  *"
                color: "red"
                visible: company.text.length === 0
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "所属部门："
            }
            TextField {
                id: department
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  *"
                color: "red"
                visible: department.text.length === 0
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "所属组别："
            }
            TextField {
                id: group
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  *"
                color: "red"
                visible: group.text.length === 0
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  电话      : "
            }
            TextField {
                id: phone
            }
        }
        Row {
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  邮箱      : "
            }
            TextField {
                id: email
            }
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "  *"
                color: "red"
                visible: email.text.length === 0
            }
        }

        Button {
            text: "注册"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                if (name.text.length === 0 || password.text.length === 0 || confirm.text.length
                        === 0 || company.text.length === 0 || department.text.length
                        === 0 || group.text.length === 0 || email.text.length === 0) {
                    mistake.text = "信息未填写完整"
                } else if (password.text != confirm.text) {
                    mistake.text = "确认密码与密码不匹配"
                } else {
                    conferenceUI.getRegisterInformation(_image.source,
                                                        name.text,
                                                        password.text,
                                                        company.text,
                                                        department.text,
                                                        group.text, phone.text,
                                                        email.text)
                }
            }
        }
        Text {
            id: mistake
            color: "red"
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Connections {
        target: conferenceUI.employee
        onEmailAlreadyRegistered: {
            mistake.text = "该邮箱已被注册"
        }
        onRegisterSuccessfully: {
            _image.source = "../resources/avatar.png"
            name.text = password.text = company.text = department.text
                    = group.text = phone.text = email.text = confirm.text = ""
            registerSuccess(conferenceUI.employee.userID)
        }
    }
}
