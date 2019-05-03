#include "videosender.h"


void CheckError(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}


SVideoSender::SVideoSender(void)
{
}


SVideoSender::~SVideoSender(void)
{
}

void SVideoSender::OnAPPPacket(RTCPAPPPacket *apppacket,const RTPTime &receivetime,const RTPAddress *senderaddress)
{//收到RTCP APP数据
    std::cout<<"Got RTCP packet from: "<<senderaddress<<std::endl;
    std::cout<<"Got RTCP subtype: "<< apppacket->GetSubType() <<std::endl;
    std::cout<<"Got RTCP data: "<<(char *)apppacket->GetAPPData()<<std::endl;
    return ;
}

void SVideoSender::SendH264Nalu(unsigned char* m_h264Buf,int buflen)
{
    unsigned char *pSendbuf; //发送数据指针
    pSendbuf = m_h264Buf;

    char sendbuf[1430];   //发送的数据缓冲
    memset(sendbuf,0,1430);

    int status;

    printf("send packet length %d \n",buflen);

    if ( buflen <= MAX_RTP_PKT_LENGTH )
    {
        memcpy(sendbuf,pSendbuf,buflen);
        status = this->SendPacket((void *)sendbuf,buflen);

        CheckError(status);

    }
    else if(buflen > MAX_RTP_PKT_LENGTH)
    {
        //设置标志位Mark为0
        this->SetDefaultMark(false);
        //得到该需要用多少长度为MAX_RTP_PKT_LENGTH字节的RTP包来发送
        int k=0,l=0;
        k = buflen / MAX_RTP_PKT_LENGTH;
        l = buflen % MAX_RTP_PKT_LENGTH;
        int t=0;//用指示当前发送的是第几个分片RTP包
        char nalHeader = pSendbuf[0]; // NALU 头ª¡¤
        while( t < k || ( t==k && l>0 ) )
        {
            if( (0 == t ) || ( t<k && 0!=t ) )//第一包到最后包的前一包
            {
                memcpy(sendbuf,&pSendbuf[t*MAX_RTP_PKT_LENGTH],MAX_RTP_PKT_LENGTH);
                status = this->SendPacket((void *)sendbuf,MAX_RTP_PKT_LENGTH);
                CheckError(status);
                t++;
            }
            //最后一包
            else if( ( k==t && l>0 ) || ( t== (k-1) && l==0 ))
            {
                //设置标志位Mark为1
                this->SetDefaultMark(true);

                int iSendLen;
                if ( l > 0)
                {
                    iSendLen = buflen - t*MAX_RTP_PKT_LENGTH;
                }
                else
                    iSendLen = MAX_RTP_PKT_LENGTH;

                memcpy(sendbuf,&pSendbuf[t*MAX_RTP_PKT_LENGTH],iSendLen);
                status = this->SendPacket((void *)sendbuf,iSendLen);

                CheckError(status);
                t++;
            }
        }
    }
}


void SVideoSender::SetParamsForSendingH264()
{
    this->SetDefaultPayloadType(H264);//设置传输类型
    this->SetDefaultMark(true);		//设置位
    this->SetTimestampUnit(1.0/90000.0); //设置采样间隔
    this->SetDefaultTimestampIncrement(3600);//设置时间戳增加间隔
}

void SVideoSender::OnBYEPacket(RTPSourceData *srcdat)
{

}

void SVideoSender::OnBYETimeout(RTPSourceData *srcdat)
{

}


void SVideoSender::InitBufferSize()
{
    m_pVideoData = new CVideoData();
    memset(m_buffer,0,BUFFER_SIZE);
    m_current_size = 0;
}


void SVideoSender::OnPollThreadStep()
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

void SVideoSender::ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack)
{


        if(rtppack.GetPayloadType() == H264)
        {
            std::cout<<"Got H264 packet： " << rtppack.GetExtendedSequenceNumber() << " from SSRC " << srcdat.GetSSRC()
                    <<std::endl;
            if(rtppack.HasMarker())//如果是最后一包则进行组包
            {
                m_pVideoData->m_lLength = m_current_size + rtppack.GetPayloadLength();//得到数据包总的长度
                memcpy(m_pVideoData->m_pBuffer,m_buffer,m_current_size);
                memcpy(m_pVideoData->m_pBuffer + m_current_size ,rtppack.GetPayloadData(),rtppack.GetPayloadLength());

                m_ReceiveArray.push_back(m_pVideoData);//添加到接收队列

                int fd_out = open("rec.h264", O_CREAT | O_RDWR,S_IRWXU|S_IRWXO|S_IRWXG);
                lseek(fd_out, 0, SEEK_END);
                write(fd_out, m_pVideoData->m_pBuffer,m_pVideoData->m_lLength);
                close(fd_out);

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
