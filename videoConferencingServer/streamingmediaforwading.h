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


    void initAll();


    void receiveInit();//接收--1
    void receiveVideoInit();
    void receiveAudioInit();

    void sendInit();//发送部分--2
    void sendVideoInit();
    void sendAudioInit();

    void sendSetProperties();//发送部分--4
    void sendVideoSetProperties();
    void sendAudioSetProperties();



    void addNewDestIP(std::string destIp);
    void addVideoNewDestIP(std::string destIp);//a new attendee//发送部分--3
    void addAudioNewDestIP(std::string destIp);

    void addDestIPs(std::vector<std::string> destIps);//attendees//发送部分--3
    void addVideoDestIPs(std::vector<std::string> destIps);
    void addAudioDestIPs(std::vector<std::string> destIps);

    void deleteADestIP(std::string destIp);
    void deleteAVideoDestIP(std::string destIp);//leave a attendee//发送部分
    void deleteAAudioDestIP(std::string destIp);

    void deleteDestIps(std::vector<std::string> destIps);
    void deleteVideoDestIPs(std::vector<std::string> destIps);//attendees//发送部分
    void deleteAudioDestIPs(std::vector<std::string> destIps);

    void deleteAllDestIPs();
    void deleteAllVideoDestIPs();
    void deleteAllAudioDestIPs();







    void videoForward();//接收 发送 ---5
    void audioForward();



    int videoState() const;
    void setVideoState(int videoState);
    int audioState() const;
    void setAudioState(int audioState);



    void closeRecvSessparams();//关闭接收
    void closeSendSessparams();//关闭发送
    void closeVideoRecvSessparams();//关闭接收
    void closeVideoSendSessparams();//关闭发送
    void closeAudioRecvSessparams();//关闭接收
    void closeAudioSendSessparams();//关闭发送



private:
    void checkerror(int rtperr);

    //video
    RTPSession m_serverVideoRecvSess;//接收
    uint16_t m_recvVideoPortbase;
    RTPUDPv4TransmissionParams m_recvVideoTransparams;
    RTPSessionParams m_recvVideoSessparams;
    std::string m_videoServerIP;

    RTPSession m_serverVideoSendSess;//发送
    uint16_t m_sendVideoPortbase;//输入用于发送的本地端口号
    uint16_t m_sendVideoDestport;
    RTPUDPv4TransmissionParams m_sendVideoTransparams;
    RTPSessionParams m_sendVideoSessparams;

    int m_videoStatus;
    int m_videoState;//接收--状态


    //adio
    RTPSession m_serverAudioRecvSess;//接收
    uint16_t m_recAudioPortbase;
    RTPUDPv4TransmissionParams m_recvAudioTransparams;
    RTPSessionParams m_recvAudioSessparams;

    RTPSession m_serverAudioSendSess;//发送
    uint16_t m_sendAudioPortbase;//输入用于发送的本地端口号
    uint16_t m_sendAudioDestport;
    RTPUDPv4TransmissionParams m_sendAudioTransparams;
    RTPSessionParams m_sendAudioSessparams;
    std::string m_audioServerIP;

    int m_audioStatus;
    int m_audioState;
};

#endif // STREAMINGMEDIAFORWADING_H
