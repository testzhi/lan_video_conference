#include "videoconferencingserver.h"
#include "company.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonArray>


using std::cout;
using std::endl;
using std::string;
using namespace boost::asio;
using namespace boost::posix_time;
using std::vector;

VideoConferencingServer::VideoConferencingServer()
    : m_acceptor(m_io, ip::tcp::endpoint(ip::tcp::v4(), 2333)), m_sockTcp(m_io) , m_sockUdp(m_io)
{
    m_sockUdp.open(ip::udp::v4());
    accept();
}

void VideoConferencingServer::accept()
{
    m_destIps.clear();
    sock_ptr sock(new socket_type(m_io));
    cout <<  "最大连接数" << m_acceptor.max_connections << endl;
    cout << "最大监听数" << m_acceptor.max_listen_connections << endl;
    cout << "message_peek" << m_acceptor.message_peek<<endl;
    m_acceptor.async_accept(*sock,boost::bind(&VideoConferencingServer::handle_accepter, this, boost::asio::placeholders::error, sock));
}
void VideoConferencingServer::handle_accepter(const boost::system::error_code &ec, VideoConferencingServer::sock_ptr sock)
{
    if(ec)
        return;
    cout  << "Client: "<< sock->remote_endpoint() << "已连接"<<endl;

    clearTcpRecBuffer();
    sock->async_receive(buffer(m_tcpRecvBuf), boost::bind(&VideoConferencingServer::tcpHandleReceive, this, sock, sock->remote_endpoint().address().to_string()));
    accept();
}
void VideoConferencingServer::run()
{
    m_io.run();
}

void VideoConferencingServer::tcpHandleReceive(VideoConferencingServer::sock_ptr sock, std::string _remote_ip)
{
    std::string receive_message;

    for(unsigned int i = 0;i != BUFFER_LENGTH; i++)
    {
        if (m_tcpRecvBuf[i] != '\0')
            receive_message.push_back(m_tcpRecvBuf[i]);
    }

    QJsonObject Data = stringToQJsonObject(receive_message);

    if(receive_message.length() != 0)
        cout << "#########来自客户端的数据：" << receive_message << endl;
    receive_message.clear();

    string type = Data["TYPE"].toString().toStdString();
    if(type == "#REGISTER")                                 handleRegister(Data, sock);//处理注册请求
    else if(type == "#LOGIN")                               handleLogin(Data, _remote_ip, sock);//处理登录请求
    else if(type == "#EXIT")                                handleExit(Data, sock);
    else if(type == "#REQUEST_ACCOUNT_DETAIL")              handleAccountDetail(Data, sock);
    else if(type == "#REQUEST_COLLEAGUE_LIST")              handleColleagueList(Data, sock);
    else if(type == "#REQUEST_MEETING_INVITATIONS_LIST")    handleInvitionsList(Data, sock);
    else if(type == "#REQUEST_MEETINGS_LIST")               handleMeetingList(Data, sock);
    else if(type == "#REQUEST_LAUNCH_MEETING")              handleRequestLaunchMeeting(Data, sock);
    else if(type == "#REQUEST_START_MEETING")               handleRequestStartMeeting(Data, sock);
    else if(type == "#REQUEST_STOP_MEETING")                handleRequestStopMeeting(Data, sock);
    else if(type == "#REQUEST_SEND_INVITATION_RESULT")      handleRequestInvitionResult(Data, sock);
    else if(type == "#REQUEST_ATTEND_MEETING")              handleRequestAttendMeeting(Data, sock);
    else if(type == "#REQUEST_FINISHED_MEETINGS_NOTES")     handleRequestFinishedMeetingsNotes(Data, sock);
    else if(type == "#REQUEST_UNNOTED_MEETINGS")            handleRequestUnnotedMeetings(Data, sock);
    else if(type == "#REQUEST_NOTE_MEETING")                handleRequestNoteMeeting(Data, sock);
    else if(type == "#REQUEST_START_VIDEO")                 handleRequestStartVideo(Data, sock);

    clearTcpRecBuffer();
    sock->async_receive(buffer(m_tcpRecvBuf), boost::bind(&VideoConferencingServer::tcpHandleReceive,this,  sock,_remote_ip));
}
void VideoConferencingServer::tcpSendMessage(std::string msg, VideoConferencingServer::sock_ptr sock)
{
    cout  << "-------" << "当前服务端输出：" << msg;
    async_write(*sock, boost::asio::buffer(msg), boost::bind(&VideoConferencingServer::handleTcpSend, this, boost::asio::placeholders::error, sock));
}
void VideoConferencingServer::handleTcpSend(const boost::system::error_code &ec, VideoConferencingServer::sock_ptr sock)
{
    cout << sock->remote_endpoint() << "-------" <<"发送完毕" << endl;
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
    cout << send_ep << "～～～～～～" <<"发送完毕" << endl;
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
        cout << "*******" <<"异步发送给" <</* m_sockTcp.remote_endpoint() << " 内容： "<<*/ msg;
        m_sockTcp.async_send(boost::asio::buffer(msg), boost::bind(&VideoConferencingServer::tcpAsyncSendToHandler, this, boost::asio::placeholders::error));
    }
}
void VideoConferencingServer::tcpAsyncConnectionHandler(std::string msg, const boost::system::error_code &ec)
{
    cout << "*******" <<"异步连接成功,异步发送给 " /*<< m_sockTcp.remote_endpoint() << " 内容： "*/<< msg;
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

    cout  << "=========" << "当前UDP服务端输出：" << msg <<"   ip:  " << send_ep;
    m_sockUdp.async_send_to(boost::asio::buffer(msg), send_ep,
                            boost::bind(&VideoConferencingServer::handleUdpSend, this,
                                        boost::asio::placeholders::error));
}

void VideoConferencingServer::udpSysSendMessage(std::string ip, std::string msg)
{
    boost::asio::ip::udp::endpoint send_ep(boost::asio::ip::address::from_string(ip),2444);
    cout  << "~~~~~~~~~~~" << "当前UDP服务端输出：" << msg <<"   ip:  " << send_ep;
    m_sockUdp.send_to(boost::asio::buffer(msg), send_ep);
    cout << "~~~~~~~~~~~" <<"UDP发送完毕" << endl;
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
    string realName = Data.value("DATA")["REALNAME"].toString().toStdString();
    string passwd = Data.value("DATA")["PASSWD"].toString().toStdString();
    string avatar = Data.value("DATA")["AVATAR"].toString().toStdString();
    string company = Data.value("DATA")["COMPANY"].toString().toStdString();
    string department = Data.value("DATA")["DEPARTMENT"].toString().toStdString();
    string group = Data.value("DATA")["GROUP"].toString().toStdString();
    string phone = Data.value("DATA")["PHONE"].toString().toStdString();
    jsonStrCreateRegisteredID(tcpJson, email, id, realName, passwd, avatar, group, department, company, phone);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleLogin(QJsonObject Data, string ip, VideoConferencingServer::sock_ptr sock)
{
    string emailid = Data.value("DATA")["EMAILID"].toString().toStdString();
    string passwd = Data.value("DATA")["PASSWD"].toString().toStdString();
    string verifyRes;
    jsonStrVerifyAccountResult(emailid, passwd, ip, verifyRes);
    tcpSendMessage(verifyRes, sock);
}

void VideoConferencingServer::handleExit(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string tcpJson;
    string emailid = Data.value("DATA")["FROM"].toString().toStdString();

    if(!emailid.empty())
    {
        m_adb.exit(emailid);
        vector<string> meetingIDs;
        dc.getDb().queryMeetingIDByAttendeeIDAndAttendeeState(emailid, 2, meetingIDs);
        if(!meetingIDs.empty())
        {
            for(auto &meetingid:meetingIDs)
            {
                if(!meetingid.empty())
                {
                    string speaker, assistant;
                    dc.getDb().queryMeetingSpeakerAndAssistantByMeetingID(meetingid, speaker, assistant);
                    if(emailid == speaker || emailid == assistant)
                    {
                        dc.getDb().updateMeetingStateByMeetingID(meetingid, 2);
                        dc.getDb().deleteMeetingEndUndisposedNotifications(meetingid, 1);//删除会议结束时未处理的通知
                        dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingid, emailid, 4, "");
                        vector<string> attendees;
                        dc.getDb().queryAttendeesByStateAndMeetingID(meetingid, 2, attendees);
                        dc.getDb().queryAttendeesByStateAndMeetingID(meetingid, 3, attendees);
                        string json;
                        dc.jsonStopMeeting(meetingid, json);

                        if(!attendees.empty())
                        {
                            for(auto &attendee:attendees)
                            {
                                if(attendee != emailid)
                                {
                                    dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingid, attendee, 4, "");
                                    string ip;
                                    int r2 = dc.getDb().queryIpByUserID(attendee, 1, ip);
                                    if(r2 == 1)
                                        udpSendMessage(ip, json);
                                }
                            }
                        }
                    }
                    else
                    {
                        dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingid, emailid, 3, "");
                        vector<string> attendees;
                        dc.getDb().queryAttendeesByStateAndMeetingID(meetingid, 2, attendees);
                        if(!attendees.empty())
                        {
                            string json;
                            dc.jsonExitMeeting(meetingid, emailid, json);
                            for(auto &atten : attendees)
                            {
                                string ip;
                                int r2 = dc.getDb().queryIpByUserID(atten, 1, ip);
                                if(r2 == 1)
                                    udpSendMessage(ip, json);
                            }
                        }
                    }
                }

            }
        }
    }
}
void VideoConferencingServer::handleAccountDetail(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
    string tcpJson;
    jsonStrAccountDetail(emailID, tcpJson);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleColleagueList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    int res;
    jsonStrColleagueDetail(emailID, tcpJson, res);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleInvitionsList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson;
    unsigned long long res;
    jsonStrInvitationsDetail(emailID, tcpJson, res);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleMeetingList(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();

    string tcpJson, id;
    unsigned long long res;
    jsonStrMeetingsDetail(emailID, tcpJson, res);
    tcpSendMessage(tcpJson, sock);
}

void VideoConferencingServer::handleRequestFinishedMeetingsNotes(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{

}

void VideoConferencingServer::handleRequestNoteMeeting(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{

}

void VideoConferencingServer::handleRequestUnnotedMeetings(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{

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
                    dc.getDb().insertIntoTableAttendees(mm, userid, 0, "");
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

    int meetingState = -1;
    dc.getDb().queryMeetingStateByMeetingID(meetingID, meetingState);
    if(meetingState == 0)
    {
        dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, emailID, 2, "");
        dc.getDb().updateMeetingStateByMeetingID(meetingID, 1);
        dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, emailID, 2, "");
        dc.getDb().updateMeetingStateByMeetingID(meetingID, 1);

        vector<string> attendees;
        dc.getDb().queryAttendeesByStateAndMeetingID(meetingID, 1, attendees);

        string json;
        dc.jsonStartMeeting(meetingID, json);
        if(!attendees.empty())
        {
            for(auto &attendee:attendees)
            {
                if(attendee != emailID)
                {
                    string ip;
                    int r2 = dc.getDb().queryIpByUserID(attendee, 1, ip);
                    if(r2 == 1)
                        udpSendMessage(ip, json);
                }
            }
        }
    }
}

void VideoConferencingServer::handleRequestStopMeeting(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
    string meetingID = Data.value("DATA")["MEETINGID"].toString().toStdString();

    int meetingState = -1;
    dc.getDb().queryMeetingStateByMeetingID(meetingID, meetingState);
    if(meetingState == 1)
    {
        string speaker, assistant;
        dc.getDb().queryMeetingSpeakerAndAssistantByMeetingID(meetingID, speaker, assistant);
        if(emailID == speaker || emailID == assistant)
        {
            dc.getDb().updateMeetingStateByMeetingID(meetingID, 2);
            dc.getDb().deleteMeetingEndUndisposedNotifications(meetingID, 1);//删除会议结束时未处理的通知
            dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, emailID, 4, "");
            vector<string> attendeesList;
            dc.getDb().queryAttendeesByStateAndMeetingID(meetingID, 2, attendeesList);
            dc.getDb().queryAttendeesByStateAndMeetingID(meetingID, 3, attendeesList);
            string json;
            dc.jsonStopMeeting(meetingID, json);

            for(auto m:attendeesList)
                if(!attendeesList.empty())
                {
                    for(auto &attendee:attendeesList)
                    {
                        if(attendee != emailID)
                        {
                            dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, attendee, 4, "");
                            string ip;
                            int r2 = dc.getDb().queryIpByUserID(attendee, 1, ip);
                            if(r2 == 1)
                            {
                                udpSendMessage(ip, json);
                            }
                        }
                    }
                }
        }
        else
        {
            dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, emailID, 3, "");
            vector<string> attendees;
            dc.getDb().queryAttendeesByStateAndMeetingID(meetingID, 2, attendees);
            if(!attendees.empty())
            {
                string json;
                dc.jsonExitMeeting(meetingID, emailID, json);
                for(auto &atten : attendees)
                {
                    string ip;
                    int r2 = dc.getDb().queryIpByUserID(atten, 1, ip);
                    if(r2 == 1)
                    {
                        udpSendMessage(ip, json);
                    }
                }
            }
        }
    }
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
    int meetingState = -1;
    dc.getDb().queryMeetingStateByMeetingID(meetingID, meetingState);
    string userip;
    int i = dc.getDb().queryIpByUserID(emailID, 1 ,userip);
    if(i == 1)
        m_srsVideo.addNewDestIP(emailID);

    if(meetingState == 1)
    {
        vector<string> attendees;
        dc.getDb().queryAttendeesByStateAndMeetingID(meetingID, 2, attendees);
        string jsonstr2;
        dc.jsonStrNewAttendeeDetail(emailID, meetingID,jsonstr2);//给所有已经在会人员

        dc.getDb().updateAttendeeByMeetingIDAndAttendeeID(meetingID, emailID, 2, "");

        string jsonstr;
        dc.jsonNewMeetingAttendeesList(meetingID, jsonstr);//给当前参会人员
        string ownIp; ownIp.clear();
        int r2 =dc.getDb().queryIpByUserID(emailID, 1, ownIp);
        if(r2 == 1)
            udpSendMessage(ownIp, jsonstr);

        if(!attendees.empty())
        {
            for(auto &atten:attendees)
            {
                if(atten != emailID)
                {
                    string attenip;
                    attenip.clear();
                    int r = dc.getDb().queryIpByUserID(atten, 1, attenip);
                    if(r == 1)
                        udpSendMessage(attenip, jsonstr2);
                }
            }
        }
    }

    //    m_srsVideo.addNewDestIP("192.168.43.7");
    //    m_srsVideo.addNewDestIP("192.168.43.188");
    //    m_srsVideo.addNewDestIP("192.168.43.174");
    ////    m_srsVideo.addDestIPs(m_destIps);
    //    std::thread t1(&StreamingMediaForwading::videoForward, &m_srsVideo);
    //    t1.detach();
    //    std::thread t2(&StreamingMediaForwading::audioForward, &m_srsVideo);
    //    t2.detach();
}

void VideoConferencingServer::handleRequestStartVideo(QJsonObject Data, VideoConferencingServer::sock_ptr sock)
{
    string emailID = Data.value("DATA")["FROM"].toString().toStdString();
    string meetingID = Data.value("DATA")["MEETINGID"].toString().toStdString();

    vector<string> attendees;
    dc.getDb().queryAttendeesByStateAndMeetingID(meetingID, 1, attendees);

    m_destIps.clear();
    if(!attendees.empty())
    {
        for(auto &attendee:attendees)
        {
            if(attendee != emailID)
            {
                string ip;
                int r2 = dc.getDb().queryIpByUserID(attendee, 1, ip);
                if(r2 == 1)
                {
                    cout<<"<<<<<<<<加入ip："<<ip <<endl;
                    m_destIps.push_back(ip);
                }
            }
        }
    }

    //    m_srsVideo.addNewDestIP("192.168.43.7");
    //    m_srsVideo.addNewDestIP("192.168.43.188");
    //    m_srsVideo.addNewDestIP("192.168.43.174");
    m_srsVideo.addNewDestIP("192.168.43.174");
    //    m_srsVideo.addDestIPs(m_destIps);
    std::thread t1(&StreamingMediaForwading::videoForward, &m_srsVideo);
    t1.detach();
    std::thread t2(&StreamingMediaForwading::audioForward, &m_srsVideo);
    t2.detach();
}

void VideoConferencingServer::jsonStrCreateRegisteredID(std::string &idJson, std::string email, std::string &id, std::string realName, std::string passwd, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone)
{
    idJson.clear();
    id.clear();

    int rr = m_adb.canRegister(email);
    QJsonObject data;
    if(!rr)
    {
        data.insert("RESULT", "-1");
        data.insert("USERID", "");
        data.insert("EMAIL", email.c_str());
        data.insert("ERROR", "The email HAS BEEN REGISTERED.");
    }else {
        auto low = 1000000;
        auto high = 9999999;
        srand(time(nullptr));
        long int rnum = rand()%(high-low+1)+low;
        string iid =std::to_string(rnum);
        id =iid;
        while(!m_adb.canRegister(iid))
        {
            srand(time(nullptr));
            rnum = rand()%(high-low+1)+low;
            iid =std::to_string(rnum);
            id = iid;
        }
        data.insert("RESULT", "1");
        data.insert("USERID", id.c_str());
        data.insert("EMAIL", email.c_str());
        data.insert("ERROR", "");
        m_edb.addEmployee(id, passwd, realName, email, avatar, gName, dName, cName, phone);
    }

    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", data);
    jsonMsg.insert("TYPE", "_REGISTER");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    idJson = strJson;
}

void VideoConferencingServer::jsonStrVerifyAccountResult(std::string emailid, std::string passwd, std::string ip, std::string &verifyResult)
{
    verifyResult.clear();
    string err; err.clear();
    string res; res.clear();
    int i = m_adb.validateForLogin(emailid, passwd, ip);

    if(i == -3)
    {
        err = m_adb.getErrorInfo();
    }
    else if (i == -1)
    {
        err = "InvalidAccount";
        res = "-1";
    }
    else if(i == 0)
    {
        err = "WrongPassword";
        res = "-2";
    }
    else {
        err="";
        res = "1";
    }

    QJsonObject dd;
    dd.insert("RESULT", res.c_str());
    dd.insert("ERROR", err.c_str());
    dd.insert("EMAILID", emailid.c_str());
    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", dd);
    jsonMsg.insert("TYPE", "_LOGIN");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    verifyResult = strJson;
}

void VideoConferencingServer::jsonStrAccountDetail(std::string emailid, std::string &jsonstr)
{
    vector<string> data;
    auto e = m_edb.findByEmployeeID(emailid);
    QJsonObject dd;
    dd.insert("USERID", e->userID().c_str());
    dd.insert("EMAIL", e->email().c_str());
    dd.insert("REALNAME", e->realName().c_str());
    dd.insert("AVATAR", e->avatar().c_str());
    dd.insert("COMPANY", e->companyName().c_str());
    dd.insert("DEPARTMENT", e->departmentName().c_str());
    dd.insert("GROUP", e->groupName().c_str());
    dd.insert("PHONE", e->phone().c_str());
    QJsonObject jsonMsg;
    jsonMsg.insert("DATA", dd);
    jsonMsg.insert("TYPE", "_INITIALIZE_ACCOUNT_DETAIL");
    QJsonDocument document;
    document.setObject(jsonMsg);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    string strJson(byteArray);
    jsonstr = strJson;
}

void VideoConferencingServer::jsonStrColleagueDetail(std::string emailid, std::string &jsonstr, int &res)
{
    QJsonArray departmentsArray;

    string comid;
    Company *company = m_edb.findColleagues(emailid);
    if(company)
    {
        auto departments = company->departments();//map-departments
        for (auto departments_begin = departments.begin(); departments_begin != departments.end(); ++departments_begin)//a department
        {
            QJsonObject aDepartment;
            aDepartment.insert("DEPARTMENTNAME", departments_begin->first.c_str());
            QJsonArray groupsInDepartment;
            auto groups = departments_begin->second->groups();//map-groups
            for(auto groups_begin = groups.begin(); groups_begin != groups.end(); ++groups_begin)//a group
            {
                QJsonObject aGroup;
                aGroup.insert("GROUPNAME", groups_begin->first.c_str());
                QJsonArray employeesInAGroup;
                auto employees = groups_begin->second->members();
                for (auto employees_begin = employees.begin(); employees_begin != employees.end(); ++employees_begin)
                {
                    QJsonObject employee;
                    employee.insert("USERID", employees_begin->first.c_str());
                    employee.insert("EMAIL", employees_begin->second->email().c_str());
                    employee.insert("REALNAME", employees_begin->second->realName().c_str());
                    employee.insert("AVATAR", employees_begin->second->avatar().c_str());
                    employee.insert("PHONE", employees_begin->second->phone().c_str());
                    employeesInAGroup.insert(0, employee);
                }
                aGroup.insert("EMPLOYEES", employeesInAGroup);
                groupsInDepartment.insert(0, aGroup);

            }
            aDepartment.insert("GROUPS",groupsInDepartment);
            departmentsArray.insert(0, aDepartment);
        }
    }

    QJsonObject data;
    data.insert("DEPARTMENTS", departmentsArray);
    QJsonObject json;
    json.insert("DATA", QJsonValue(data));
    json.insert("TYPE", "_INITIALIZE_COLLEAGUE_LIST");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
    res = 1;
}

void VideoConferencingServer::jsonStrMeetingsDetail(std::string emalid, std::string &jsonstr, unsigned long long &res)
{
    QJsonArray meetingsArray;
    auto meetings = m_edb.findMeetings(emalid);//meetings
    for(auto meetings_begin = meetings.begin(); meetings_begin != meetings.end(); ++meetings_begin)
    {
        auto ameeting = meetings_begin->second;
        if(ameeting->state() != 2)//未结束的会议
        {
            QJsonObject meeting;
            meeting.insert("MEETINGID", ameeting->meetingID());
            //                    meeting.insert("INITIATOR", ameeting->initiator().c_str());
            meeting.insert("ASSISTANT", ameeting->assistant().c_str());
            meeting.insert("ASSISTANTNAME", ameeting->assistantName().c_str());
            meeting.insert("SPEAKER", ameeting->speaker().c_str());
            meeting.insert("SPEAKERNAME", ameeting->speakerName().c_str());
            meeting.insert("DATE", ameeting->date().c_str());
            meeting.insert("TIME", ameeting->time().c_str());
            meeting.insert("CATEGORY", ameeting->catagory());
            meeting.insert("SUBJECT", ameeting->subject().c_str());
            meeting.insert("MEETINGSCALE", ameeting->scale());
            meeting.insert("PREDICTEDDURATION", ameeting->preDuration());
            meeting.insert("MEETINGSTATE", ameeting->state());
            meeting.insert("REMARK", ameeting->remark().c_str());
            meetingsArray.insert(0, meeting);
        }
    }

    QJsonObject qdata;
    qdata.insert("MEETINGS", meetingsArray);
    QJsonObject json;
    json.insert("DATA", QJsonValue(qdata));
    json.insert("TYPE", "_INITIALIZE_MEETINGS_LIST");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
}

void VideoConferencingServer::jsonStrInvitationsDetail(std::string emailid, std::string &jsonstr, unsigned long long &res)
{
    QJsonArray invitationsArray;
    QJsonObject json;
    QJsonObject qdata;
    //    vector<vector<string>> invi;
    //    res = db.queryInvitationsUndisposed(emailid, invi);

    //    if(res != 0)
    //    {
    //        for (auto &anInvi: invi)
    //        {
    //            QJsonObject meeting;
    //            vector<string> data;
    //            auto meetingNumber = db.queryMeetingOfInvitionInfo(anInvi[5], data);
    //            if(meetingNumber != 0)
    //            {
    //                meeting.insert("MEETINGID", data[0].c_str());
    //                //            meeting.insert("INITIATOR", data[1].c_str());
    //                meeting.insert("ASSISTANT", data[2].c_str());
    //                string assistantName;   assistantName.clear();
    //                db.queryNameByUserID(data[2], assistantName);
    //                meeting.insert("ASSISTANTNAME", data[2].c_str());
    //                meeting.insert("SPEAKER", data[3].c_str());
    //                string speakerName;     speakerName.clear();
    //                db.queryNameByUserID(data[3], speakerName);
    //                meeting.insert("SPEAKERNAME", speakerName.c_str());
    //                meeting.insert("DATE", data[4].c_str());
    //                meeting.insert("TIME", data[5].c_str());
    //                meeting.insert("SUBJECT", data[7].c_str());
    //                //            meeting.insert("MEETINGNAME", data[8].c_str());
    //                //            meeting.insert("OWNUNIT", data[9].c_str());
    //                //                            meeting.insert("MEETINGSCALE", data[10].c_str());
    //                //            meeting.insert("PREDICTEDDURATION", data[11].c_str());
    //                //            meeting.insert("MEETINGSTATE", data[14].c_str());
    //                meeting.insert("REMARK", data[15].c_str());
    //                invitationsArray.insert(0, meeting);
    //            }
    //        }
    //    }
    qdata.insert("INVITATIONS", invitationsArray);
    json.insert("DATA", QJsonValue(qdata));
    json.insert("TYPE", "_INITIALIZE_MEETING_INVITATIONS_LIST");
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    std::string strJson(byteArray);
    jsonstr = strJson;
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

void VideoConferencingServer::clearTcpRecBuffer()
{
    for(unsigned long i = 0; i != BUFFER_LENGTH; ++i)
    {
        m_tcpRecvBuf[i] = '\0';
    }
}




