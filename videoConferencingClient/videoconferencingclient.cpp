#include "videoconferencingclient.h"
#include <boost/bind.hpp>
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
    :m_sockTcp(m_io), m_tcpEP(ip::address::from_string("192.168.43.7"), 2333)
{
    m_sockTcp.connect(m_tcpEP);
}
//TCP
void VideoConferencingClient::threadTcpReceive()
{
    std::thread threadTcp(&VideoConferencingClient::tcpReceiveMessage, this);
    threadTcp.detach();
}
void VideoConferencingClient::tcpReceiveMessage()
{
    for(int i = 0; i != BUFFER_LENGTH; i++)
        m_tcpRecvBuf[i] = '\0';

    size_t readSize = 0;
    while(readSize == 0)
        readSize = m_sockTcp.read_some(buffer(m_tcpRecvBuf));

    string s = "";
    for(size_t i = 0; i != readSize; i++)
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

    QString userID, email;
    int registerResult, loginResult;
    QString err;
    if(type == "_REGISTER")
    {
        handleRegisteredResult(qo, registerResult, userID, email, err);
        if(registerResult == -1)
        {
            qDebug() << "注册失败： " << err;
            m_employee->emailAlreadyRegistered();
        }else if (registerResult == 1)
            m_employee->registerSuccessfully();
    }
    else if (type == "_LOGIN")
    {
        handleLoginResult(qo, loginResult, err);
        if(loginResult != 1) {
            qDebug() << "登录失败： " << err;
            m_employee->loginFailed(err);
        }else m_employee->loginSucceeded();
    }
    else if (type == "_INITIALIZE_ACCOUNT_DETAIL")
    {
    }
    else if (type == "_INITIALIZE_COLLEAGUE_LIST")
    {
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
    m_employee->setRealName(QString::fromStdString(realName));
    m_employee->setUserPassword(QString::fromStdString(passwd));
    m_employee->setEmail(QString::fromStdString(email));
    QString a(avatar);
    m_employee->setAvatar(a);
    m_employee->setCompany(QString::fromStdString(company));
    m_employee->setDepartment(QString::fromStdString(department));
    m_employee->setGroup(QString::fromStdString(group));
    m_employee->setPhone(QString::fromStdString(phoneNumber));


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
void VideoConferencingClient::requestAccountDetail(string emailId)
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
    result = qo.value("DATA")["RESULT"].toString().toInt();
    string emailId = qo.value("DATA")["EMAILID"].toString().toStdString();
    if(result == 1)
        requestAccountDetail(emailId);
    else
        err = qo.value("DATA")["ERROR"].toString();
    //等待重新输入
}
void VideoConferencingClient::handleInitAccountDetailResult(QJsonObject qo, QList<QString> &employeeDetail)
{
    employeeDetail.append(qo.value("DATA")["USERID"].toString());
    employeeDetail.append(qo.value("DATA")["EMAIL"].toString());
    employeeDetail.append(qo.value("DATA")["REALNAME"].toString());
    employeeDetail.append(qo.value("DATA")["AVATAR"].toString());
    employeeDetail.append(qo.value("DATA")["GROUP"].toString());
    employeeDetail.append(qo.value("DATA")["PHONE"].toString());
}

void VideoConferencingClient::handleInitColleagueListResult(QJsonObject qo, QList<QString> &group, int &groupNumber)
{
//    TYPE：_INITIALIZE_COLLEAGUE_LIST
//    DATA:{
//        GROUPS：[
//            {GROUPNAME：
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:"0"/"1"]，
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//            }],
//            [
//            {GROUPNAME：
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//            }],
//            [
//            {GROUPNAME：
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//                [REALNAME:  XX,     AVATAR：XX，    EMAIL：liannaxu07@gmail.com, STATE:]，
//            }]

//        }
//    }
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
    json.insert("TYPE", "#REGISTERED");

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
