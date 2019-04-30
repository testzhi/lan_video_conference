#ifndef VIDEOSENDER_H
#define VIDEOSENDER_H

#include "jrtplib3/rtcpapppacket.h"
#include "jrtplib3/rtpsession.h"
#include "jrtplib3/rtppacket.h"
#include "jrtplib3/rtpudpv4transmitter.h"
#include "jrtplib3/rtpipv4address.h"
#include "jrtplib3/rtpsessionparams.h"
#include "jrtplib3/rtperrors.h"
#include "jrtplib3/rtpsourcedata.h"
#include <jthread/jthread.h>
#include "videodata.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace jrtplib;
using namespace jthread;

#define MAX_RTP_PKT_LENGTH 1360
#define H264               96

void CheckError(int rtperr);

class SVideoSender :
    public RTPSession
{
public:
    SVideoSender(void);
    ~SVideoSender(void);

    void SendH264Nalu(unsigned char* m_h264Buf,int buflen);
    void SetParamsForSendingH264();

    std::vector<CVideoData*> m_ReceiveArray; //存放接收到的h264的数据
    void InitBufferSize();

protected:
    void OnAPPPacket(RTCPAPPPacket *apppacket,const RTPTime &receivetime,const RTPAddress *senderaddress);
    void OnBYEPacket(RTPSourceData *srcdat);
    void OnBYETimeout(RTPSourceData *srcdat);

//接收h264数据
    void OnPollThreadStep();
    void ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack);

private:
    CVideoData* m_pVideoData;
    unsigned char m_buffer[BUFFER_SIZE];
    int m_current_size;


};


#endif // VIDEOSENDER_H
