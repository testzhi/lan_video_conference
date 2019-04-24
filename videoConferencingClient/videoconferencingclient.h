#ifndef VIDEOCONFERENCINGSERVER_H
#define VIDEOCONFERENCINGSERVER_H

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <QObject>
#include <string>
#include <QJsonObject>
#include "employee.h"

#define BUFFER_LENGTH   1024

using namespace boost::asio;
using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::asio::ip::address;


class VideoConferencingClient
{
public:
    VideoConferencingClient();
    //TCP（调用HANDLE部分）
    void threadTcpReceive();//TCP-接收 线程
    void tcpReceiveMessage();//TCP-接收数据
    void tcpStrResultAnalysis(std::string str);//TCP-对 接收的数据 的处理

    //RTP
    void threadRtpReceive();//RTP-接收 线程
    void rtpReceiveMessage();//RTP-接收数据
    void rtpResultAnalysis();//RTP-对 接收的数据 的处理


    //REQUEST PART：客户端 发送 数据 (调用COLLECTION部分)
    void requestRegister(std::string realName, std::string passwd, std::string email, QByteArray avatar, std::string company, std::string department, std::string group, std::string phoneNumber);
    void requestLogin(std::string emailId, std::string passwd);
    void requestExit(std::string emailId);
    void requestAccountDetail(std::string emailId);//请求账户细节
    void requestColleagueList(std::string emaiId);//请求同事列表


    void setEmployee(Employee *employee);
//    void setCompany(Company *company);

private:
    //HANDLE PART：客户端处理来自Server的数据
    void handleRegisteredResult(QJsonObject qo, int &result, QString &returnID, QString &email, QString &err);//处理注册返回结果
    void handleLoginResult(QJsonObject qo, int &result, QString &err);//处理登录返回结果
    void handleInitAccountDetailResult(QJsonObject qo, QList<QString> &employeeDetail);
    void handleInitColleagueListResult(QJsonObject qo);


    //COLLECTION PART：客户端 收集整理 数据
    std::string registerJsonToString(std::string realName, std::string passwd, std::string email, QByteArray avatar, std::string company, std::string department, std::string group, std::string phoneNumber);
    std::string loginJsonToString(std::string emailId, std::string passwd);
    std::string exitJsonToString(std::string emailId);
    std::string initializeAccountDetailJsonToString(std::string emailId);
    std::string initializeColleagueListToString(std::string emailId);


    void tcpSendMessage(std::string msg);
    QJsonObject stringToQJsonObject(std::string str);

    io_service m_io;
    tcp::socket m_sockTcp;
    tcp::endpoint m_tcpEP;
    boost::array<char,BUFFER_LENGTH> m_tcpRecvBuf;//接收数据缓冲区。
    boost::array<char,BUFFER_LENGTH> m_tcpSendBuf;//接收数据缓冲区。

    Employee *m_employee;
    Company com;
//    Company *m_company;
};

#endif // VIDEOCONFERENCINGSERVER_H
