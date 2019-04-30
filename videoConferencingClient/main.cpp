#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>
#include "conferenceui.h"
#include "videoconferencingclient.h"
#include "xvideo.h"
#include "xscreen.h"

#include "videosender.h"


//测试数据--------------------
#define SSRC           100
#define DEST_PORT     2222
#define BASE_PORT     2222
//测试数据结束-----------------

void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
//        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

void SetRTPParams(SVideoSender& sess,uint32_t destip,uint16_t destport,uint16_t baseport)
{
    int status;
    //RTP+RTCP库初始化SOCKET环境
    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/90000.0); //时间戳单位
    sessparams.SetAcceptOwnPackets(true);	//接收自己发送的数据包
    sessparams.SetUsePredefinedSSRC(true);  //设置使用预先定义的SSRC
    sessparams.SetPredefinedSSRC(SSRC);     //定义SSRC

    transparams.SetPortbase(baseport);

    status = sess.Create(sessparams,&transparams);
    CheckError(status);

    destip = ntohl(destip);
    RTPIPv4Address addr(destip,destport);
    status = sess.AddDestination(addr);
    CheckError(status);

}

void testH264SendAndRecive()
{
    SVideoSender sender;

    sender.InitBufferSize();

    std::string destip_str = "127.0.0.1";
    uint32_t dest_ip = inet_addr(destip_str.c_str());

    SetRTPParams(sender,dest_ip,DEST_PORT,BASE_PORT);
    sender.SetParamsForSendingH264();


    FILE *fp_open;
    uint8_t buff[1024*5] = {0};
    int  bufsize = 1024; //每次读1024字节,谁便取，不超过1400就行

    fp_open = fopen("out.h264","rb");
    while( !feof(fp_open) )
    {
        int true_size = fread(buff,1,bufsize,fp_open);  //读一次，内部位移
        printf("\n--> read file %d bytes",true_size);
        sender.SendH264Nalu(buff,true_size);     // 每次发送固定大小的数据
        RTPTime::Wait(0.005); //间隔5毫秒
    }

}

//int main(void)
//{
//    testH264SendAndRecive();

//    return 0;
//}


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
