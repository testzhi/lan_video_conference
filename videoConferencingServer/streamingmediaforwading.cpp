#include "streamingmediaforwading.h"
#include <iostream>

#define SSRC     100
#define ASSRC    102

using std::cout;
using std::endl;
using std::string;


StreamingMediaForwading::StreamingMediaForwading()
{
    m_recvVideoPortbase = 5000;//服务器接收客户端数据端口号
    m_sendVideoPortbase = 4000;//输入用于发送的本地端口号
    m_sendVideoDestport = 6666;//发送数据到客户端的目的端口号
    //    m_videoState = 1;//默认开启
    m_recAudioPortbase = 8000;//服务器接收端口号
    m_sendAudioPortbase = 8010;//输入用于发送的本地端口号
    m_sendAudioDestport = 8888;//输入发送数据的目的端口号
    initAll();
}


void StreamingMediaForwading::initAll()
{
    receiveInit();
    sendInit();
    sendSetProperties();
}



void StreamingMediaForwading::receiveInit()
{
    receiveVideoInit();
    receiveAudioInit();
}

void StreamingMediaForwading::receiveVideoInit()
{
    m_recvVideoSessparams.SetOwnTimestampUnit(1.0/90000.0);
    m_recvVideoSessparams.SetAcceptOwnPackets(true);

    m_recvVideoTransparams.SetPortbase(m_recvVideoPortbase);
    m_videoStatus = m_serverVideoRecvSess.Create(m_recvVideoSessparams, &m_recvVideoTransparams);
    checkerror(m_videoStatus);
}

void StreamingMediaForwading::receiveAudioInit()
{
    m_recvAudioSessparams.SetOwnTimestampUnit(1.0/8000.0);
    m_recvAudioSessparams.SetAcceptOwnPackets(true);

    m_recvAudioTransparams.SetPortbase(m_recAudioPortbase);
    m_audioStatus = m_serverAudioRecvSess.Create(m_recvAudioSessparams, &m_recvAudioTransparams);
    checkerror(m_audioStatus);
}


void StreamingMediaForwading::sendInit()
{
    sendVideoInit();
    sendAudioInit();
}

void StreamingMediaForwading::sendVideoInit()
{
    m_sendVideoSessparams.SetOwnTimestampUnit(1.0/90000.0);//时间戳单位
    m_sendVideoSessparams.SetAcceptOwnPackets(true);//接收自己发送的数据包
    m_sendVideoSessparams.SetUsePredefinedSSRC(true);  //设置使用预先定义的SSRC
    m_sendVideoSessparams.SetPredefinedSSRC(SSRC);     //定义SSRC

    m_sendVideoTransparams.SetPortbase(m_sendVideoPortbase);
    int oldBufSize = m_sendVideoTransparams.GetRTPReceiveBuffer();
    m_sendVideoTransparams.SetRTPReceiveBuffer(oldBufSize * 2);

    m_videoStatus = m_serverVideoSendSess.Create(m_sendVideoSessparams,&m_sendVideoTransparams);
    checkerror(m_videoStatus);
}

void StreamingMediaForwading::sendAudioInit()
{
    m_sendAudioSessparams.SetOwnTimestampUnit(1.0/8000.0);//时间戳单位
    m_sendAudioSessparams.SetAcceptOwnPackets(true);//接收自己发送的数据包
    m_sendAudioSessparams.SetUsePredefinedSSRC(true);  //设置使用预先定义的SSRC
    m_sendAudioSessparams.SetPredefinedSSRC(ASSRC);     //定义SSRC

    m_sendAudioTransparams.SetPortbase(m_sendAudioPortbase);
    int oldBufSize = m_sendAudioTransparams.GetRTPReceiveBuffer();
    m_sendAudioTransparams.SetRTPReceiveBuffer(oldBufSize * 2);

    m_audioStatus = m_serverAudioSendSess.Create(m_sendAudioSessparams, &m_sendAudioTransparams);
    checkerror(m_audioStatus);

}


void StreamingMediaForwading::sendSetProperties()
{
    sendVideoSetProperties();
    sendAudioSetProperties();
}

void StreamingMediaForwading::sendVideoSetProperties()
{
    m_serverVideoSendSess.SetDefaultPayloadType(96);//设置默认传输参数
    m_serverVideoSendSess.SetDefaultMark(true);
    m_serverVideoSendSess.SetTimestampUnit(1.0/90000.0);
    m_serverVideoSendSess.SetDefaultTimestampIncrement(3600);
    //int newBufSize = m_sendVideoTransparams.GetRTPReceiveBuffer();
    int oldBufSizec = m_sendVideoTransparams.GetRTCPReceiveBuffer();
    m_sendVideoTransparams.SetRTCPReceiveBuffer(oldBufSizec * 2);
    //int newBufSizec = m_sendVideoTransparams.GetRTCPReceiveBuffer();
}

void StreamingMediaForwading::sendAudioSetProperties()
{
    m_serverAudioSendSess.SetDefaultPayloadType(97);//设置默认传输参数
    m_serverAudioSendSess.SetDefaultMark(true);
    m_serverAudioSendSess.SetTimestampUnit(1.0/8000.0);
    m_serverAudioSendSess.SetDefaultTimestampIncrement(160);

    //int newBufSize = transparams1.GetRTPReceiveBuffer();
    int oldBufSizec = m_sendAudioTransparams.GetRTCPReceiveBuffer();
    m_sendAudioTransparams.SetRTCPReceiveBuffer(oldBufSizec * 2);
    //int newBufSizec = transparams1.GetRTCPReceiveBuffer();
}




void StreamingMediaForwading::addNewDestIP(std::string destIp)
{
    addVideoNewDestIP(destIp);
    addAudioNewDestIP(destIp);
}

void StreamingMediaForwading::addVideoNewDestIP(std::string destIp)
{
    if(!destIp.empty())
    {
        uint32_t destip = inet_addr(destIp.c_str());
        if (destip == INADDR_NONE)
        {
            std::cerr << "IP有误" << std::endl;
        }
        else {
            destip = ntohl(destip);
            RTPIPv4Address addr(destip,m_sendVideoDestport);
            m_videoStatus = m_serverVideoSendSess.AddDestination(addr);
            checkerror(m_videoStatus);
            std::cerr << "添加新目标IP：" << destIp << std::endl;
        }
    }
}

void StreamingMediaForwading::addAudioNewDestIP(std::string destIp)
{
    if(!destIp.empty())
    {
        uint32_t destip = inet_addr(destIp.c_str());
        if (destip == INADDR_NONE)
        {
            std::cerr << "IP有误" << std::endl;
        }
        else {
            destip = ntohl(destip);
            RTPIPv4Address addr(destip, m_sendAudioDestport);
            m_audioStatus = m_serverAudioSendSess.AddDestination(addr);
            checkerror(m_audioStatus);
            std::cerr << "添加新目标IP：" << destIp << std::endl;
        }
    }
}


void StreamingMediaForwading::addDestIPs(std::vector<std::string> destIps)
{
    addVideoDestIPs(destIps);
    addAudioDestIPs(destIps);
}

void StreamingMediaForwading::addVideoDestIPs(std::vector<std::string> destIps)
{
    for(auto &dip:destIps)
        addVideoNewDestIP(dip);
}

void StreamingMediaForwading::addAudioDestIPs(std::vector<std::string> destIps)
{
    for(auto &dip:destIps)
        addAudioNewDestIP(dip);
}


void StreamingMediaForwading::deleteADestIP(std::string destIp)
{
    deleteAVideoDestIP(destIp);
    deleteAAudioDestIP(destIp);
}

void StreamingMediaForwading::deleteAVideoDestIP(std::string destIp)
{
    uint32_t destip= inet_addr(destIp.c_str());
    if (destip == INADDR_NONE)
    {
        std::cerr << "IP有误" << std::endl;
    }
    else {
        destip = ntohl(destip);
        RTPIPv4Address addr(destip,m_sendVideoDestport);
        m_videoStatus = m_serverVideoSendSess.DeleteDestination(addr);
        checkerror(m_videoStatus);
        std::cerr << "删除目标IP：" << destIp << std::endl;
    }
}

void StreamingMediaForwading::deleteAAudioDestIP(std::string destIp)
{
    uint32_t destip= inet_addr(destIp.c_str());
    if (destip == INADDR_NONE)
    {
        std::cerr << "IP有误" << std::endl;
    }
    else {
        destip = ntohl(destip);
        RTPIPv4Address addr(destip,m_sendAudioDestport);
        m_audioStatus = m_serverAudioSendSess.DeleteDestination(addr);
        checkerror(m_audioStatus);
        std::cerr << "删除目标IP：" << destIp << std::endl;
    }
}


void StreamingMediaForwading::deleteDestIps(std::vector<std::string> destIps)
{
    deleteVideoDestIPs(destIps);
    deleteAudioDestIPs(destIps);
}

void StreamingMediaForwading::deleteVideoDestIPs(std::vector<std::string> destIps)
{
    for(auto &dip:destIps)
        deleteAVideoDestIP(dip);
}

void StreamingMediaForwading::deleteAudioDestIPs(std::vector<std::string> destIps)
{
    for(auto &dip:destIps)
        deleteAAudioDestIP(dip);
}


void StreamingMediaForwading::deleteAllDestIPs()
{
    deleteAllVideoDestIPs();
    deleteAllAudioDestIPs();
}

void StreamingMediaForwading::deleteAllVideoDestIPs()
{
    m_serverVideoSendSess.ClearDestinations();
}

void StreamingMediaForwading::deleteAllAudioDestIPs()
{
    m_serverAudioSendSess.ClearDestinations();
}


void StreamingMediaForwading::videoForward()
{
    unsigned char *pfBuffer;
    unsigned char *pBuffer;

    while(1)
    {
        m_serverVideoRecvSess.BeginDataAccess();
        // check incoming packets
        if (m_serverVideoRecvSess.GotoFirstSourceWithData())
        {
            do
            {
                RTPPacket *pack;
                while ((pack = m_serverVideoRecvSess.GetNextPacket()) != nullptr)
                {
                    std::cerr << "Got Video packet" << std::endl;
                    int nLen = pack->GetPayloadLength();
                    //                    uint8_t t = pack->GetPayloadType();
                    //                    bool mark = pack->HasMarker();
                    //                    uint32_t timestam = pack->GetTimestamp();
                    pfBuffer = (unsigned char*)pack->GetPayloadData();
                    pBuffer = new unsigned char[nLen + 1];
                    memcpy(pBuffer, pfBuffer, nLen);
                    pBuffer[nLen] = 0;

                    m_videoStatus = m_serverVideoSendSess.SendPacket((void *)pBuffer, nLen);

                    checkerror(m_videoStatus);
                    m_serverVideoRecvSess.DeletePacket(pack);
                }
            } while (m_serverVideoRecvSess.GotoNextSourceWithData());
        }

        m_serverVideoRecvSess.EndDataAccess();
        RTPTime::Wait(RTPTime(3,0));
    }
    m_serverVideoRecvSess.BYEDestroy(RTPTime(10,0),nullptr,0);
    m_serverVideoSendSess.BYEDestroy(RTPTime(10,0),nullptr,0);
}

void StreamingMediaForwading::audioForward()
{
    unsigned char *pfBuffer;
    unsigned char *pBuffer;
    while(1)
    {
        m_serverAudioRecvSess.BeginDataAccess();
        if (m_serverAudioRecvSess.GotoFirstSourceWithData())
        {
            do
            {
                RTPPacket *pack;
                while ((pack = m_serverAudioRecvSess.GetNextPacket()) != nullptr)
                {
                    std::cerr << "got audio packet" << std::endl;
                    int nLen = pack->GetPayloadLength();
                    pfBuffer = (unsigned char*)pack->GetPayloadData();
                    pBuffer = new unsigned char[nLen + 1];
                    memcpy(pBuffer, pfBuffer, nLen);
                    pBuffer[nLen] = 0;

                    m_audioStatus = m_serverAudioSendSess.SendPacket((void *)pBuffer, nLen);
                    checkerror(m_audioStatus);
                    m_serverAudioRecvSess.DeletePacket(pack);
                }
            } while (m_serverAudioRecvSess.GotoNextSourceWithData());
        }
        m_serverAudioRecvSess.EndDataAccess();
        RTPTime::Wait(RTPTime(3,0));
    }
    m_serverAudioRecvSess.BYEDestroy(RTPTime(10,0),nullptr,0);
    m_serverAudioSendSess.BYEDestroy(RTPTime(10,0),nullptr,0);
}



int StreamingMediaForwading::videoState() const
{
    return m_videoState;
}

void StreamingMediaForwading::setVideoState(int videoState)
{
    m_videoState = videoState;
}

int StreamingMediaForwading::audioState() const
{
    return m_audioState;
}

void StreamingMediaForwading::setAudioState(int audioState)
{
    m_audioState = audioState;
}



void StreamingMediaForwading::closeRecvSessparams()
{
    closeVideoRecvSessparams();
    closeAudioRecvSessparams();
}

void StreamingMediaForwading::closeSendSessparams()
{
    closeVideoSendSessparams();
    closeAudioSendSessparams();
}

void StreamingMediaForwading::closeVideoRecvSessparams()
{
    m_recvVideoSessparams.SetRequestImmediateBYE(1);
}

void StreamingMediaForwading::closeVideoSendSessparams()
{
    m_sendVideoSessparams.SetRequestImmediateBYE(1);
}

void StreamingMediaForwading::closeAudioRecvSessparams()
{
    m_recvAudioSessparams.SetRequestImmediateBYE(1);
}

void StreamingMediaForwading::closeAudioSendSessparams()
{
    m_sendAudioSessparams.SetRequestImmediateBYE(1);
}





void StreamingMediaForwading::checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cerr << "流媒体服务器错误信息: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}
