#include "crtpsender.h"

#define SSRC           100

#define DEST_IP_STR   "127.0.0.1"
#define DEST_PORT     1234
#define BASE_PORT     2222

void SetRTPParams(CRTPSender& sess,uint32_t destip,uint16_t destport,uint16_t baseport)
{
    int status;
    //RTP+RTCP库初始化SOCKET环境
    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/9000.0); //时间戳单位
    sessparams.SetAcceptOwnPackets(true);	//接收自己发送的数据包
    sessparams.SetUsePredefinedSSRC(true);  //设置使用预先定义的SSRC
    sessparams.SetPredefinedSSRC(SSRC);     //定义SSRC

    transparams.SetPortbase(baseport);

    status = sess.Create(sessparams,&transparams);
    CheckError(status);

    destip = ntohl(destip);
    RTPIPv4Address addr(destip,destport);
    status = sess.AddDestination(addr);
    CheckError(status);

}

int main(void)
{
    CRTPSender sender;

    std::string destip_str = "127.0.0.1";
    uint32_t dest_ip = inet_addr(destip_str.c_str());

    SetRTPParams(sender,dest_ip,DEST_PORT,BASE_PORT);
    sender.SetParamsForSendingH264();


    FILE *fp_open;
    uint8_t buff[1024*5] = {0};
    int  bufsize = 1024; //每次读1024字节,谁便取，不超过1400就行

    fp_open = fopen("out.h264","rb");
    while( !feof(fp_open) )
    {
        int true_size = fread(buff,1,bufsize,fp_open);  //读一次，内部位移
        printf("\n--> read file %d bytes",true_size);
        sender.SendH264Nalu(buff,true_size);     // 每次发送固定大小的数据
        RTPTime::Wait(0.005); //间隔5毫秒
    }

    return 0;
}

