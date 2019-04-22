#ifndef CRTPSENDER_H
#define CRTPSENDER_H
#include "jrtplib3/rtcpapppacket.h"
#include "jrtplib3/rtpsession.h"
#include "jrtplib3/rtppacket.h"
#include "jrtplib3/rtpudpv4transmitter.h"
#include "jrtplib3/rtpipv4address.h"
#include "jrtplib3/rtpsessionparams.h"
#include "jrtplib3/rtperrors.h"
#include "jrtplib3/rtpsourcedata.h"
#include <jthread/jthread.h>
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

class CRTPSender :
    public RTPSession
{
public:
    CRTPSender(void);
    ~CRTPSender(void);

protected:
    void OnAPPPacket(RTCPAPPPacket *apppacket,const RTPTime &receivetime,const RTPAddress *senderaddress);
    void OnBYEPacket(RTPSourceData *srcdat);
    void OnBYETimeout(RTPSourceData *srcdat);
public:
    void SendH264Nalu(unsigned char* m_h264Buf,int buflen);
    void SetParamsForSendingH264();
};

#endif // CRTPSENDER_H
