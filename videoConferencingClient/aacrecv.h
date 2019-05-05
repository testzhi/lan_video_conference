#ifndef AACRECV_H
#define AACRECV_H
#include "jrtplib3/rtcpapppacket.h"
#include "jrtplib3/rtpsession.h"
#include "jrtplib3/rtppacket.h"
#include "jrtplib3/rtpudpv4transmitter.h"
#include "jrtplib3/rtpipv4address.h"
#include "jrtplib3/rtpsessionparams.h"
#include "jrtplib3/rtperrors.h"
#include "jrtplib3/rtpsourcedata.h"
#include <jthread/jthread.h>
#include "caudiodata.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>

using namespace jrtplib;
using namespace jthread;

#define BUFFER_SIZE 1360
#define AAC        97

class AudioReceiver : public RTPSession
{
protected:
    void OnPollThreadStep();
    void ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack);

public:
    std::vector<CAudioData*> m_ReceiveArray; //存放接收到的h264的数据
    void InitBufferSize();

private:
    CAudioData* m_pAudioData;
    unsigned char m_buffer[BUFFER_SIZE];
    int m_current_size;
};






#endif // AACRECV_H
