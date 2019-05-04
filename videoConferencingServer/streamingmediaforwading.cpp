#include "streamingmediaforwading.h"
#include <iostream>

#define SSRC     100

using std::cout;
using std::endl;
using std::string;


StreamingMediaForwading::StreamingMediaForwading()
{
    m_recvPortbase = 5000;//服务器接收客户端数据端口号
    m_sendPortbase = 4000;//输入用于发送的本地端口号
    m_destport = 6666;//发送数据到客户端的目的端口号
    //    m_videoState = 1;//默认开启
    receiveInit();
    sendInit();
    sendSetProperties();
//    recvAboutInfo();
//    sendAboutInfo();
}

void StreamingMediaForwading::checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

void StreamingMediaForwading::receiveInit()
{
    m_recvSessparams.SetOwnTimestampUnit(1.0/90000.0);
    m_recvSessparams.SetAcceptOwnPackets(true);
    m_recvTransparams.SetPortbase(m_recvPortbase);
    m_status = m_serverVideoRecvSess.Create(m_recvSessparams,&m_recvTransparams);
    checkerror(m_status);
}

void StreamingMediaForwading::sendInit()
{
    m_sendSessparams.SetOwnTimestampUnit(1.0/90000.0);//时间戳单位
    m_sendSessparams.SetAcceptOwnPackets(true);//接收自己发送的数据包
    m_sendSessparams.SetUsePredefinedSSRC(true);  //设置使用预先定义的SSRC
    m_sendSessparams.SetPredefinedSSRC(SSRC);     //定义SSRC
    m_sendTransparams.SetPortbase(m_sendPortbase);
    int oldBufSize = m_sendTransparams.GetRTPReceiveBuffer();
    m_sendTransparams.SetRTPReceiveBuffer(oldBufSize * 2);
    m_status = m_serverVideoSendSess.Create(m_sendSessparams,&m_sendTransparams);
    checkerror(m_status);

}

void StreamingMediaForwading::addNewDestIP(std::string destIp)
{
    if(!destIp.empty())
    {
        uint32_t destip= inet_addr(destIp.c_str());
        if (destip == INADDR_NONE)
        {
            std::cerr << "IP有误" << std::endl;
        }
        else {
            destip = ntohl(destip);
            RTPIPv4Address addr(destip,m_destport);
            m_status = m_serverVideoSendSess.AddDestination(addr);
            checkerror(m_status);
        }
    }
}

void StreamingMediaForwading::addDestIPs(std::vector<std::string> destIps)
{
    m_serverVideoSendSess.ClearDestinations();
    for(auto &dip:destIps)
        addNewDestIP(dip);
}

void StreamingMediaForwading::deleteADestIP(std::string destIp)
{
    uint32_t destip= inet_addr(destIp.c_str());
    if (destip == INADDR_NONE)
    {
        std::cerr << "IP有误" << std::endl;
    }
    else {
        destip = ntohl(destip);
        RTPIPv4Address addr(destip,m_destport);
        m_status = m_serverVideoSendSess.DeleteDestination(addr);
        checkerror(m_status);
    }
}

void StreamingMediaForwading::deleteDestIPs(std::vector<std::string> destIps)
{
    for(auto &dip:destIps)
        deleteADestIP(dip);
}

void StreamingMediaForwading::sendSetProperties()
{
    m_serverVideoSendSess.SetDefaultPayloadType(96);//设置默认传输参数
    m_serverVideoSendSess.SetDefaultMark(true);
    m_serverVideoSendSess.SetTimestampUnit(1.0/90000.0);
    m_serverVideoSendSess.SetDefaultTimestampIncrement(3600);
    //int newBufSize = m_sendTransparams.GetRTPReceiveBuffer();
    int oldBufSizec = m_sendTransparams.GetRTCPReceiveBuffer();
    m_sendTransparams.SetRTCPReceiveBuffer(oldBufSizec * 2);
    //int newBufSizec = m_sendTransparams.GetRTCPReceiveBuffer();
}

void StreamingMediaForwading::videoForward()
{
//        receiveInit();
//        sendInit();
//    //    string ip;
//    //    addNewDestIP(ip);
//    sendSetProperties();

    recvAboutInfo();
    sendAboutInfo();
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
                    recvAboutInfo();
                    sendAboutInfo();
                    printf("Got packet !\n");

                    //                    uint8_t t = pack->GetPayloadType();
                    //                    bool mark = pack->HasMarker();
                    //                    uint32_t timestam = pack->GetTimestamp();

                    int nLen = pack->GetPayloadLength();

                    pfBuffer = (unsigned char*)pack->GetPayloadData();
                    pBuffer = new unsigned char[nLen + 1];
                    memcpy(pBuffer, pfBuffer, nLen);
                    pBuffer[nLen] = 0;

                    m_status = m_serverVideoSendSess.SendPacket((void *)pBuffer, nLen);

                    checkerror(m_status);
                    m_serverVideoRecvSess.DeletePacket(pack);
                }
            } while (m_serverVideoRecvSess.GotoNextSourceWithData());
        }

        m_serverVideoRecvSess.EndDataAccess();

        RTPTime::Wait(RTPTime(1,0));
    }

    m_serverVideoRecvSess.BYEDestroy(RTPTime(10,0),nullptr,0);
    m_serverVideoSendSess.BYEDestroy(RTPTime(10,0),nullptr,0);
}

int StreamingMediaForwading::videoState() const
{
    return m_videoState;
}

void StreamingMediaForwading::setVideoState(int videoState)
{
    m_videoState = videoState;
}

void StreamingMediaForwading::recvAboutInfo()
{
    cout << "^^^^^流媒体服务器接收的ip："<< m_recvTransparams.GetBindIP() << "用于接收的端口：" << m_recvTransparams.GetPortbase() << endl;;
    auto localIpList = m_recvTransparams.GetLocalIPList();
    cout << "^^^^^流媒体服务器接收部分的本地IP簇";
    for(auto &lil: localIpList)
        cout << "   " << lil;
    cout << endl;
}

void StreamingMediaForwading::sendAboutInfo()
{
    cout << "￥￥￥￥￥流媒体服务器用于发送的ip："<< m_sendTransparams.GetBindIP() << "用于接收的端口：" << m_sendTransparams.GetPortbase() << endl;;
    auto localIpList = m_recvTransparams.GetLocalIPList();
    cout << "￥￥￥￥￥流媒体服务器发送部分的本地IP簇";
    for(auto &lil: localIpList)
        cout << "   " << lil;
    cout << endl;
}



void StreamingMediaForwading::closeRecvSessparams()
{
    m_recvSessparams.SetRequestImmediateBYE(1);
}

void StreamingMediaForwading::closeSendSessparams()
{
    m_recvSessparams.SetRequestImmediateBYE(1);
}
