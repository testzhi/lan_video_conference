#ifndef AACSENDER_H
#define AACSENDER_H
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
#define AAC               97

void CheckError(int rtperr);

class CAACSender :
    public RTPSession
{
public:
    CAACSender(void);
    ~CAACSender(void);

protected:
    void OnAPPPacket(RTCPAPPPacket *apppacket,const RTPTime &receivetime,const RTPAddress *senderaddress);
    void OnBYEPacket(RTPSourceData *srcdat);
    void OnBYETimeout(RTPSourceData *srcdat);
public:
    void SendAACPacket(unsigned char* m_aacBuf,int buflen);
    void SetParamsForSendingAAC();
};

#endif // AACSENDER_H
