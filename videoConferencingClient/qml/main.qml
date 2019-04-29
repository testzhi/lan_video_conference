import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Meeting 1.0
import QtGraphicalEffects 1.0

Window {
    id: mainWindow
    property string listOpen: "../resources/listDown.ico"
    property string listClose: "../resources/listUp.ico"
    property string listAllChoose: "../resources/check.png"
    property string listAllNotChoose: "../resources/notCheck.png"
    visible: true
    width: 400
    height: 600
    Login {
        id: login
        onLogin: {
            mainWindow.width = 960
            mainWindow.height = 640
            homeLoader.sourceComponent = homeComponent
            login.visible = false
        }
    }
    Loader {
        anchors.fill: parent
        id: homeLoader
    }

    Component {
        id: homeComponent
        Home {
            id: home
            onExit: {
                mainWindow.width = 400
                mainWindow.height = 600
                homeLoader.sourceComponent = null
                login.visible = true
            }
        }
    }
}
