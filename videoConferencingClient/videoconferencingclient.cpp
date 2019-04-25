#include "videoconferencingclient.h"
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <QDebug>
#include <thread>
#include <iostream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>

using std::cout;
using std::endl;
using std::string;


VideoConferencingClient::VideoConferencingClient()
    :m_sockTcp(m_io), m_tcpEP(ip::address::from_string("192.168.43.174"), 2333)
{
    m_sockTcp.connect(m_tcpEP);
}
//TCP
void VideoConferencingClient::threadTcpReceive()
{
    boost::thread threadTcp(boost::bind(&VideoConferencingClient::tcpReceiveMessage, this));
    threadTcp.detach();
}
void VideoConferencingClient::tcpReceiveMessage()
{
    for(int i = 0; i != BUFFER_LENGTH; i++)
        m_tcpRecvBuf[i] = '\0';

    cout << "wait"<< endl;
    size_t readSize = 0;
    while(readSize == 0) {
        readSize = m_sockTcp.read_some(boost::asio::buffer(m_tcpRecvBuf));
    }

    string s = "";
    for(int i = 0; i != readSize; i++)
        if(m_tcpRecvBuf[i] != '\0')
            s.push_back(m_tcpRecvBuf[i]);

    cout  << "接收信息：" << s << endl;
    tcpStrResultAnalysis(s);
    tcpReceiveMessage();
}
void VideoConferencingClient::tcpStrResultAnalysis(string str)
{
    cout << "待分析语句：" << str << endl;
    QJsonObject qo = stringToQJsonObject(str);
    string type = qo["TYPE"].toString().toStdString();

    QList<QString> employeeDetail;
    QString userID, email;
    int registerResult, loginResult;
    QString err;
    if(type == "_REGISTER")
    {
        handleRegisteredResult(qo, registerResult, userID, email, err);
        if(registerResult == -1)
        {
            qDebug() << "注册失败： " << err;
            emit m_employee->emailAlreadyRegistered();
        }else if (registerResult == 1)
            m_employee->registerSuccessfully();
    }
    else if (type == "_LOGIN")
    {
        handleLoginResult(qo, loginResult, err);
        cout << "loginResult  " << loginResult << endl;
        if(loginResult != 1) {
            qDebug() << "登录失败： " << err;
            emit m_employee->loginFailed(err);
        }else {
            requestAccountDetail(m_employee->userID().toStdString());
            emit m_employee->loginSucceeded("LoginSucceed");
        }
    }
    else if (type == "_INITIALIZE_ACCOUNT_DETAIL")
    {
        handleInitAccountDetailResult(qo,employeeDetail);
        m_employee->setUserID(employeeDetail.at(0));
        m_employee->setEmail(employeeDetail.at(1));
        m_employee->setRealName(employeeDetail.at(2));
        m_employee->setAvatar(employeeDetail.at(3));
        m_employee->setCompany(employeeDetail.at(4));
        m_employee->setDepartment(employeeDetail.at(5));
        m_employee->setGroup(employeeDetail.at(6));
        m_employee->setPhone(employeeDetail.at(7));
        requestColleagueList(m_employee->userID().toStdString());
    }
    else if (type == "_INITIALIZE_COLLEAGUE_LIST")
    {
        handleInitColleagueListResult(qo);
        cout << "department count  " <<  m_employee->companys()->departmentCount() << endl;
        for(int i = 0;i != m_employee->companys()->departmentCount();i++) {
            cout << "department name  " << m_employee->companys()->getDepartment(i)->departmentName().toStdString() << endl;
            for(int a = 0; a != m_employee->companys()->getDepartment(i)->groupCount();a++) {
                cout << "groupName  " << m_employee->companys()->getDepartment(i)->getGroup(a)->groupName().toStdString() << endl;
            }
        }
        requestMeetingInvitionsList(m_employee->userID().toStdString());
        cout << "initCompanyMessage" << endl;
        emit m_employee->loginSucceeded("CompanyMessage");

    }
    else if (type == "_INITIALIZE_MEETING_INVITATIONS_LIST")
    {
        handleInitMeetingInvitionsListResult(qo);
        cout << "initNotificationMessage" << endl;
        emit m_employee->loginSucceeded("NotificationMessage");
        requestMeetingList(m_employee->userID().toStdString());
    }
    else if (type == "_INITIALIZE_MEETINGS_LIST")
    {
        handleInitMeetingListResult(qo);
        cout << "initMeetingMessage" << endl;
        emit m_employee->loginSucceeded("MeetingMessage");
    }
    else if (type == "_LAUNCH_MEETING_RESULT")
    {
        QString err;
        handleReplyLaunchMeetingResult(qo, err);
        if(err.length() == 0) {
            emit m_employee->loginSucceeded("PublishSucceed");
            emit m_employee->loginSucceeded("MeetingMessage");
        }
        else emit m_employee->loginSucceeded(err);

    }
    else if (type == "_REPLY_INVITATION")
    {
        handleReplyInvitation(qo);
        emit m_employee->loginSucceeded("MeetingMessage");
    }
}

//RTP
void VideoConferencingClient::threadRtpReceive()
{

}
void VideoConferencingClient::rtpReceiveMessage()
{

}
void VideoConferencingClient::rtpResultAnalysis()
{

}


//REQUEST PART：客户端 发送 数据 (调用COLLECTION部分)
void VideoConferencingClient::requestRegister(string realName, string passwd, string email, QByteArray avatar, string company, string department, string group, string phoneNumber)
{
    string sendMessage = registerJsonToString(realName, passwd, email, avatar, company, department, group, phoneNumber);
    cout << "请求注册：" << sendMessage << endl;
    tcpSendMessage(sendMessage);
}
void VideoConferencingClient::requestLogin(string emailId, string passwd)
{
    string message = loginJsonToString(emailId, passwd);
    cout << "请求登录：" << message << endl;
    tcpSendMessage(message);
}
void VideoConferencingClient::requestExit(string emailId)
{
    string sendMessage = exitJsonToString(emailId);
    cout << "请求退出："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}

void VideoConferencingClient::requestAccountDetail(std::string emailId)
{
    string sendMessage = initializeAccountDetailJsonToString(emailId);
    cout << "请求账户细节信息："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}
void VideoConferencingClient::requestColleagueList(string emaiId)
{
    string sendMessage = initializeColleagueListToString(emaiId);
    cout << "请求同事列表："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}

void VideoConferencingClient::requestMeetingInvitionsList(std::string emaiId)
{
    string sendMessage = initializeMeetingInvitionsListToString(emaiId);
    cout << "请求会议受邀请列表："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}

void VideoConferencingClient::requestMeetingList(std::string emailID)
{
    string sendMessage = initializeMeetingListToString(emailID);
    cout << "请求会议列表："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}

void VideoConferencingClient::requestLaunchMeeting(std::string emailid, std::string assistant, std::string speaker, std::string date, std::string time, std::string category, std::string subject, std::string scale, std::string dura, std::string remark, std::vector<std::string> attendees)
{
    Meeting *meeting = new Meeting();
    meeting->setDate(QString::fromStdString(date));
    meeting->setTime(QString::fromStdString(time));
    meeting->setScale(QString::fromStdString(scale));
    meeting->setState(QString::fromStdString("0"));
    meeting->setTheme(QString::fromStdString(subject));
    meeting->setSpeaker(QString::fromStdString(speaker));
    meeting->setCategory(QString::fromStdString(category));
    meeting->setDuration(QString::fromStdString(dura));
    meeting->setInitiator(QString::fromStdString(assistant));
//    meeting->setMeetingID(meetingID);
    meeting->setRemark(QString::fromStdString(remark));
    mee.append(meeting);
//    m_employee->setMeetings(&mee);
    cout << "mee length  " << mee.count() << endl;
    string sendMessage = requestLaunchMeetingToString(emailid, assistant, speaker, date, time, category, subject, scale, dura, remark, attendees);
    cout << "请求发起会议："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}

void VideoConferencingClient::requestReplyMeetingInvitation(std::string emailid, std::string result, std::string meetingID, std::string cause)
{
    QList<Notification *> notification;
    for(int i = 0;i != noti.count();i++) {
        if(noti.at(i)->meetingID() != QString::fromStdString(meetingID))
            notification.append(noti.at(i));
    }
    noti = notification;
    cout << "noti length  "<< noti.count() << endl;
    m_employee->setNotifications(noti);
    cout << "noti length  "<< m_employee->notificationCount() << endl;
     emit m_employee->loginSucceeded("NotificationMessage");
    string sendMessage = requestReplyMeetingToString(emailid, result, meetingID, cause);
    cout << "请求回复通知："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}

void VideoConferencingClient::requestStartMeeting(std::string emailid, std::string meetingID)
{
    string sendMessage = requestStartMeetingToString(emailid, meetingID);
    cout << "请求开始会议："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}

void VideoConferencingClient::requestStopMeeting(std::string emailid, std::string meetingID)
{
    string sendMessage = requestStopMeetingToString(emailid, meetingID);
    cout << "请求关闭会议："  << sendMessage << endl;
    tcpSendMessage(sendMessage);
}


//HANDLE PART：客户端处理来自Server的数据
void VideoConferencingClient::handleRegisteredResult(QJsonObject qo, int &result, QString &returnID, QString &email, QString &err)
{
    err.clear();
    result = qo.value("DATA")["RESULT"].toString().toInt();
    if(result == 1)
    {
        returnID = qo.value("DATA")["USERID"].toString();
        email = qo.value("DATA")["EMAIL"].toString();
        cout << "用户ID:    " << returnID.toStdString() << endl
             << "用户Email： " << email.toStdString() << endl;
        m_employee->setUserID(returnID);
        m_employee->setEmail(email);
    } else if(qo.value("DATA")["RESULT"].toString().toInt() == -1){
        err = qo.value("DATA")["ERROR"].toString();
    }
}
void VideoConferencingClient::handleLoginResult(QJsonObject qo, int &result, QString &err)
{
    err.clear();
    QString qs = qo.value("DATA")["RESULT"].toString();
    result = qs.toInt();
    err = qo.value("DATA")["ERROR"].toString();
    //等待重新输入
}
void VideoConferencingClient::handleInitAccountDetailResult(QJsonObject qo, QList<QString> &employeeDetail)
{
    employeeDetail.append(qo.value("DATA")["USERID"].toString());
    employeeDetail.append(qo.value("DATA")["EMAIL"].toString());
    employeeDetail.append(qo.value("DATA")["REALNAME"].toString());
    employeeDetail.append(qo.value("DATA")["AVATAR"].toString());
    employeeDetail.append(qo.value("DATA")["COMPANY"].toString());
    employeeDetail.append(qo.value("DATA")["DEPARTMENT"].toString());
    employeeDetail.append(qo.value("DATA")["GROUP"].toString());
    employeeDetail.append(qo.value("DATA")["PHONE"].toString());
}

void VideoConferencingClient::handleInitColleagueListResult(QJsonObject qo)
{

    com.setCompanyName(m_employee->company());
    //    QList<Department *> departmentss;
    QJsonArray departments = qo.value("DATA")["DEPARTMENTS"].toArray();

    for(auto aDepa : departments)
    {
        if(!aDepa.isUndefined())
        {
            Department *department = new Department();
            QJsonObject aDepartment = aDepa.toObject();
            department->setDepartmentName(aDepartment.value("DEPARTMENTNAME").toString());
            QJsonArray groups = aDepartment.value("GROUPS").toArray();
            for(auto aGro : groups)
            {
                if(!aGro.isUndefined())
                {
                    Group *group = new Group();
                    QJsonObject aGroup = aGro.toObject();
                    group->setGroupName(aGroup.value("GROUPNAME").toString());
                    QJsonArray employees = aGroup.value("EMPLOYEES").toArray();
                    for(auto anEmpl : employees)
                    {
                        if(!anEmpl.isUndefined())
                        {
                            ConciseEmployee *employee = new ConciseEmployee();
                            QJsonObject anEmployee = anEmpl.toObject();
                            employee->setRealName(anEmployee.value("REALNAME").toString());
                            employee->setUserID(anEmployee.value("USERID").toString());
                            group->insertConciseEmployee(employee);
                        }
                    }
                    department->insertGroup(group);
                }
            }
            com.insertDepartment(department);
        }
    }
    cout << "xxxxxxxxxxxxxx" << endl;
    m_employee->setCompanys(&com);
}

void VideoConferencingClient::handleInitMeetingInvitionsListResult(QJsonObject qo)
{
    QJsonArray invitations = qo.value("DATA")["INVITATIONS"].toArray();
    for (auto anInvi : invitations)
    {
        QJsonObject anInvitation =  anInvi.toObject();
        if(!anInvi.isUndefined())
        {
            QString meetingID = anInvitation.value("MEETINGID").toString();
            QString assistant = anInvitation.value("ASSISTANT").toString();
            QString speaker = anInvitation.value("SPEAKER").toString();
            QString date = anInvitation.value("DATE").toString();
            QString time = anInvitation.value("TIME").toString();
            QString subject = anInvitation.value("SUBJECT").toString();
            //                int scale = anInvitation.value("MEETINGSCALE").toInt();
//            QString preDuration = anInvitation.value("PREDICTEDDURATION").toString();
            //    int state = anInvitation.value("MEETINGSTATE").toInt();
            QString remark = anInvitation.value("REMARK").toString();

            QString invitation;
            invitation.clear();
            invitation.append(assistant);   invitation.append(" 在 ");                   invitation.append(date);
            invitation.append(" ");         invitation.append(time);                    invitation.append(" 邀请您参加主题为 ");
            invitation.append(subject);     invitation.append(" 的会议  [ 主讲人：");      invitation.append(speaker);
            if(remark.isEmpty())
                invitation.append(" ]");
            else
                invitation.append("     会议说明：");    invitation.append(remark);      invitation.append(" ]");

            Notification *notification = new Notification() ;
            notification->setNotificationMessage(invitation);
            notification->setMeetingID(meetingID);
            notification->setNotificationCategory("MEETING_INVITATION");
            noti.append(notification);
        }
    }
    m_employee->setNotifications(noti);
}

void VideoConferencingClient::handleInitMeetingListResult(QJsonObject qo)
{
    QJsonArray meetings = qo.value("DATA")["MEETINGS"].toArray();
    for (auto aMeet : meetings)
    {
        QJsonObject aMeeting =  aMeet.toObject();
        if(!aMeet.isUndefined())
        {
            QString meetingID = aMeeting.value("MEETINGID").toString();
            QString assistant = aMeeting.value("ASSISTANT").toString();
            QString speaker = aMeeting.value("SPEAKER").toString();
            QString date = aMeeting.value("DATE").toString();
            QString time = aMeeting.value("TIME").toString();
            QString subject = aMeeting.value("SUBJECT").toString();
            QString scale = aMeeting.value("MEETINGSCALE").toString();
            QString category = aMeeting.value("CATEGORY").toString();
            QString preDuration = aMeeting.value("PREDICTEDDURATION").toString();
            QString state = aMeeting.value("MEETINGSTATE").toString();
            QString remark = aMeeting.value("REMARK").toString();

            Meeting *meeting = new Meeting();
            meeting->setDate(date);
            meeting->setTime(time);
            meeting->setScale(scale);
            meeting->setState(state);
            meeting->setTheme(subject);
            meeting->setSpeaker(speaker);
            meeting->setCategory(category);
            meeting->setDuration(preDuration);
            meeting->setInitiator(assistant);
            meeting->setMeetingID(meetingID);
            meeting->setRemark(remark);
            mee.append(meeting);
        }
    }
    m_employee->setMeetings(mee);
    m_employee->sortMeeting();
}

void VideoConferencingClient::handleReplyLaunchMeetingResult(QJsonObject qo, QString &err)
{
    err.clear();
    QString qs = qo.value("DATA")["RESULT"].toString();
    err = qo.value("DATA")["ERROR"].toString();
    QString meetingid = qo.value("DATA")["MEETINGID"].toString();
    mee.at(mee.count() - 1)->setMeetingID(meetingid);
    m_employee->setMeetings(mee);
    m_employee->sortMeeting();
}

void VideoConferencingClient::handleReplyInvitation(QJsonObject qo)
{
    QString meetingID = qo.value("DATA")["MEETINGID"].toString();
    QString assistant = qo.value("DATA")["ASSISTANT"].toString();
    QString speaker = qo.value("DATA")["SPEAKER"].toString();
    QString date = qo.value("DATA")["DATE"].toString();
    QString time = qo.value("DATA")["TIME"].toString();
    QString subject = qo.value("DATA")["SUBJECT"].toString();
    QString scale = qo.value("DATA")["MEETINGSCALE"].toString();
    QString category = qo.value("DATA")["CATEGORY"].toString();
    QString preDuration = qo.value("DATA")["PREDICTEDDURATION"].toString();
    QString state = qo.value("DATA")["MEETINGSTATE"].toString();
    QString remark = qo.value("DATA")["REMARK"].toString();

    Meeting *meeting = new Meeting();
    meeting->setDate(date);
    meeting->setTime(time);
    meeting->setScale(scale);
    meeting->setState(state);
    meeting->setTheme(subject);
    meeting->setSpeaker(speaker);
    meeting->setCategory(category);
    meeting->setDuration(preDuration);
    meeting->setInitiator(assistant);
    meeting->setMeetingID(meetingID);
    meeting->setRemark(remark);
    mee.append(meeting);
    m_employee->setMeetings(mee);
}


//COLLECTION PART：客户端 收集整理 数据
string VideoConferencingClient::registerJsonToString(string realName, string passwd, string email, QByteArray avatar, string company, string department, string group, string phoneNumber)
{
    QJsonObject data;

    data.insert("REALNAME", QString::fromStdString(realName));
    data.insert("PASSWD", QString::fromStdString(passwd));
    data.insert("EMAIL", QString::fromStdString(email));
    data.insert("AVATAR", QString::fromStdString(avatar.toStdString()));
    data.insert("COMPANY", QString::fromStdString(company));
    data.insert("DEPARTMENT", QString::fromStdString(department));
    data.insert("GROUP", QString::fromStdString(group));
    data.insert("PHONE", QString::fromStdString(phoneNumber));

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REGISTER");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}
string VideoConferencingClient::loginJsonToString(string emailId, string passwd)
{
    QJsonObject data;
    data.insert("EMAILID", QString::fromStdString(emailId));
    data.insert("PASSWD", QString::fromStdString(passwd));

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#LOGIN");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}
string VideoConferencingClient::exitJsonToString(string emailId)
{
    QJsonObject data;
    data.insert("FROM",QString::fromStdString(emailId));

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#EXIT");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}
string VideoConferencingClient::initializeAccountDetailJsonToString(string emailId)
{
    QJsonObject data;
    data.insert("FROM",QString::fromStdString(emailId));

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_ACCOUNT_DETAIL");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}
string VideoConferencingClient::initializeColleagueListToString(string emailId)
{
    QJsonObject data;
    data.insert("FROM",QString::fromStdString(emailId));

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_COLLEAGUE_LIST");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}

std::string VideoConferencingClient::initializeMeetingInvitionsListToString(std::string emailid)
{
    QJsonObject data;
    data.insert("FROM",QString::fromStdString(emailid));

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_MEETING_INVITATIONS_LIST");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}

std::string VideoConferencingClient::initializeMeetingListToString(std::string emailID)
{
    QJsonObject data;
    data.insert("FROM",QString::fromStdString(emailID));

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_MEETINGS_LIST");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}

std::string VideoConferencingClient::requestLaunchMeetingToString(std::string emailid, std::string assistant, std::string speaker, std::string date, std::string time, std::string category, std::string subject, std::string scale, std::string dura, std::string remark, std::vector<std::string> attendees)
{
    QJsonObject data;
    data.insert("FROM", emailid.c_str());
    data.insert("ASSISTANT",assistant.c_str());
    data.insert("SPEAKER",speaker.c_str());
    data.insert("DATE",date.c_str());
    data.insert("TIME",time.c_str());
    data.insert("CATEGORY",category.c_str());
    data.insert("SUBJECT",subject.c_str());
    data.insert("MEETINGSCALE",scale.c_str());
    data.insert("PREDICTEDDURATION",dura.c_str());
    data.insert("REMARK",remark.c_str());
    QJsonArray attendeesArray;
    for(auto m: attendees)
    {
        QJsonObject atten;
        atten.insert("EMAILID", m.c_str());
        attendeesArray.insert(0, atten);
    }
    data.insert("ATTENDEES", attendeesArray);

    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_LAUNCH_MEETING");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}

std::string VideoConferencingClient::requestReplyMeetingToString(std::string emailid,std::string result, std::string meetingID, std::string cause)
{
    QJsonObject data;
    data.insert("FROM", emailid.c_str());
    data.insert("RESULT", result.c_str());
    data.insert("MEETINGID", meetingID.c_str());
    data.insert("CAUSE", cause.c_str());
    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_SEND_INVITATION_RESULT");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}

std::string VideoConferencingClient::requestStartMeetingToString(std::string emailid, std::string meetingID)
{
    QJsonObject data;
    data.insert("FROM", emailid.c_str());
    data.insert("MEETINGID", meetingID.c_str());
    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_START_MEETING");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}

std::string VideoConferencingClient::requestStopMeetingToString(std::string emailid, std::string meetingID)
{
    QJsonObject data;
    data.insert("FROM", emailid.c_str());
    data.insert("MEETINGID", meetingID.c_str());
    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "#REQUEST_STOP_MEETING");

    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);

    return strJson;
}




void VideoConferencingClient::tcpSendMessage(string msg)
{
    for(int i = 0; i != BUFFER_LENGTH; i++)
    {
        if(i < msg.size())
            m_tcpSendBuf[i] = msg[i];
        else
            m_tcpSendBuf[i] = '\0';
    }
    cout << "写" << endl;
    write(m_sockTcp,boost::asio::buffer(m_tcpSendBuf));
}

QJsonObject VideoConferencingClient::stringToQJsonObject(string str)
{
    QString qString = QString::fromStdString(str);
    qDebug()<< qString;
    QJsonObject data = QJsonDocument::fromJson(qString.toUtf8()).object();
    return data;
}

//void VideoConferencingClient::setCompany(Company *company)
//{
//    m_company = company;
//}

void VideoConferencingClient::setEmployee(Employee *employee)
{
    m_employee = employee;
}
