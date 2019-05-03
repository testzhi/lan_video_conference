#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include "conferenceui.h"
#include "videoconferencingclient.h"
#include "xvideo.h"
#include "xscreen.h"

//void startReceive();

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<ConferenceUI>("Meeting",1,0,"ConferenceUI");
    qmlRegisterType<Employee>("Meeting",1,0,"Employee");
    qmlRegisterType<Meeting>("Meeting",1,0,"Meeting");
    qmlRegisterType<Company>("Meeting",1,0,"Company");
    qmlRegisterType<Department>("Meeting",1,0,"Department");
    qmlRegisterType<Group>("Meeting",1,0,"Group");
    qmlRegisterType<Notification>("Meeting",1,0,"Notification");
    qmlRegisterType<ConciseEmployee>("Meeting",1,0,"ConciseEmployee");
    qmlRegisterType<Attendee>("Meeting",1,0,"Attendee");
    qmlRegisterType<XVideo>("Meeting",1,0,"XVideo");
    qmlRegisterType<XScreen>("Meeting",1,0,"XScreen");
    Employee *employee = new Employee();
    ConferenceUI conferenceUI;
    employee->threadReceive();
    conferenceUI.setEmployee(employee);
    VideoConferencingClient *client = new VideoConferencingClient();
    client->threadTcpReceive();
    client->threadUdpOnlineReceive();

    conferenceUI.setVideoConferencing(client);
    conferenceUI.getVideoConferencing()->setEmployee(conferenceUI.employee());
    engine.rootContext()->setContextProperty("conferenceUI",&conferenceUI);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto i = app.exec();
    if(i  ==  0)
    {
//        std::string userID = conferenceUI.employee()->userID().toStdString();
//        conferenceUI.getVideoConferencing()->requestExit(userID);
        conferenceUI.getExitMessage();
    }


    return app.exec();
}
