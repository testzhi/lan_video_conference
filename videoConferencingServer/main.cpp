#include <iostream>
#include "videoconferencingserver.h"
#include "datacontroller.h"
#include <stdio.h>
#include <regex>

#include <jrtplib3/rtpsession.h>
#include <jrtplib3/rtpudpv4transmitter.h>
#include <jrtplib3/rtpipv4address.h>
#include <jrtplib3/rtpsessionparams.h>
#include <jrtplib3/rtperrors.h>
#include <jrtplib3/rtplibraryversion.h>
#include <jrtplib3/rtppacket.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <boost/thread.hpp>

using namespace jrtplib;

#define SSRC           100

void checkerror(int rtperr);
void videoForward(std::vector<std::string> destIps);

int main()
{
    try {
        int num = 2;
        VideoConferencingServer *server = new VideoConferencingServer();
        server->run();
        boost::thread_group group;
        for(int i = 0; i != num; ++i)
            group.create_thread(boost::bind(&VideoConferencingServer::run, server));
        group.join_all();
        delete server;
    } catch (std::exception &err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}

void checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

void videoForward(std::vector<std::string> destIps)
{
    RTPSession serverVideoRecvSess;//接收
    uint16_t portbase;
    int status;
    portbase = 5000;//服务器接收端口号

    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/90000.0);
    sessparams.SetAcceptOwnPackets(true);
    transparams.SetPortbase(portbase);
    status = serverVideoRecvSess.Create(sessparams,&transparams);
    checkerror(status);



    RTPSession serverVideoSendSess;//发送
    uint16_t portbase1 = 4000;//输入用于发送的本地端口号



    RTPUDPv4TransmissionParams transparams1;
    RTPSessionParams sessparams1;

    sessparams1.SetOwnTimestampUnit(1.0/90000.0);//时间戳单位
    sessparams1.SetAcceptOwnPackets(true);//接收自己发送的数据包
    sessparams1.SetUsePredefinedSSRC(true);  //设置使用预先定义的SSRC
    sessparams1.SetPredefinedSSRC(SSRC);     //定义SSRC

    transparams1.SetPortbase(portbase1);

    int oldBufSize = transparams1.GetRTPReceiveBuffer();
    transparams1.SetRTPReceiveBuffer(oldBufSize * 2);
    status = serverVideoSendSess.Create(sessparams1,&transparams1);
    checkerror(status);


    uint16_t destport1 = 3000;//输入发送数据的目的端口号
    for(auto &dip:destIps)
    {
        uint32_t destip1= inet_addr(dip.c_str());
        if (destip1 == INADDR_NONE)
        {
            std::cerr << "IP有误" << std::endl;
        }
        destip1 = ntohl(destip1);
        RTPIPv4Address addr1(destip1,destport1);
        status = serverVideoSendSess.AddDestination(addr1);
    }

    serverVideoSendSess.SetDefaultPayloadType(96);//设置默认传输参数
    serverVideoSendSess.SetDefaultMark(true);
    serverVideoSendSess.SetTimestampUnit(1.0/90000.0);
    serverVideoSendSess.SetDefaultTimestampIncrement(3600);
    checkerror(status);

    //int newBufSize = transparams1.GetRTPReceiveBuffer();
    int oldBufSizec = transparams1.GetRTCPReceiveBuffer();
    transparams1.SetRTCPReceiveBuffer(oldBufSizec * 2);
    //int newBufSizec = transparams1.GetRTCPReceiveBuffer();

    unsigned char *pfBuffer;
    unsigned char *pBuffer;


    while(1)
    {

        serverVideoRecvSess.BeginDataAccess();

        // check incoming packets
        if (serverVideoRecvSess.GotoFirstSourceWithData())
        {
            do
            {
                RTPPacket *pack;

                while ((pack = serverVideoRecvSess.GetNextPacket()) != nullptr)
                {
                    printf("Got packet !\n");

                    //                    uint8_t t = pack->GetPayloadType();
                    //                    bool mark = pack->HasMarker();
                    //                    uint32_t timestam = pack->GetTimestamp();

                    int nLen = pack->GetPayloadLength();

                    pfBuffer = (unsigned char*)pack->GetPayloadData();
                    pBuffer = new unsigned char[nLen + 1];
                    memcpy(pBuffer, pfBuffer, nLen);
                    pBuffer[nLen] = 0;

                    status = serverVideoSendSess.SendPacket((void *)pBuffer, nLen);

                    checkerror(status);
                    serverVideoRecvSess.DeletePacket(pack);
                }
            } while (serverVideoRecvSess.GotoNextSourceWithData());
        }

        serverVideoRecvSess.EndDataAccess();

        RTPTime::Wait(RTPTime(1,0));
    }

    serverVideoRecvSess.BYEDestroy(RTPTime(10,0),0,0);
    serverVideoSendSess.BYEDestroy(RTPTime(10,0),0,0);
}
