#ifndef VIDEOCONFERENCINGSERVER_H
#define VIDEOCONFERENCINGSERVER_H
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/scoped_array.hpp>
#include <boost/asio.hpp>
#include <QJsonObject>
#include <string>
#include "datacontroller.h"
#include "streamingmediaforwading.h"
#include "accountbroker.h"
#include "employeebroker.h"




#define BUFFER_LENGTH 1024

using namespace boost::asio;
using boost::asio::ip::udp;
using boost::asio::ip::tcp;
using std::string;

class VideoConferencingServer
{
    typedef ip::tcp::socket socket_type;
    typedef std::shared_ptr<socket_type> sock_ptr;

public:
    VideoConferencingServer();

    void accept();
    void handle_accepter(const boost::system::error_code &ec, sock_ptr sock);
    void run();

    //TCP
    void tcpHandleReceive(sock_ptr sock, std::string _remote_ip);
    void handleTcpSend(const boost::system::error_code &ec, sock_ptr sock);
    void tcpSendMessage(std::string msg, sock_ptr sock);

    void tcpSendTo(std::string ip, std::string msg);

    void tcpAsyncConnect(std::string ip, std::string msg);
    void tcpAsyncConnectionHandler(std::string msg, const boost::system::error_code &ec);
    void tcpAsyncSendToHandler(const boost::system::error_code &ec);


    //UDP
    void udpSendMessage(std::string ip, string msg);
    void udpSysSendMessage(std::string ip, string msg);
    void handleUdpSend(const boost::system::error_code &ec);

    //RTP
    void rtpSendMessage(std::string ip, string msg);


    //处理函数
    void handleRegister(QJsonObject Data, sock_ptr sock);  //处理注册
    void handleLogin(QJsonObject Data, std::string ip, sock_ptr sock);//处理登录
    void handleExit(QJsonObject Data, sock_ptr sock);//处理退出
    void handleAccountDetail(QJsonObject Data, sock_ptr sock);//处理账户信息
    void handleColleagueList(QJsonObject Data, sock_ptr sock);
    void handleInvitionsList(QJsonObject Data, sock_ptr sock);
    void handleMeetingList(QJsonObject Data, sock_ptr sock);
    void handleRequestFinishedMeetingsNotes(QJsonObject Data, sock_ptr sock);//for all(include assistant)
    void handleRequestNoteMeeting(QJsonObject Data, sock_ptr sock);//for assistant 请求记录
    void handleRequestUnnotedMeetings(QJsonObject Data, sock_ptr sock);//for assistant未记录的会议
    void handleRequestLaunchMeeting(QJsonObject Data, sock_ptr sock);//发起人
    void handleRequestStartMeeting(QJsonObject Data, sock_ptr sock);
    void handleRequestStopMeeting(QJsonObject Data, sock_ptr sock);
    void handleRequestInvitionResult(QJsonObject Data, sock_ptr sock);
    void handleRequestAttendMeeting(QJsonObject Data, sock_ptr sock);//参会人
    void handleRequestStartVideo(QJsonObject Data, sock_ptr sock);


    void jsonStrCreateRegisteredID(std::string &idJson, string email, string &id, std::string realName, std::string passwd, std::string avatar, std::string gName, std::string dName, std::string cName, std::string phone);
    void jsonStrVerifyAccountResult(std::string emailid, std::string passwd, std::string ip, std::string &verifyResult);
    void jsonStrAccountDetail(string emailid, string &jsonstr);
    void jsonStrColleagueDetail(std::string emailid, std::string &jsonstr, int &res);
    void jsonStrMeetingsDetail(std::string emalid, std::string &jsonstr, unsigned long long &res);
    void jsonStrInvitationsDetail(std::string emailid, std::string &jsonstr, unsigned long long &res);


private:
    QJsonObject stringToQJsonObject(std::string string);
    bool isSameString(string s1, string s2);
    void clearTcpRecBuffer();

    io_service m_io;
    ip::tcp::acceptor m_acceptor;


    boost::array<char,BUFFER_LENGTH> m_tcpRecvBuf;
    //    boost::array<char,BUFFER_LENGTH> m_tcpSendBuf;
    tcp::socket m_sockTcp;

    udp::socket m_sockUdp;

    DataController dc;
    AccountBroker m_adb;
    EmployeeBroker m_edb;

    std::vector<std::string> m_destIps;
    StreamingMediaForwading m_srsVideo;
};

#endif // VIDEOCONFERENCINGSERVER_H
