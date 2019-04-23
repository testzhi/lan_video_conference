#include "videoconferencingserver.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonArray>


using std::cout;
using std::endl;
using std::string;
using namespace boost::asio;
using namespace boost::posix_time;

void VideoConferencingServer::accept()
{
    sock_ptr sock(new socket_type(m_io));
    m_acceptor.async_accept(*sock,boost::bind(&VideoConferencingServer::handle_accepter,this, boost::asio::placeholders::error, sock));
}
void VideoConferencingServer::handle_accepter(const boost::system::error_code &ec, VideoConferencingServer::sock_ptr sock)
{
    if(ec)
        return;
    _remote_endpoint = sock->remote_endpoint();
    cout  << "Client: "<< sock->remote_endpoint() << "已连接"<<endl;

//    sock->async_send()
    sock->async_receive(buffer(m_tcpRecvBuf), boost::bind(&VideoConferencingServer::tcpHandleReceive, this, boost::asio::placeholders::error, sock, sock->remote_endpoint().address().to_string()));
    accept();
}
void VideoConferencingServer::run()
{
    m_io.run();
}

void VideoConferencingServer::tcpHandleReceive(const boost::system::error_code &ec, VideoConferencingServer::sock_ptr sock, std::string _remote_ip)
{
    std::string receive_message;

    for(int i = 0;i != BUFFER_LENGTH; i++)
    {
        if (m_tcpRecvBuf[i] != '\0')
            receive_message.push_back(m_tcpRecvBuf[i]);
    }
    QJsonObject Data = stringToQJsonObject(receive_message);

    if(receive_message.length() != 0)
        cout << "来自客户端的数据：" << receive_message << endl;
    receive_message.clear();

    string type = Data["TYPE"].toString().toStdString();

    if(type == "#REGISTER") //处理注册请求
        handleRegister(Data, sock);
    else if(type == "#LOGIN") //处理登录请求
        handleLogin(Data, _remote_ip,sock);
    else if(type == "#EXIT")
        handleExit(Data, sock);
    else if(type == "#REQUEST_ACCOUNT_DETAIL")
        handleAccountDetail(Data, sock);
    else if(type == "#REQUEST_COLLEAGUE_LIST")
        handleColleagueList(Data, sock);
    else if(type == "#REQUEST_MEETING_INVITIONS_LIST")
        handleInvitionsList(Data, sock);
    else if(type == "#REQUEST_LAUNCH_MEETING")
        handleRequestLaunchMeeting(Data, sock);
    else if(type == "#REQUEST_START_MEETING")
        handleRequestStartMeeting(Data, sock);
    else if(type == "#REQUEST_STOP_MEETING")
        handleRequestStopMeeting(Data, sock);

    sock->async_receive(buffer(m_tcpRecvBuf), boost::bind(&VideoConferencingServer::tcpHandleReceive,this, boost::asio::placeholders::error,sock,_remote_ip));
}

void VideoConferencingServer::tcpSendMessage(std::string msg, VideoConferencingServer::sock_ptr sock)
{
    for(int i = 0;i != BUFFER_LENGTH; i++)
    {
        if(i < msg.size())
            m_tcpSendBuf[i] = msg[i];
        else m_tcpSendBuf[i] = '\0';
    }
    cout  << "-------" << "当前服务端输出：" << m_tcpSendBuf.data();
    async_write(*sock, boost::asio::buffer(m_tcpSendBuf), boost::bind(&VideoConferencingServer::handleTcpSend, this, boost::asio::placeholders::error,sock));
}
void VideoConferencingServer::handleTcpSend(const boost::system::error_code &ec, VideoConferencingServer::sock_ptr sock)
{
    cout << "-------" <<"发送完毕" << endl;
}


//处理函数
void VideoConferencingServer::handleRegister(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{

    string email = Data.value("DATA")["EMAIL"].toString().toStdString();

    string tcpJson, id;
    int res;
    dc.jsonStrCreateRegisteredID(tcpJson, email, id, res);

    string realName = Data.value("DATA")["REALNAME"].toString().toStdString();
    string passwd = Data.value("DATA")["PASSWD"].toString().toStdString();
    string avatar = Data.value("DATA")["AVATAR"].toString().toStdString();
    string company = Data.value("DATA")["COMPANY"].toString().toStdString();
    string department = Data.value("DATA")["DEPARTMENT"].toString().toStdString();
    string group = Data.value("DATA")["GROUP"].toString().toStdString();
    string phone = Data.value("DATA")["PHONE"].toString().toStdString();

    if(res == 1)
        dc.getDb().insertIntoTableEmployees(id, passwd, realName, email, group, department, company, "");
    tcpSendMessage(tcpJson, sock);
}
void VideoConferencingServer::handleLogin(QJsonObject Data, string ip, VideoConferencingServer::sock_ptr sock)
{
    string emailid = Data.value("DATA")["EMAILID"].toString().toStdString();
    string passwd = Data.value("DATA")["PASSWD"].toString().toStdString();

    string verifyRes;
    int result;
    dc.jsonStrVerifyAccountResult(emailid, passwd, verifyRes, result);

    if(result == 1)
    {
        dc.getDb().updateStateByEmaiID(emailid, 1, ip);
    }
    cout << "登录反馈发送前的json str： " << verifyRes <<endl;;
    tcpSendMessage(verifyRes, sock);
}
void VideoConferencingServer::handleExit(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string tcpJson;
    string emailid = Data.value("DATA")["FROM"].toString().toStdString();

    string verifyRes;
    dc.getDb().updateStateByEmaiID(emailid, 0, "");
}
void VideoConferencingServer::handleAccountDetail(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    int res;
    dc.jsonStrAccountDetail(emailID, tcpJson, res);
    if(res == 1)
        tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleColleagueList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    int res;
    dc.jsonStrColleagueDetail(emailID, tcpJson, res);
    cout << tcpJson;
    if(res == 1)
        tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleInvitionsList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    unsigned long long res;
    dc.jsonStrInvitationsDetail(emailID, tcpJson, res);
    cout << tcpJson;
//    if(res == 1)
//        tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleMeetingList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    unsigned long long res;
    dc.jsonStrMeetingsDetail(emailID, tcpJson, res);
    cout << tcpJson;
//    if(res == 1)
//        tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleRequestLaunchMeeting(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
//    string initiator = Data.value("DATA")["INITIATOR"].toString().toStdString();
    string assistant = Data.value("DATA")["ASSISTANT"].toString().toStdString();
    string speaker = Data.value("DATA")["SPEAKER"].toString().toStdString();
    string date = Data.value("DATA")["DATE"].toString().toStdString();
    string time = Data.value("DATA")["TIME"].toString().toStdString();
    int catagro = Data.value("DATA")["CATAGRO"].toInt();
    string subject = Data.value("DATA")["SUBJECT"].toString().toStdString();
//    string name = Data.value("DATA")["MEETINGNAME"].toString().toStdString();
    int scale = Data.value("DATA")["MEETINGSCALE"].toInt();
    int preDura = Data.value("DATA")["PREDICTEDDURATION"].toInt();
    string remark = Data.value("DATA")["REMARK"].toString().toStdString();


    string tcpJson, id;
    unsigned long long meetingid = dc.getDb().insertIntoTableMeetings(assistant, speaker, date, time, catagro, subject, scale, preDura, remark);
    if(meetingid != 0)
    {
        string mm = std::to_string(meetingid);
        dc.jsonStrLaunchMeetingResult(meetingid, tcpJson);
        dc.getDb().insertIntoTableAttendees(mm, assistant);
        dc.getDb().insertIntoTableAttendees(mm, speaker);


        QJsonArray attendeesArray =  Data.value("DATA")["ATTENDEES"].toArray();
        for(auto attendee : attendeesArray)
        {
            QJsonObject per = attendee.toObject();
            string userid = per.value("EMAILID").toString().toStdString();
            dc.getDb().insertIntoTableAttendees(mm, userid);
            dc.getDb().insertIntoTableNotifications(userid, emailID, 1, subject, 0, mm);
            //向其他人发会议邀请
            //            找userid对应ip？
            //        向其他人广播？？客户端请求他人IP，服务器回馈IP给客户端UDP发送？


        }
//        tcpSendMessage(tcpJson, sock);
    }
}

void VideoConferencingServer::handleRequestStartMeeting(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
    string meetingID = Data.value("DATA")["MEETINGID"].toString().toStdString();

    string tcpJson, id;
    dc.getDb().updateMeetingStateByMeetingID(meetingID, 1);
    //告诉其他人发会议状态更改
    //            找userid对应ip？
    //        向其他人广播？？客户端请求他人IP，服务器回馈IP给客户端UDP发送？
}

void VideoConferencingServer::handleRequestStopMeeting(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
    string meetingID = Data.value("DATA")["MEETINGID"].toString().toStdString();

    string tcpJson, id;
    dc.getDb().updateMeetingStateByMeetingID(meetingID, 2);
    //告诉其他人发会议状态更改
    //            找userid对应ip？
    //        向其他人广播？？客户端请求他人IP，服务器回馈IP给客户端UDP发送？
}



QJsonObject VideoConferencingServer::stringToQJsonObject(std::string string)
{
    QString qString = QString::fromStdString(string);
    QJsonObject DATA = QJsonDocument::fromJson(qString.toUtf8()).object();

    return DATA;
}
