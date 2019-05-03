#include "videorecv.h"


//void CheckError(int rtperr)
//{
//    if (rtperr < 0)
//    {
//        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
//        exit(-1);
//    }
//}


void SVideoRecv::InitBufferSize()
{
    m_pVideoData = new CVideoData();
    memset(m_buffer,0,BUFFER_SIZE);
    m_current_size = 0;
}


void SVideoRecv::OnPollThreadStep()
{

    std::cout << "thread begin" << std::endl;
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

void SVideoRecv::ProcessRTPPacket(const RTPSourceData &srcdat,const RTPPacket &rtppack)
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
