import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    anchors.fill: parent
    signal login(var userID, var userPassword)
    Column {
        id: loginPage
        anchors.centerIn: parent
        spacing: 10
        Row {
            spacing: 20
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "帐号"
            }
            TextField {
                id: account
            }
            Text {
                text: "  *"
                visible: account.text.length == 0
                color: "red"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Row {
            spacing: 20
            Text {
                anchors.verticalCenter: parent.verticalCenter
                text: "密码"
            }
            TextField {
                id: loginPassword
            }
            Text {
                text: "  *"
                visible: loginPassword.text.length == 0
                color: "red"
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "登录"
            //            anchors.centerIn: parent
            onClicked: {
                if (account.text.length === 0 || loginPassword.text.length == 0)
                    mistake.text = "信息未填写完整"
                else {
                    conferenceUI.getLoginInformation(account.text, loginPassword.text)
                    login(account.text, loginPassword.text)
                    account.text = loginPassword.text = ""
                }
            }
        }
        Text {
            id: mistake
            color: "red"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Button {
            text: "注册"
            width: 80
            height: 30
            anchors.right: parent.right
            onClicked: {
                loginPage.visible = false
                register.visible = true
            }
        }
    }
    Register {
        id: register
        visible: false
        onBack: {
            loginPage.visible = true
            register.visible = false
        }
        //        onRegister: {
        //            account.text = email
        //            loginPassword.text = password
        //            loginPage.visible = true
        //            register.visible = false
        //        }
    }
}
