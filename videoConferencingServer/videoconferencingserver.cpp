#include "videoconferencingserver.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonArray>


using std::cout;
using std::endl;
using std::string;
using namespace boost::asio;
using namespace boost::posix_time;
using std::vector;

void VideoConferencingServer::accept()
{
    sock_ptr sock(new socket_type(m_io));
    m_acceptor.async_accept(*sock,boost::bind(&VideoConferencingServer::handle_accepter,this, boost::asio::placeholders::error, sock));
}
void VideoConferencingServer::handle_accepter(const boost::system::error_code &ec, VideoConferencingServer::sock_ptr sock)
{
    if(ec)
        return;
    //    _remote_endpoint = sock->remote_endpoint();
    cout  << "Client: "<< sock->remote_endpoint() << "已连接"<<endl;

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
        cout << "#########来自客户端的数据：" << receive_message << endl;
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
    else if(type == "#REQUEST_MEETING_INVITATIONS_LIST")
        handleInvitionsList(Data, sock);
    else if(type == "#REQUEST_MEETINGS_LIST")
        handleMeetingList(Data, sock);
    else if(type == "#REQUEST_LAUNCH_MEETING")
        handleRequestLaunchMeeting(Data, sock);
    //    else if(type == "#REQUEST_START_MEETING")
    //        handleRequestStartMeeting(Data, sock);
    //    else if(type == "#REQUEST_STOP_MEETING")
    //        handleRequestStopMeeting(Data, sock);
    else if(type == "#REQUEST_SEND_INVITATION_RESULT")
        handleRequestInvitionResult(Data, sock);

    sock->async_receive(buffer(m_tcpRecvBuf), boost::bind(&VideoConferencingServer::tcpHandleReceive,this, boost::asio::placeholders::error,sock,_remote_ip));
}
void VideoConferencingServer::tcpSendMessage(std::string msg, VideoConferencingServer::sock_ptr sock)
{
    cout  << "-------" << "当前服务端输出：" << msg;
    async_write(*sock, boost::asio::buffer(msg), boost::bind(&VideoConferencingServer::handleTcpSend, this, boost::asio::placeholders::error, sock));
}
void VideoConferencingServer::handleTcpSend(const boost::system::error_code &ec, VideoConferencingServer::sock_ptr sock)
{
    cout << "-------" <<"发送完毕" << endl;
}

void VideoConferencingServer::tcpSendTo(std::string ip, std::string msg)
{
    boost::asio::ip::tcp::endpoint send_ep(boost::asio::ip::address::from_string(ip), 2444);

    cout  << "～～～～～～" << "当前服务端发送：" << msg;
    if(!m_sockTcp.is_open())
    {
        m_sockTcp.open(ip::tcp::v4());
        m_sockTcp.connect(send_ep);
    }
    m_sockTcp.send(boost::asio::buffer(msg));
    cout << "～～～～～～" <<"发送完毕" << endl;
    //    m_sockTcp.close();
}

void VideoConferencingServer::tcpAsyncConnect(std::string ip, std::string msg)
{
    if(!m_sockTcp.is_open())
    {
        m_sockTcp.open(ip::tcp::v4());
        boost::asio::ip::tcp::endpoint send_ep(boost::asio::ip::address::from_string(ip), 2444);
        m_sockTcp.async_connect(send_ep, boost::bind(&VideoConferencingServer::tcpAsyncConnectionHandler, this, msg, boost::asio::placeholders::error));
    }
    else {
        cout << "*******" <<"异步发送给" << /*m_sockTcp.remote_endpoint() << " 内容： "<<*/ msg;
        m_sockTcp.async_send(boost::asio::buffer(msg), boost::bind(&VideoConferencingServer::tcpAsyncSendToHandler, this, boost::asio::placeholders::error));
    }
}
void VideoConferencingServer::tcpAsyncConnectionHandler(std::string msg, const boost::system::error_code &ec)
{
    cout << "*******" <<"异步连接成功,异步发送给 " << /*m_sockTcp.remote_endpoint() << " 内容： "<<*/ msg;
    m_sockTcp.async_send(boost::asio::buffer(msg), boost::bind(&VideoConferencingServer::tcpAsyncSendToHandler, this, boost::asio::placeholders::error));
}
void VideoConferencingServer::tcpAsyncSendToHandler(const boost::system::error_code &ec)
{
    cout << "*******" <<"发送完毕" << endl;
    m_sockTcp.close();
}

void VideoConferencingServer::udpSendMessage(std::string ip, std::string msg)
{
    boost::asio::ip::udp::endpoint send_ep(boost::asio::ip::address::from_string(ip),2444);

    cout  << "=========" << "当前UDP服务端输出：" << msg;
    m_sockUdp.async_send_to(boost::asio::buffer(msg), send_ep,
                            boost::bind(&VideoConferencingServer::handleUdpSend, this,
                                        boost::asio::placeholders::error));
}
void VideoConferencingServer::handleUdpSend(const boost::system::error_code &ec)
{
    cout << "=========" <<"UDP发送完毕" << endl;
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
    tcpSendMessage(verifyRes, sock);
}
void VideoConferencingServer::handleExit(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string tcpJson;
    string emailid = Data.value("DATA")["FROM"].toString().toStdString();

    if(!emailid.empty())
        dc.getDb().updateStateByEmaiID(emailid, 0, "");
}
void VideoConferencingServer::handleAccountDetail(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    int res;
    dc.jsonStrAccountDetail(emailID, tcpJson, res);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleColleagueList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    int res;
    dc.jsonStrColleagueDetail(emailID, tcpJson, res);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleInvitionsList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson;
    unsigned long long res;
    dc.jsonStrInvitationsDetail(emailID, tcpJson, res);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleMeetingList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    unsigned long long res;
    dc.jsonStrMeetingsDetail(emailID, tcpJson, res);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleRequestLaunchMeeting(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    QJsonObject r_data;

    string assistant = Data.value("DATA")["FROM"].toString().toStdString();//与assistant同一人
    //    string initiator = Data.value("DATA")["INITIATOR"].toString().toStdString();
    //    string assistant = Data.value("DATA")["ASSISTANT"].toString().toStdString();
    string speaker = Data.value("DATA")["SPEAKER"].toString().toStdString();
    string date = Data.value("DATA")["DATE"].toString().toStdString();
    string time = Data.value("DATA")["TIME"].toString().toStdString();
    int catagro = Data.value("DATA")["CATEGORY"].toInt();
    string subject = Data.value("DATA")["SUBJECT"].toString().toStdString();
    //    string name = Data.value("DATA")["MEETINGNAME"].toString().toStdString();
    int scale = Data.value("DATA")["MEETINGSCALE"].toInt();
    int preDura = Data.value("DATA")["PREDICTEDDURATION"].toInt();
    string remark = Data.value("DATA")["REMARK"].toString().toStdString();


    string tcpJson, id;
    unsigned long long meetingid = dc.getDb().insertIntoTableMeetings(assistant, speaker, date, time, catagro, subject, scale, preDura, remark);
    string mm = std::to_string(meetingid);


    dc.jsonStrLaunchMeetingResult(meetingid, tcpJson);
    dc.getDb().insertIntoTableAttendees(mm, assistant, 1, "");
    string aip;
    int aaa = dc.getDb().queryIpByUserID(assistant, 1, aip);
    if(aaa == 1)//助手
    {
        //若在线 重新发邀请列表json
        int a_res;
        string a_jsonstr;
        dc.jsonStrMeetingAddDetail(mm, a_jsonstr, a_res);
        //                tcpSendTo(sip, s_jsonstr);
        //                tcpAsyncConnect(sip, s_jsonstr);
        udpSendMessage(aip, a_jsonstr);
    }
    //邮件

    if(meetingid > 0)
    {
        if(!isSameString(assistant, speaker))//演讲者
        {
            dc.getDb().insertIntoTableAttendees(mm, speaker, 1, "");
            //邮件
            //            //暂定不向speaker发会议邀请×
            string sip;
            int ss = dc.getDb().queryIpByUserID(speaker, 1, sip);
            if(ss == 1)
            {
                //若在线 重新发邀请列表json
                int s_res;
                string s_jsonstr;
                dc.jsonStrMeetingAddDetail(mm, s_jsonstr, s_res);
                //                tcpSendTo(sip, s_jsonstr);
                //                tcpAsyncConnect(sip, s_jsonstr);
                udpSendMessage(sip, s_jsonstr);

            }
        }


        QJsonArray attendeesArray =  Data.value("DATA")["ATTENDEES"].toArray();
        for(auto attendee : attendeesArray)
        {
            QJsonObject per = attendee.toObject();
            string userid = per.value("EMAILID").toString().toStdString();
            if((!isSameString(userid, assistant)) )
            {
                if(!isSameString(userid, speaker))
                {
                    dc.getDb().insertIntoTableAttendees(mm, userid);
                    dc.getDb().insertIntoTableNotifications(userid, assistant, 1, subject, 0, mm);
                    //邮件
                    string atten_ip;
                    atten_ip.clear();
                    int aa = dc.getDb().queryIpByUserID(userid, 1, atten_ip);
                    if(aa == 1)
                    {
                        //若在线 向其他人发会议邀请json
                        //            找userid对应ip？
                        //        向其他人广播？？客户端请求他人IP，服务器回馈IP给客户端UDP发送？
                        string atten_invi_jsonstr;
                        atten_invi_jsonstr.clear();
                        unsigned long long atten_invi_res = 0;
                        dc.jsonStrInvitationAddDetail(mm, atten_invi_jsonstr, atten_invi_res);
                        //                    tcpSendTo(atten_ip, atten_invi_jsonstr);
                        //                    tcpAsyncConnect(atten_ip, atten_invi_jsonstr);
                        udpSendMessage(atten_ip, atten_invi_jsonstr);
                    }
                }
            }
        }
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
    //    dc.
    //告诉其他人发会议状态更改
    //            找userid对应ip？
    //        向其他人广播？？客户端请求他人IP，服务器回馈IP给客户端UDP发送？
}

void VideoConferencingServer::handleRequestInvitionResult(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
    string meetingID = Data.value("DATA")["MEETINGID"].toString().toStdString();
    string result = Data.value("DATA")["RESULT"].toString().toStdString();
    string cause = Data.value("DATA")["CAUSE"].toString().toStdString();

    dc.getDb().deleteNotificationByUserIDAndMeetingID(emailID, meetingID);

    if(result == "0")
        dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, emailID, -1, cause);
    else
    {
        dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, emailID, 1, "");//暂时未考虑迟到0
        QJsonObject meeting;
        vector<string> data;
        dc.getDb().queryMeetingDetailsOnlyByMeetingID(meetingID, data);
        meeting.insert("MEETINGID", meetingID.c_str());
        //            meeting.insert("INITIATOR", data[1].c_str());
        meeting.insert("ASSISTANT", data[2].c_str());
        string assistantName;
        dc.getDb().queryNameByUserID(meetingID, assistantName);
        meeting.insert("ASSISTANTNAME", assistantName.c_str());
        string speakerName;
        dc.getDb().queryNameByUserID(meetingID, speakerName);
        meeting.insert("SPEAKER", data[3].c_str());
        meeting.insert("SPEAKERNAME", speakerName.c_str());
        meeting.insert("DATE", data[4].c_str());
        meeting.insert("TIME", data[5].c_str());
        meeting.insert("CATEGORY", data[6].c_str());
        //            meeting.insert("MEETINGNAME", data[8].c_str());
        //            meeting.insert("OWNUNIT", data[9].c_str());
        meeting.insert("MEETINGSCALE", data[10].c_str());
        meeting.insert("PREDICTEDDURATION", data[11].c_str());
        meeting.insert("MEETINGSTATE", data[14].c_str());
        meeting.insert("REMARK", data[15].c_str());
        meeting.insert("SUBJECT", data[7].c_str());
        QJsonObject json;
        json.insert("DATA", QJsonValue(meeting));
        json.insert("TYPE", "_REPLY_INVITATION");
        QJsonDocument document;
        document.setObject(json);
        QByteArray byteArray = document.toJson(QJsonDocument::Compact);
        std::string strJson(byteArray);
        tcpSendMessage(strJson, sock);
    }
}

void VideoConferencingServer::handleRequestAttendMeeting(QJsonObject Data, VideoConferencingServer::sock_ptr)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
    string meetingID = Data.value("DATA")["MEETINGID"].toString().toStdString();
    dc.getDb().insertIntoTableAttendees(meetingID, emailID, 1, "");
}



QJsonObject VideoConferencingServer::stringToQJsonObject(std::string string)
{
    QString qString = QString::fromStdString(string);
    QJsonObject DATA = QJsonDocument::fromJson(qString.toUtf8()).object();

    return DATA;
}

bool VideoConferencingServer::isSameString(std::string s1, std::string s2)
{
    if(s1 == s2)
        return true;
    return false;
}
