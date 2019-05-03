#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include "conferenceui.h"
#include "videoconferencingclient.h"
#include "xvideo.h"
#include "xscreen.h"
#include "videorecv.h"

//#define PORT_BASE     1234


//void checkerror(int rtperr)
//{
//    if (rtperr < 0)
//    {
//        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
//        exit(-1);
//    }
//}
//void StartReceive();

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);



//    StartReceive();

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
    ConciseEmployee *employee0 = new ConciseEmployee();
    employee0->setUserID("00");
    employee0->setRealName("lzy");
    ConciseEmployee *employee1 = new ConciseEmployee();
    employee1->setUserID("01");
    employee1->setRealName("xly");
    ConciseEmployee *employee2 = new ConciseEmployee();
    employee2->setUserID("02");
    employee2->setRealName("zjm");
    ConciseEmployee *employee3 = new ConciseEmployee();
    employee3->setUserID("03");
    employee3->setRealName("lzd");
    ConciseEmployee *employee4 = new ConciseEmployee();
    employee4->setUserID("04");
    employee4->setRealName("lxy");
    Group group0;
    group0.insertConciseEmployee(employee0);
    group0.insertConciseEmployee(employee1);
    group0.setGroupName("Ginkgoes");
    Group group1;
    group1.insertConciseEmployee(employee2);
    group1.setGroupName("SunBirds");
    Group group2;
    group2.insertConciseEmployee(employee3);
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
    Meeting meeting("许林玉","李章玉","4.17","15：00","Dspreader","12","90分钟","讨论","0");
    Meeting meetings("l李章玉","许林玉","5.17","16：00","聊天","12","90分钟","讨论","0");
    Meeting meeting1("许林玉","李章玉","4.17","9：00","Dspreader","12","90分钟","讨论","0");
    Notification notification;
    notification.setNotificationCategory("Meeting");
    notification.setNotificationMessage("zjm invote 4.30 9:00 meeting");
    Notification notification1;
    notification1.setNotificationCategory("Meeting");
    notification1.setNotificationMessage("xly invote 5.3 10:00 meeting");
    Employee employee;
    employee.insertNotification(&notification);
    employee.insertNotification(&notification1);
    employee.sortMeeting();
    ConferenceUI conferenceUI;
    employee.setCompanys(&company);
    conferenceUI.setEmployee(&employee);
    VideoConferencingClient *client = new VideoConferencingClient();
    client->threadTcpReceive();
    client->threadUdpOnlineReceive();


    conferenceUI.setVideoConferencing(client);
    conferenceUI.getVideoConferencing()->setEmployee(conferenceUI.employee());
//    conferenceUI.getVideoConferencing()->setCompany(conferenceUI.company());
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


//void StartReceive()
//{
//    SVideoRecv sess;
//    sess.InitBufferSize();
//    std::string ipstr;
//    int status;


//    RTPUDPv4TransmissionParams transparams;
//    RTPSessionParams sessparams;


//    sessparams.SetOwnTimestampUnit(1.0/9000.0);

//    transparams.SetPortbase(PORT_BASE);
//    status = sess.Create(sessparams,&transparams);
//    checkerror(status);


//    RTPTime::Wait(RTPTime(1,0));
//    sess.BYEDestroy(RTPTime(10,0),0,0);
//}

