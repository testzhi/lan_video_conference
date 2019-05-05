#ifndef VIDEORECV_H
#define VIDEORECV_H

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

#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>

using namespace jrtplib;
using namespace jthread;

#define MAX_RTP_PKT_LENGTH 1360
#define H264               96



class SVideoRecv :public RTPSession
{
public:

    std::vector<CVideoData*> m_ReceiveArray; //存放接收到的h264的数据
    void InitBufferSize();
    void CheckError(int rtperr);
protected:

//接收h264数据
    void OnPollThreadStep();
    void ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack);

private:
    CVideoData* m_pVideoData;
    unsigned char m_buffer[BUFFER_SIZE];
    int m_current_size;
};


#endif // VIDEORECV_H
