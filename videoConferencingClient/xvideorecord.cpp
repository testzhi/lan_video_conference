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
    m_pOutCodecCtx->bit_rate = 20000; // 400000
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

void XVideoRecordThread::SetH264RTPParams(SVideoSender& sess,uint32_t destip,uint16_t destport,uint16_t baseport)
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

void XVideoRecordThread::SetAACRTPParams(CAACSender &sess, uint32_t destip, uint16_t destport, uint16_t baseport)
{
    int status;
    //RTP+RTCP库初始化SOCKET环境
    RTPUDPv4TransmissionParams transparams;
    RTPSessionParams sessparams;
    sessparams.SetOwnTimestampUnit(1.0/8000.0); //时间戳单位
    sessparams.SetAcceptOwnPackets(true);	//接收自己发送的数据包
    sessparams.SetUsePredefinedSSRC(true);  //设置使用预先定义的SSRC
    sessparams.SetPredefinedSSRC(ASSRC);     //定义SSRC

    transparams.SetPortbase(baseport);

    status = sess.Create(sessparams,&transparams);
    CheckError(status);

    destip = ntohl(destip);
    RTPIPv4Address addr(destip,destport);
    status = sess.AddDestination(addr);
    CheckError(status);
}

int XVideoRecordThread::GetSampleIndex(int sample_rate)
{
    for (int i = 0; i < 16; i++)
    {
        if (sample_rate == avpriv_mpeg4audio_sample_rates[i])
        {
            return i;
        }
    }
    return -1;
}

int XVideoRecordThread::init_resampler(AVCodecContext *input_codec_context, AVCodecContext *output_codec_context, SwrContext **resample_context)
{
    int error;

    /*
         * Create a resampler context for the conversion.
         * Set the conversion parameters.
         * Default channel layouts based on the number of channels
         * are assumed for simplicity (they are sometimes not detected
         * properly by the demuxer and/or decoder).
         */
    *resample_context = swr_alloc_set_opts(NULL,
                                           av_get_default_channel_layout(output_codec_context->channels),
                                           output_codec_context->sample_fmt,
                                           output_codec_context->sample_rate,
                                           av_get_default_channel_layout(input_codec_context->channels),
                                           input_codec_context->sample_fmt,
                                           input_codec_context->sample_rate,
                                           0, NULL);
    if (!*resample_context) {
        fprintf(stderr, "Could not allocate resample context\n");
        return AVERROR(ENOMEM);
    }
    /*
        * Perform a sanity check so that the number of converted samples is
        * not greater than the number of samples to be converted.
        * If the sample rates differ, this case has to be handled differently
        */
    av_assert0(output_codec_context->sample_rate == input_codec_context->sample_rate);

    /* Open the resampler with the specified parameters. */
    if ((error = swr_init(*resample_context)) < 0) {
        fprintf(stderr, "Could not open resample context\n");
        swr_free(resample_context);
        return error;
    }
    return 0;
}

int XVideoRecordThread::init_converted_samples(uint8_t ***converted_input_samples, AVCodecContext *output_codec_context, int frame_size)
{
    int error;

    /* Allocate as many pointers as there are audio channels.
     * Each pointer will later point to the audio samples of the corresponding
     * channels (although it may be NULL for interleaved formats).
     */
    if (!(*converted_input_samples = (uint8_t **)calloc(output_codec_context->channels,
                                                        sizeof(**converted_input_samples)))) {
        fprintf(stderr, "Could not allocate converted input sample pointers\n");
        return AVERROR(ENOMEM);
    }

    /* Allocate memory for the samples of all channels in one consecutive
     * block for convenience. */
    if ((error = av_samples_alloc(*converted_input_samples, NULL,
                                  output_codec_context->channels,
                                  frame_size,
                                  output_codec_context->sample_fmt, 0)) < 0) {
        //        fprintf(stderr,
        //                "Could not allocate converted input samples (error '%s')\n",
        //                av_err2str(error));
        av_freep(&(*converted_input_samples)[0]);
        free(*converted_input_samples);
        return error;
    }
    return 0;
}

int XVideoRecordThread::convert_samples(const uint8_t **input_data, uint8_t **converted_data, const int frame_size, SwrContext *resample_context)
{
    int error;

    /* Convert the samples using the resampler. */
    if ((error = swr_convert(resample_context,
                             converted_data, frame_size,
                             input_data    , frame_size)) < 0) {
        //        fprintf(stderr, "Could not convert input samples (error '%s')\n",
        //                av_err2str(error));
        //        return error;
    }

    return 0;
}

int XVideoRecordThread::add_samples_to_fifo(AVAudioFifo *fifo, uint8_t **converted_input_samples, const int frame_size)
{
    int error;

    /* Make the FIFO as large as it needs to be to hold both,
     * the old and the new samples. */
    if ((error = av_audio_fifo_realloc(fifo, av_audio_fifo_size(fifo) + frame_size)) < 0) {
        fprintf(stderr, "Could not reallocate FIFO\n");
        return error;
    }

    /* Store the new samples in the FIFO buffer. */
    if (av_audio_fifo_write(fifo, (void **)converted_input_samples,
                            frame_size) < frame_size) {
        fprintf(stderr, "Could not write data to FIFO\n");
        return AVERROR_EXIT;
    }
    return 0;
}

void XVideoRecordThread::WriteADTSHeader(int Size, int sample_rate, int channels)
{
    if (ADTSHeader == nullptr)
    {
        ADTSHeader = (char*)av_malloc(ADTS_HEADER_SIZE);
    }
    memset(ADTSHeader,0, ADTS_HEADER_SIZE);
    int length = ADTS_HEADER_SIZE + Size;
    length &= 0x1FFF;
    int sample_index = GetSampleIndex(sample_rate);
    int channel = 0;
    if (channels < (int)FF_ARRAY_ELEMS(ff_mpeg4audio_channels))
        channel = ff_mpeg4audio_channels[channels];
    ADTSHeader[0] = (char)0xff;
    ADTSHeader[1] = (char)0xf1;
    ADTSHeader[2] = (char)(0x40 | (sample_index << 2) | (channel >> 2));
    ADTSHeader[3] = (char)((channel & 0x3) << 6 | (length >> 11));
    ADTSHeader[4] = (char)(length >> 3) & 0xff;
    ADTSHeader[5] = (char)(((length & 0x7) << 5) & 0xff) | 0x1f;
    ADTSHeader[6] = (char)0xfc;
}

int XVideoRecordThread::ADTS(AVPacket *src, AVPacket **des)
{
    if (src == nullptr) {
        return -1;
    }
    if (des == nullptr) {
        return -1;
    }
    AVPacket *adtsPacket = av_packet_alloc();
    av_init_packet(adtsPacket);
    av_new_packet(adtsPacket, src->size + ADTS_HEADER_SIZE);
    WriteADTSHeader(src->size, 48000, 2);
    memcpy(adtsPacket->data, ADTSHeader, ADTS_HEADER_SIZE);
    memcpy(adtsPacket->data + ADTS_HEADER_SIZE, src->data, src->size);
    adtsPacket->pts = src->pts;
    adtsPacket->dts = src->dts;
    adtsPacket->duration = src->duration;
    adtsPacket->flags = src->flags;
    adtsPacket->stream_index = src->stream_index;
    adtsPacket->pos = src->pos;
    if (*des == src)
    {
        av_packet_unref(src);
        av_packet_move_ref(*des, adtsPacket);
    }
    else if (*des != nullptr)
    {
        av_packet_move_ref(*des, adtsPacket);
    }
    else
    {
        *des = adtsPacket;
    }
    return 0;
}

void XVideoRecordThread::aacCodeAndSent()
{

    av_register_all();
    avcodec_register_all();
    avdevice_register_all();

    FILE *outAudioFile = nullptr;
    outAudioFile = fopen("rec.aac", "wb");

    AVFormatContext *inputFormatCtx = NULL;
    AVInputFormat *inputFmt = av_find_input_format("alsa");
    // 打开输入音频文件
    int ret = avformat_open_input(&inputFormatCtx, url, inputFmt, 0);
    if (ret != 0) {
        printf("打开文件失败\n");
    }

    //获取音频中流的相关信息
    ret = avformat_find_stream_info(inputFormatCtx, 0);
    if (ret != 0) {
        printf("不能获取流信息\n");
    }

    av_dump_format(inputFormatCtx, 0, url, false);
    // 获取数据中音频流的序列号，这是一个标识符
    int  index = 0,audioStream = -1;
    AVCodecContext *inputCodecCtx;

    for (index = 0; index <inputFormatCtx->nb_streams; index++) {
        AVStream *stream = inputFormatCtx->streams[index];
        AVCodecContext *code = stream->codec;
        if (code->codec_type == AVMEDIA_TYPE_AUDIO){
            audioStream = index;
            break;
        }
    }

    //从音频流中获取输入编解码相关的上下文
    inputCodecCtx = inputFormatCtx->streams[audioStream]->codec;
    //查找解码器
    AVCodec *pCodec = avcodec_find_decoder(inputCodecCtx->codec_id);
    // 打开解码器
    int result =  avcodec_open2(inputCodecCtx, pCodec, NULL);
    if (result < 0) {
        printf("打开音频解码器失败\n");
    }

    // 创建aac编码器
    AVCodec *aacCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
    if (!aacCodec){
        printf("Can not find encoder!\n");
    }

    //常见aac编码相关上下文信息
    AVCodecContext *aacCodeContex = avcodec_alloc_context3(aacCodec);
    // 设置编码相关信息
    aacCodeContex->sample_fmt = aacCodec->sample_fmts[0];
    aacCodeContex->sample_rate= inputCodecCtx->sample_rate;             // 音频的采样率
    aacCodeContex->channel_layout = av_get_default_channel_layout(2);
    aacCodeContex->channels = inputCodecCtx->channels;
    aacCodeContex->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

    //打开编码器
    AVDictionary *opts = NULL;
    result = avcodec_open2(aacCodeContex, aacCodec, &opts);

    if (result < 0) {
        printf("failure open code\n");
    }

    //初始化先进先出缓存队列
    AVAudioFifo *fifo = av_audio_fifo_alloc(AV_SAMPLE_FMT_FLTP,aacCodeContex->channels, aacCodeContex->frame_size);

    //获取编码每帧的最大取样数
    int output_frame_size = aacCodeContex->frame_size;

    // 初始化重采样上下文
    SwrContext *resample_context = NULL;
    if (init_resampler(inputCodecCtx, aacCodeContex,
                       &resample_context)){
    }

    //jrtplib 发送初始化START-------------------------------------------
    CAACSender Asender;
    std::string destip_str = "10.253.77.87";
    uint32_t dest_ip = inet_addr(destip_str.c_str());
    SetAACRTPParams(Asender,dest_ip,A_DEST_PORT,A_BASE_PORT);
    Asender.SetParamsForSendingAAC();
    //JRTPLIB 发送初始化END---------------------------------------------

    bool finished  = false;
    while (1) {

        if (finished){
            break;
        }
        // 查看fifo队列中的大小是否超过可以编码的一帧的大小
        while (av_audio_fifo_size(fifo) < output_frame_size) {
            // 如果没超过，则继续进行解码
            if (finished)
            {
                break;
            }

            AVFrame *audioFrame = av_frame_alloc();
            AVPacket packet;
            packet.data = NULL;
            packet.size = 0;
            int data_present;

            // 读取出一帧未解码数据
            finished =  (av_read_frame(inputFormatCtx, &packet) == AVERROR_EOF);

            // 判断该帧数据是否为音频数据
            if (packet.stream_index != audioStream) {
                continue;
            }

            // 开始进行解码
            if ( avcodec_decode_audio4(inputCodecCtx, audioFrame, &data_present, &packet) < 0) {
                printf("音频解码失败\n");
            }

//            if (data_present)
//            {
//                //将pcm数据写入文件
//                for(int i = 0 ; i <audioFrame->channels;i++)
//                {
//                    //                    NSData *data = [NSData dataWithBytes:audioFrame->data[i] length:audioFrame->linesize[0]];
//                    //                    [pcmfileHandle writeData:data];

//                }
//            }

            // 初始化进行重采样的存储空间
            uint8_t **converted_input_samples = NULL;
            if(init_converted_samples(&converted_input_samples, aacCodeContex,
                                      audioFrame->nb_samples))
            {
            }

            // 进行重采样
            if(convert_samples((const uint8_t**)audioFrame->extended_data, converted_input_samples,
                               audioFrame->nb_samples, resample_context))
            {
            }

           //将采样结果加入进fifo中
            add_samples_to_fifo(fifo, converted_input_samples,audioFrame->nb_samples);

            // 释放重采样存储空间
            if (converted_input_samples)
            {
                av_freep(&converted_input_samples[0]);
                free(converted_input_samples);
            }
        }
        // 从fifo队列中读入数据
        while (av_audio_fifo_size(fifo) >= output_frame_size || finished) {

            AVFrame *frame;

            frame = av_frame_alloc();

            const int frame_size = FFMIN(av_audio_fifo_size(fifo),aacCodeContex->frame_size);

            // 设置输入帧的相关参数
            (frame)->nb_samples     = frame_size;
            (frame)->channel_layout = aacCodeContex->channel_layout;
            (frame)->format         = aacCodeContex->sample_fmt;
            (frame)->sample_rate    = aacCodeContex->sample_rate;

            int error;

            //根据帧的相关参数，获取数据存储空间
            if ((error = av_frame_get_buffer(frame, 0)) < 0)
            {
                av_frame_free(&frame);
            }

            // 从fifo中读取frame_size个样本数据
            if (av_audio_fifo_read(fifo, (void **)frame->data, frame_size) < frame_size)
            {
                av_frame_free(&frame);
            }

            AVPacket pkt;
            av_init_packet(&pkt);
            pkt.data = NULL;
            pkt.size = 0;

            AVPacket *dpkt = av_packet_alloc();
            av_init_packet(dpkt);

            int data_present = 0;

            frame->pts = av_frame_get_best_effort_timestamp(frame);
            frame->pict_type=AV_PICTURE_TYPE_NONE;

            // 将pcm数据进行编码
            if ((error = avcodec_encode_audio2(aacCodeContex, &pkt,frame, &data_present)) < 0)
            {
                av_free_packet(&pkt);
            }
            av_frame_free(&frame);

            WriteADTSHeader(pkt.size, 48000, 2);
            // 如果编码成功，写入文件
            if (data_present) {

                int i =  ADTS(&pkt, &dpkt);

                //jrtplib发送包含ADTS头部的数据
                Asender.SendAACPacket((unsigned char*)dpkt->data, dpkt->size);
                fwrite(dpkt->data, 1, dpkt->size, outAudioFile);
            }

            av_free_packet(&pkt);
            av_free_packet(dpkt);
        }

    }
    free(outAudioFile);


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

    std::string serverip_str = "192.168.43.188";
    uint32_t dest_ip = inet_addr(serverip_str.c_str());

    SetH264RTPParams(sender,dest_ip,SERVER_PORT,BASE_PORT);
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


