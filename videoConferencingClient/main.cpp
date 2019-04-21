#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include "conferenceui.h"
#include "videoconferencingclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);



    QQmlApplicationEngine engine;
    qmlRegisterType<Employee>("Meeting",1,0,"Employee");
    qmlRegisterType<Meeting>("Meeting",1,0,"Meeting");
    qmlRegisterType<Company>("Meeting",1,0,"Company");
    qmlRegisterType<Department>("Meeting",1,0,"Department");
    qmlRegisterType<Group>("Meeting",1,0,"Group");
    Employee employee;
    employee.setUserID("00");
    employee.setRealName("lzy");
    Employee employee1;
    employee1.setUserID("01");
    employee1.setRealName("xly");
    Employee employee2;
    employee2.setUserID("02");
    employee2.setRealName("zjm");
    Employee employee3;
    employee3.setUserID("03");
    employee3.setRealName("lzd");
    Employee employee4;
    employee4.setUserID("04");
    employee4.setRealName("lxy");
    Group group0;
    group0.insertEmplyee(&employee);
    group0.insertEmplyee(&employee1);
    group0.setGroupName("Ginkgoes");
    Group group1;
    group1.insertEmplyee(&employee2);
    group1.setGroupName("SunBirds");
    Group group2;
    group2.insertEmplyee(&employee3);
    group2.setGroupName("Abc");
    Department department;
    department.setDepartmentName("3G");
    department.insertGroup(&group0);
    department.insertGroup(&group1);
    Department department1;
    department1.setDepartmentName("4G");
    department1.insertGroup(&group2);
    Company company;
    company.setCompanyName("tieto");
    company.insertDepartment(&department);
    company.insertDepartment(&department1);
    Meeting meeting("许林玉","李章玉","四月十七号","15：00","Dspreader","12","90分钟","讨论","0");
    Meeting meetings("l李章玉","许林玉","五月十七号","16：00","聊天","12","90分钟","讨论","0");
    employee.insertMeeting(&meeting);
    employee.insertMeeting(&meetings);
    ConferenceUI conferenceUI;
    conferenceUI.setCompany(&company);
    conferenceUI.setEmployee(&employee);
    VideoConferencingClient *client = new VideoConferencingClient();
    client->threadTcpReceive();
    conferenceUI.setVideoConferencing(client);
    conferenceUI.getVideoConferencing()->setEmployee(conferenceUI.employee());
    conferenceUI.getVideoConferencing()->setCompany(conferenceUI.company());
    engine.rootContext()->setContextProperty("conferenceUI",&conferenceUI);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
