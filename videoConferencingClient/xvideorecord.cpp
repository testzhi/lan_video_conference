#include "xvideorecord.h"
#include <QDebug>
#include <stdio.h>

#define SDL_AUDIO_BUFFER_SIZE 1024
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio


XVideoRecordThread::XVideoRecordThread(QString devSource, QString imtSource):m_videoSource(devSource), m_videoInputFormat(imtSource)
{
}

XVideoRecordThread::~XVideoRecordThread()
{
    m_playerState = Pause;
    avcodec_close(m_pCodecCtx);
    avformat_close_input(&m_formatCtx);

}

void XVideoRecordThread::initVideoRecord()
{
    av_register_all();
    avdevice_register_all();
    avformat_network_init();

    m_videoOptions = nullptr;
    m_formatCtx = nullptr;
    m_pCodecCtx = nullptr;
    m_formatCtx = avformat_alloc_context();

    if(!m_videoInputFormat.isEmpty())
    {
        if(m_videoInputFormat == QString("video4linux2"))
        {
            AVInputFormat *inputVideoFmt = av_find_input_format(m_videoInputFormat.toStdString().c_str());
            if(avformat_open_input(&m_formatCtx, m_videoSource.toStdString().c_str(), inputVideoFmt, &m_videoOptions))
            {
                qDebug() << "不能打开相机设备.";
                return;
            }
        }
        else if (m_videoInputFormat == QString("x11grab"))
        {
            AVInputFormat *inputVideoFmt = av_find_input_format(m_videoInputFormat.toStdString().c_str());
            if(avformat_open_input(&m_formatCtx, m_videoSource.toStdString().c_str(), inputVideoFmt, &m_videoOptions))
            {
                qDebug() << "不能打开录屏设备.";
                return;
            }
//            av_dict_set(&m_videoOptions,"framerate","15",0 );//     set frame per second 流畅度，越大越流畅，但不宜过大
//            av_dict_set(&m_videoOptions, "preset", "medium", 0 );
//            av_dict_set(&m_videoOptions,"video_size","1280x720",0);
        //    av_dict_set(&options,"video_size","640×360",0);
        }
        else {
            qDebug() << "不能打开相机/录屏设备.";
            return;
        }
    }
    else {
        if (avformat_open_input(&m_formatCtx, m_videoSource.toStdString().c_str(), nullptr, &m_videoOptions) != 0)
        {
            qDebug() << "不能打开该文件.";
            return;
        }
    }
    if (avformat_find_stream_info(m_formatCtx, &m_videoOptions) < 0) {
        qDebug() << "不能找到视频流信息.\n";
        return;
    }

    m_videoStream = -1;
    //查找视频中包含的流信息，
    for (int i = 0; i < m_formatCtx->nb_streams; i++)
    {
        if (m_formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            m_videoStream = i;
            break;
        }
    }

    if (m_videoStream == -1)
    {
        qDebug() << "不能找到任何视频流";
        return;
    }

    m_pCodecCtx = m_formatCtx->streams[m_videoStream]->codec;
    AVCodec *pCodec = avcodec_find_decoder(m_pCodecCtx->codec_id);
    if (pCodec == nullptr)
    {
        qDebug() << "不能发现视频编码器.";
        return;
    }

    if (avcodec_open2(m_pCodecCtx, pCodec, &m_videoOptions) < 0)
    {
        qDebug()<<"不能打开视频编码器.";
        return;
    }
    m_pixWidth = m_pCodecCtx->width;
    m_pixHeight = m_pCodecCtx->height;
    qDebug() << m_pixWidth << "          " << m_pixHeight ;
}

void XVideoRecordThread::closeVideoRecord()
{
    avcodec_close(m_pCodecCtx);
    avformat_close_input(&m_formatCtx);
    //    avformat_free_context(&m_formatCtx);
}

void XVideoRecordThread::initH264OutputFile()
{
    m_videoOutputOptions = nullptr;
    m_outFormatCtx = nullptr;
    m_pOutCodecCtx = nullptr;
    m_H264OutputFilePath = "TEMP_H264_VIDEO.H264";
    m_outFormatCtx = avformat_alloc_context();
    AVOutputFormat *output_format = av_guess_format(nullptr, m_H264OutputFilePath.toStdString().c_str() ,nullptr);
    if( !output_format )
    {
        qDebug() <<"猜视频格式出错";
        return;
    }
    m_outFormatCtx->oformat = output_format;
    if(avio_open(&m_outFormatCtx->pb, m_H264OutputFilePath.toStdString().c_str(), AVIO_FLAG_READ_WRITE) < 0)
    {
        qDebug() <<"打开输出文件";
    }
    m_video_st = avformat_new_stream(m_outFormatCtx ,nullptr);
    if( !m_video_st )
    {
        qDebug() <<"创建新流出错";
        return;
    }

    AVCodec *outAVCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if(!outAVCodec)
    {
        qDebug() <<"未找到H264编码器";
        return;
    }

    m_pOutCodecCtx = avcodec_alloc_context3(outAVCodec);
    if( !m_pOutCodecCtx)
    {
        qDebug() <<"分配输出环境上下文出错";
        return;
    }
    m_pOutCodecCtx = m_video_st->codec;
    m_pOutCodecCtx->codec_id = output_format->video_codec;
    m_pOutCodecCtx ->codec_type = AVMEDIA_TYPE_VIDEO;
    m_pOutCodecCtx->pix_fmt  = AV_PIX_FMT_YUV420P;
    m_pOutCodecCtx->bit_rate = 400000; // 400000
    m_pOutCodecCtx->width = 1280;
    m_pOutCodecCtx->height = 720;
    m_pOutCodecCtx->gop_size = 250;//3

    m_pOutCodecCtx->time_base.num = 1;
    m_pOutCodecCtx->time_base.den = 10; // 15fps快慢

    m_pOutCodecCtx->qmax = 51;
    m_pOutCodecCtx->qmin = 10;
    m_pOutCodecCtx->max_b_frames = 3;

    if (m_pCodecCtx->codec_id == AV_CODEC_ID_H264)
    {
        av_dict_set(&m_videoOutputOptions,"preset", "slow", 0);
        av_dict_set(&m_videoOutputOptions,"tune", "zerolatency", 0);
    }

    if (m_outFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
    {
        m_outFormatCtx->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
    }
    int value = 0;
    value = avcodec_open2(m_pOutCodecCtx, outAVCodec, &m_videoOutputOptions);
    if(value < 0)
    {
        qDebug() <<"打开avcodec有误";
        return;
    }
    /* create empty video file */
    if ( !(m_outFormatCtx->flags & AVFMT_NOFILE) )
    {
        if( avio_open2(&m_outFormatCtx->pb , m_H264OutputFilePath.toStdString().c_str() , AVIO_FLAG_WRITE ,nullptr, nullptr) < 0 )
        {
            qDebug() <<"创建视频文件出错";
            return;
        }
    }

    if(!m_outFormatCtx->nb_streams)
    {
        qDebug() <<"输出文件不包含流";
        return;
    }

    value = avformat_write_header(m_outFormatCtx , &m_videoOutputOptions);
    if(value < 0)
    {
        qDebug() <<"写头出错";
        return;
    }

    qDebug() <<"列出H264输出文件信息";
    av_dump_format(m_outFormatCtx , 0 ,m_H264OutputFilePath.toStdString().c_str() ,1);

}

void XVideoRecordThread::closeH264OutputFile()
{
    avcodec_close(m_pOutCodecCtx);
    avformat_close_input(&m_outFormatCtx);
    //    avformat_free_context(&m_outFormatCtx);
}

void XVideoRecordThread::setFileName(QString &path)
{
    m_fileName = path;
}
void XVideoRecordThread::setVideoInputFormat(const QString &videoInputFormat)
{
    m_videoInputFormat = videoInputFormat;
}
void XVideoRecordThread::setVideoSource(const QString &videoSource)
{
    m_videoSource = videoSource;
}

void XVideoRecordThread::startPlay()
{
    ///调用 QThread 的start函数 将会自动执行下面的run函数 run函数是一个新的线程
    if( m_playerState == Pause || m_playerState == Stop ) {
        m_playerState = Playing;
        if( !this->isRunning() ) {
            this->start();
        }
        qDebug() << "Playing...";
    } else if( m_playerState == Playing ) {
        m_playerState = Stop;
        qDebug() << "Stop...";
    }
}

void XVideoRecordThread::stopPlay()
{
    m_playerState = Stop;
    if(!this->isFinished() ) {
        this->stopPlay();
    }
    qDebug() << "STOP...";
}

void XVideoRecordThread::pausePlay()
{
    m_playerState = Pause;
    //    if( this->isRunning() ) {
    //        this->wait();
    //    }
    qDebug() << "Pause...";
}

void XVideoRecordThread::checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

void XVideoRecordThread::SetRTPParams(SVideoSender& sess,uint32_t destip,uint16_t destport,uint16_t baseport)
{
    int status;
    //RTP+RTCP库初始化SOCKET环境
    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/90000.0); //时间戳单位
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

void XVideoRecordThread::run()
{


    initVideoRecord();

    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameRGB = av_frame_alloc();
//    pFrameRGB->format = m_pCodecCtx->pix_fmt;
//    pFrameRGB->width = m_pCodecCtx->width;
//    pFrameRGB->height = m_pCodecCtx->height;


    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, m_pCodecCtx->width,m_pCodecCtx->height);
    uint8_t *rgb_out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, rgb_out_buffer, AV_PIX_FMT_YUV420P, m_pCodecCtx->width, m_pCodecCtx->height);
    struct SwsContext *img_convert_ctx = sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt, m_pCodecCtx->width/2, m_pCodecCtx->height, AV_PIX_FMT_RGB555, SWS_BICUBIC, nullptr, nullptr, nullptr);

    AVPacket *packet = (AVPacket *) malloc(sizeof(AVPacket));
    int y_size = m_pCodecCtx->width * m_pCodecCtx->height;
    av_new_packet(packet, y_size);
    av_dump_format(m_formatCtx, 0, m_videoSource.toStdString().c_str(), 0); //输出视频信息


    initH264OutputFile();
    AVFrame *h264Frame = av_frame_alloc();
    h264Frame->format = m_pCodecCtx->pix_fmt;
    h264Frame->width = m_pCodecCtx->width;
    h264Frame->height = m_pCodecCtx->height;
    int h264_outbuf_size;
    int nbytes = avpicture_get_size(m_pOutCodecCtx->pix_fmt,m_pOutCodecCtx->width,m_pOutCodecCtx->height);
    uint8_t *h264_outbuf = (uint8_t*)av_malloc(nbytes);
    avpicture_fill((AVPicture *)h264Frame, h264_outbuf , AV_PIX_FMT_YUV420P, m_pOutCodecCtx->width,m_pOutCodecCtx->height);
    SwsContext* swsCtx_= sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt, m_pOutCodecCtx->width, m_pOutCodecCtx->height, m_pOutCodecCtx->pix_fmt, SWS_BICUBIC, nullptr, nullptr, nullptr);
    AVPacket h264Packet;


    qDebug() << "开始执行\---------------------------";
    //初始化jrtplib发送和接收数据参数
    SVideoSender sender;

    std::string serverip_str = "`192.168.43.174";
    uint32_t dest_ip = inet_addr(serverip_str.c_str());

    SetRTPParams(sender,dest_ip,SERVER_PORT,BASE_PORT);
    sender.SetParamsForSendingH264();

    int ret, got_picture, got_h264_pic;
    int j = 0;
    h264Frame->pts = 0;
    while (1)
    {
        if(m_playerState == Pause)
            break;
        if(av_read_frame(m_formatCtx, packet)>=0)
        {
            if(packet->stream_index == m_videoStream)
            {
                ret = avcodec_decode_video2(m_pCodecCtx, pFrame, &got_picture, packet);
                if(ret < 0)
                {
                    qDebug() << "解码错误";
                    return;
                }
                if(got_picture)
                {
                    //h264Frame->pts=(j-1)*(m_video_st->time_base.den)/((m_video_st->time_base.num)*25);

                    sws_scale(swsCtx_, pFrame->data, pFrame->linesize,0, m_pCodecCtx->height, h264Frame->data,h264Frame->linesize);

                    av_init_packet(&h264Packet);
                    h264Packet.data = nullptr;    // packet data will be allocated by the encoder
                    h264Packet.size = 0;
                    avcodec_encode_video2(m_pOutCodecCtx , &h264Packet ,h264Frame , &got_h264_pic);
                    h264Frame->pts++;


                    if(got_h264_pic)
                    {
                        if(h264Packet.pts != AV_NOPTS_VALUE)
                            h264Packet.pts = av_rescale_q(h264Packet.pts, m_video_st->codec->time_base, m_video_st->time_base);
                        if(h264Packet.dts != AV_NOPTS_VALUE)
                            h264Packet.dts = av_rescale_q(h264Packet.dts, m_video_st->codec->time_base, m_video_st->time_base);

                        printf("Write frame %3d (size= %2d)\n", j++, h264Packet.size/1000);
                        if(av_write_frame(m_outFormatCtx , &h264Packet) != 0)
                        {
                            qDebug()<<"写文件(H264)错误";
                        }

                        sender.SendH264Nalu((unsigned char*)h264Packet.data, h264Packet.size);
                        RTPTime::Wait(0.005);

                        av_packet_unref(&h264Packet);


                    } // got_h264_pic
                    av_packet_unref(&h264Packet);


                    sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, m_pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
                    int yy_size = m_pCodecCtx->width * m_pCodecCtx->height;
                    QSize qsize(m_pixWidth, m_pixHeight);
                    QImage *tmpImg = new QImage((uchar *)rgb_out_buffer, m_pCodecCtx->width, m_pCodecCtx->height, QImage::Format_RGB555);

                    QImage image = tmpImg->scaled(m_pCodecCtx->width*m_imageScale, m_pCodecCtx->height*m_imageScale); //把图像复制一份 传递给界面显示
                    emit sig_GetOneFrame(image);  //发送信号
//                    pFrameRGB->pts=(loop -1)*(m_video_st->time_base.den)/((m_video_st->time_base.num)*10);

                }
            }
        }
        av_free_packet(packet);
    }

    sender.BYEDestroy(RTPTime(10,0),0,0);


    int writeValue = av_write_trailer(m_outFormatCtx);
    if(writeValue < 0)
    {
        qDebug()<<"写入尾失败";
        exit(1);
    }
    closeH264OutputFile();
    sws_freeContext(swsCtx_);
    av_free(h264Frame);
    av_free(h264_outbuf);


    sws_freeContext(img_convert_ctx);
    av_free(pFrame);
    av_free(pFrameRGB);
    av_free(rgb_out_buffer);

    emit sig_GetOneFrame(QImage());
    pausePlay();

    closeVideoRecord();
}

double XVideoRecordThread::imageScale() const
{
    return m_imageScale;
}

void XVideoRecordThread::setImageScale(double imageScale)
{
    m_imageScale = imageScale;
}


int XVideoRecordThread::pixHeight() const
{
    return m_pixHeight;
}

int XVideoRecordThread::pixWidth() const
{
    return m_pixWidth;
}


