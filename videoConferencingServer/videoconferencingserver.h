#ifndef VIDEOCONFERENCINGSERVER_H
#define VIDEOCONFERENCINGSERVER_H
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <QJsonObject>
#include <string>
#include "datacontroller.h"

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
    VideoConferencingServer(): m_acceptor(m_io, ip::tcp::endpoint(ip::tcp::v4(), 2333))
    {
        accept();
    }

    void accept();
    void handle_accepter(const boost::system::error_code &ec, sock_ptr sock);
    void run();

    //TCP
    void tcpHandleReceive(const boost::system::error_code &ec, sock_ptr sock, std::string _remote_ip);
    void tcpSendMessage(std::string msg, sock_ptr sock);
    void handleTcpSend(const boost::system::error_code &ec, sock_ptr sock);


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
    void handleRequestLaunchMeeting(QJsonObject Data, sock_ptr sock);//发起人
    void handleRequestStartMeeting(QJsonObject Data, sock_ptr sock);
    void handleRequestStopMeeting(QJsonObject Data, sock_ptr sock);
    void handleRequestInvitionResult(QJsonObject Data, sock_ptr);
    void handleRequestAttendMeeting(QJsonObject Data, sock_ptr);//参会人



private:
    QJsonObject stringToQJsonObject(std::string string);

    io_service m_io;
    tcp::endpoint _remote_endpoint;
    ip::tcp::acceptor m_acceptor;
    tcp::endpoint m_tcpEP;
    boost::array<char,BUFFER_LENGTH> m_tcpRecvBuf;//接收数据缓冲区。
    boost::array<char,BUFFER_LENGTH> m_tcpSendBuf;//接收数据缓冲区。

    DataController dc;
};

#endif // VIDEOCONFERENCINGSERVER_H
