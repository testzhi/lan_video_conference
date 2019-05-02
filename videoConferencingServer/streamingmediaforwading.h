#ifndef STREAMINGMEDIAFORWADING_H
#define STREAMINGMEDIAFORWADING_H

#include <vector>
#include <string>

#include <jrtplib3/rtpsession.h>
#include <jrtplib3/rtpudpv4transmitter.h>
#include <jrtplib3/rtpipv4address.h>
#include <jrtplib3/rtpsessionparams.h>
#include <jrtplib3/rtperrors.h>
#include <jrtplib3/rtplibraryversion.h>
#include <jrtplib3/rtppacket.h>

using namespace jrtplib;

class StreamingMediaForwading
{
public:
    StreamingMediaForwading();

    void checkerror(int rtperr);

    void receiveInit();//接收--1
    void sendInit();//发送部分--2

    void addNewDestIP(std::string destIp);//a new attendee//发送部分--3
    void addDestIPs(std::vector<std::string> destIps);//attendees//发送部分--3
    void deleteADestIP(std::string destIp);//leave a attendee//发送部分
    void deleteDestIPs(std::vector<std::string> destIps);//attendees//发送部分

    void sendSetProperties();//发送部分--4

    void videoForward();//接收 发送 ---5

    int videoState() const;
    void setVideoState(int videoState);


    void recvAboutInfo();
    void sendAboutInfo();
    void closeRecvSessparams();//关闭接收
    void closeSendSessparams();//关闭发送

private:
    RTPSession m_serverVideoRecvSess;//接收
    uint16_t m_recvPortbase;
    RTPUDPv4TransmissionParams m_recvTransparams;
    RTPSessionParams m_recvSessparams;



    RTPSession m_serverVideoSendSess;//发送
    uint16_t m_sendPortbase;//输入用于发送的本地端口号
    uint16_t m_destport;
    RTPUDPv4TransmissionParams m_sendTransparams;
    RTPSessionParams m_sendSessparams;

    int m_status;

    int m_videoState;//接收--状态
};

#endif // STREAMINGMEDIAFORWADING_H
