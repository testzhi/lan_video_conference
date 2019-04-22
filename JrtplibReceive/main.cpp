#include "jrtplib3/rtcpapppacket.h"
#include "jrtplib3/rtpsession.h"
#include "jrtplib3/rtppacket.h"
#include "jrtplib3/rtpudpv4transmitter.h"
#include "jrtplib3/rtpipv4address.h"
#include "jrtplib3/rtpsessionparams.h"
#include "jrtplib3/rtperrors.h"
#include "jrtplib3/rtpsourcedata.h"
#include <jthread/jthread.h>
#include "cvideodata.h"
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

extern"C"
{
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
}


using namespace jrtplib;
using namespace jthread;

#define BUFFER_SIZE 1360
#define H264        96

#define DST_IP   "127.0.0.1"
#define DST_PORT 2222
#define PORT_BASE     1234

int num = 0;

void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

class CRTPReceiver : public RTPSession
{
protected:
    void OnPollThreadStep();
    void ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack);

public:
    std::vector<CVideoData*> m_ReceiveArray; //存放接收到的h264的数据
    void InitBufferSize();
    void tt();

private:
    CVideoData* m_pVideoData;
    unsigned char m_buffer[BUFFER_SIZE];
    int m_current_size;
};

void CRTPReceiver::InitBufferSize()
{
    m_pVideoData = new CVideoData();
    memset(m_buffer,0,BUFFER_SIZE);
    m_current_size = 0;
}


void CRTPReceiver::OnPollThreadStep()
{

    BeginDataAccess();

    // check incoming packets
    if (GotoFirstSourceWithData())
    {
        do
        {
            RTPPacket *pack;
            RTPSourceData *srcdat;

            srcdat = GetCurrentSourceInfo();

            while ((pack = GetNextPacket()) != NULL)
            {
                ProcessRTPPacket(*srcdat,*pack);
                DeletePacket(pack);
            }
        } while (GotoNextSourceWithData());
    }

    EndDataAccess();
}

void CRTPReceiver::ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack)
{


        if(rtppack.GetPayloadType() == H264)
        {
            std::cout<<"Got H264 packet： " << rtppack.GetExtendedSequenceNumber() << " from SSRC " << srcdat.GetSSRC()
                    << "数量=" << num++ << std::endl;
            if(rtppack.HasMarker())//如果是最后一包则进行组包
            {
                m_pVideoData->m_lLength = m_current_size + rtppack.GetPayloadLength();//得到数据包总的长度
                memcpy(m_pVideoData->m_pBuffer,m_buffer,m_current_size);
                memcpy(m_pVideoData->m_pBuffer + m_current_size ,rtppack.GetPayloadData(),rtppack.GetPayloadLength());

                m_ReceiveArray.push_back(m_pVideoData);//添加到接收队列

                memset(m_buffer,0,m_current_size);//清空缓存，为下次做准备
                m_current_size = 0;
            }
            else//放入缓冲区，在此必须确保有序
            {
                unsigned char* p = rtppack.GetPayloadData();


                memcpy(m_buffer + m_current_size,rtppack.GetPayloadData(),rtppack.GetPayloadLength());
                m_current_size += rtppack.GetPayloadLength();
            }
        }

}

void StartReceive()
{
    CRTPReceiver sess;
    sess.InitBufferSize();
    std::string ipstr;
    int status;


    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;


    sessparams.SetOwnTimestampUnit(1.0/9000.0);

    transparams.SetPortbase(PORT_BASE);
    status = sess.Create(sessparams,&transparams);
    checkerror(status);

    uint32_t dst_ip = inet_addr(DST_IP);
    dst_ip = ntohl(dst_ip);
    RTPIPv4Address addr(dst_ip,DST_PORT);
    status = sess.AddDestination(addr);
    checkerror(status);

    RTPTime::Wait(RTPTime(200,0));
    sess.BYEDestroy(RTPTime(10,0),0,0);
}

int main(int argc, char* argv[])
{
    StartReceive();
    return 0;
}
