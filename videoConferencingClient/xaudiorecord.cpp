#include "xaudiorecord.h"
#include <QDebug>

#define ASSRC           102
#define A_DEST_PORT     8000
#define A_BASE_PORT     8050


#define SDL_AUDIO_BUFFER_SIZE 1024
#define AVCODEC_MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio

//音频参数START-------------------------------
#define OUTPUT_BIT_RATE 96000
#define OUTPUT_CHANNELS 2
#define MAX_AUDIO_FRAME_SIZE 192000
#define ADTS_HEADER_SIZE 7

char *ADTSHeader = nullptr;

const int avpriv_mpeg4audio_sample_rates[16] = {
    96000, 88200, 64000, 48000, 44100, 32000,
    24000, 22050, 16000, 12000, 11025, 8000, 7350
};

const uint8_t ff_mpeg4audio_channels[8] = {
    0, 1, 2, 3, 4, 5, 6, 8
};
//音频参数END---------------------------------

XAudioRecord::XAudioRecord()
{

}

XAudioRecord::~XAudioRecord()
{

}

void XAudioRecord::initAudioRecord()
{
    av_register_all();
    avdevice_register_all();
    avformat_network_init();

    m_inFormatContext = avformat_alloc_context();
    AVInputFormat *inputAudioFmt = av_find_input_format("alsa");
    if(avformat_open_input(&m_inFormatContext, "hw:1", inputAudioFmt, &m_inOptions)!=0)
    {
        qDebug() << "不能打开音频设备." ;
        exit(0);
    }
    if(avformat_find_stream_info(m_inFormatContext, &m_inOptions) <0 )
    {
        printf("不能找到音频流信息.\n");
        exit(0);
    }
    for(int i = 0; i < m_inFormatContext->nb_streams; i++)
        if(m_inFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            m_audioStream = i;
            break;
        }
    if(m_audioStream == -1)
    {
        printf("不能找到任何音频流.\n");
        exit(0);
    }
    m_inPCodeCtx = m_inFormatContext->streams[m_audioStream]->codec;
    m_inPCodeCtx->channel_layout = av_get_default_channel_layout(m_inPCodeCtx->channels);

    AVCodec	*pAudioCodec = avcodec_find_decoder(m_inPCodeCtx->codec_id);
    if(pAudioCodec == nullptr)
    {
        printf("不能发现音频编码器.\n");
        exit(0);
    }
    if(avcodec_open2(m_inPCodeCtx, pAudioCodec, &m_inOptions)<0)
    {
        printf("不能打开音频编码器.\n");
        exit(0);
    }

}

void XAudioRecord::closeAudioRecord()
{
    avcodec_close(m_inPCodeCtx);;
    avformat_close_input(&m_inFormatContext);
}

void XAudioRecord::initAACOutputFile()
{
    m_AACOutputFilePath = "audio.aac";
    m_outFormatContext = avformat_alloc_context();
    AVOutputFormat *outputAudioFmt = av_guess_format(nullptr, m_AACOutputFilePath.toStdString().c_str(), nullptr);
    if(!outputAudioFmt)
    {
        qDebug() <<"猜视频格式出错";
        return;
    }

    // 创建aac编码器
    AVCodec *aacCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
    if (!aacCodec){
        printf("Can not find encoder!\n");
    }

    //常见aac编码相关上下文信息
    AVCodecContext *m_outPCodecCtx = avcodec_alloc_context3(aacCodec);
    // 设置编码相关信息
    m_outPCodecCtx->sample_fmt = aacCodec->sample_fmts[0];
    m_outPCodecCtx->sample_rate= m_outPCodecCtx->sample_rate;             // 音频的采样率
    m_outPCodecCtx->channel_layout = av_get_default_channel_layout(2);
    m_outPCodecCtx->channels = m_outPCodecCtx->channels;
    m_outPCodecCtx->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

    if (avcodec_open2(m_outPCodecCtx, aacCodec, &m_outOptions)<0) {
        printf("不能打开音频编码器.\n");
        exit(0);
    }

}

void XAudioRecord::closeAACOutputFile()
{
    avcodec_close(m_outPCodecCtx);;
    avformat_close_input(&m_outFormatContext);
}

void XAudioRecord::startPlay()
{

}

void XAudioRecord::stopPlay()
{

}

void XAudioRecord::pausePlay()
{

}

int XAudioRecord::GetSampleIndex(int sample_rate)
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

int XAudioRecord::init_resampler(AVCodecContext *input_codec_context, AVCodecContext *output_codec_context, SwrContext **resample_context)
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

int XAudioRecord::init_converted_samples(uint8_t ***converted_input_samples, AVCodecContext *output_codec_context, int frame_size)
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

int XAudioRecord::convert_samples(const uint8_t **input_data, uint8_t **converted_data, const int frame_size, SwrContext *resample_context)
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

int XAudioRecord::add_samples_to_fifo(AVAudioFifo *fifo, uint8_t **converted_input_samples, const int frame_size)
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

void XAudioRecord::WriteADTSHeader(int Size, int sample_rate, int channels)
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

int XAudioRecord::ADTS(AVPacket *src, AVPacket **des)
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


void XAudioRecord::checkerror(int rtperr)
{
    if (rtperr < 0)
    {
        std::cout << "ERROR: " << RTPGetErrorString(rtperr) << std::endl;
        exit(-1);
    }
}

void XAudioRecord::SetAACRTPParams(CAACSender &sess, uint32_t destip, uint16_t destport, uint16_t baseport)
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
    checkerror(status);

    destip = ntohl(destip);
    RTPIPv4Address addr(destip,destport);
    status = sess.AddDestination(addr);
    checkerror(status);
}

void XAudioRecord::run()
{
    initAudioRecord();

    FILE *pcmFile = fopen("record.pcm", "wb");
    uint64_t mid_pcm_channel_layout = AV_CH_LAYOUT_STEREO;//Out Audio Param
    int mid_pcm_nb_samples = m_inPCodeCtx->frame_size;//nb_samples: AAC-1024 MP3-1152
    AVSampleFormat mid_pcm_sample_fmt = AV_SAMPLE_FMT_S16;
    int mid_pcm_sample_rate = 44100;
    int mid_pcm_channels = av_get_channel_layout_nb_channels(mid_pcm_channel_layout);

    //    AUDIO INPUT
    //    int64_t in_channel_layout = av_get_default_channel_layout(m_inPCodeCtx->channels);
    int64_t in_channel_layout = m_inPCodeCtx->channel_layout;

    //Swr
    struct SwrContext *au_convert_ctx = swr_alloc();
    au_convert_ctx = swr_alloc_set_opts(au_convert_ctx, mid_pcm_channel_layout, mid_pcm_sample_fmt, mid_pcm_sample_rate, in_channel_layout, m_inPCodeCtx->sample_fmt , m_inPCodeCtx->sample_rate, 0, nullptr);
    swr_init(au_convert_ctx);

    uint8_t *mid_pcm_buffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);


    int decodeRet, decode_got_picture;



    //--------------------------aac start
    initAACOutputFile();

    //初始化先进先出缓存队列
    AVAudioFifo *fifo = av_audio_fifo_alloc(AV_SAMPLE_FMT_FLTP,m_outPCodecCtx->channels, m_outPCodecCtx->frame_size);

    //获取编码每帧的最大取样数
    int output_frame_size = m_outPCodecCtx->frame_size;

    // 初始化重采样上下文
    SwrContext *resample_context = nullptr;
    if (init_resampler(m_inPCodeCtx, m_outPCodecCtx,
                       &resample_context)){
    }
    FILE *outAudioFile = nullptr;
    outAudioFile = fopen("rec.aac", "wb");

    //---------------------------aac end

    //jrtplib 发送初始化START--------------------------------------
    CAACSender Asender;
    std::string destip_str = "192.168.43.174";
    uint32_t dest_ip = inet_addr(destip_str.c_str());
    SetAACRTPParams(Asender,dest_ip,A_DEST_PORT,A_BASE_PORT);
    Asender.SetParamsForSendingAAC();
    //JRTPLIB 发送初始化END----------------------------------------


    int index = 0;
    bool finished  = false;
    while (1)
    {

        if (finished){
            break;
        }
        // 查看fifo队列中的大小是否超过可以编码的一帧的大小
        while (av_audio_fifo_size(fifo) < output_frame_size)
        {
            // 如果没超过，则继续进行解码
            if (finished)
            {
                break;
            }

            AVFrame *pcmFrame = av_frame_alloc();
            AVPacket aacRawDataPacket;
            aacRawDataPacket.data = nullptr;
            aacRawDataPacket.size = 0;

            // 读取出一帧未解码数据
            finished =  (av_read_frame(m_inFormatContext, &aacRawDataPacket) == AVERROR_EOF);

            // 判断该帧数据是否为音频数据
            if (aacRawDataPacket.stream_index != m_audioStream) {
                continue;
            }

            // 开始进行解码
            decodeRet = avcodec_decode_audio4(m_inPCodeCtx, pcmFrame, &decode_got_picture, &aacRawDataPacket);
            if(decodeRet < 0)
            {
                printf("解码音频出错\n");
                exit(0);
            }
            if(decode_got_picture>0)//写入本地pcm文件
            {
                swr_convert(au_convert_ctx, &mid_pcm_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pcmFrame->data, pcmFrame->nb_samples);
                qDebug()<<"index:"<<index++<<"    pts:"<<aacRawDataPacket.pts<<"  packet size"<<aacRawDataPacket.size;
                int audioDecodeBufferSize = av_samples_get_buffer_size(nullptr, mid_pcm_channels, pcmFrame->nb_samples, mid_pcm_sample_fmt, 1);
                fwrite(mid_pcm_buffer, 1, audioDecodeBufferSize, pcmFile);
            }


            // 初始化进行重采样的存储空间
            uint8_t **converted_input_samples = nullptr;
            if(init_converted_samples(&converted_input_samples, m_outPCodecCtx, pcmFrame->nb_samples))
            {
            }

            // 进行重采样
            if(convert_samples((const uint8_t**)pcmFrame->extended_data, converted_input_samples,
                               pcmFrame->nb_samples, resample_context))
            {
            }

            //将采样结果加入进fifo中
            add_samples_to_fifo(fifo, converted_input_samples,pcmFrame->nb_samples);

            // 释放重采样存储空间
            if (converted_input_samples)
            {
                av_freep(&converted_input_samples[0]);
                free(converted_input_samples);
            }
            av_free_packet(&aacRawDataPacket);
            av_free(pcmFrame);
        }
        // 从fifo队列中读入数据
        while (av_audio_fifo_size(fifo) >= output_frame_size || finished) {

            AVFrame *frame;

            frame = av_frame_alloc();

            const int frame_size = FFMIN(av_audio_fifo_size(fifo),m_outPCodecCtx->frame_size);

            // 设置输入帧的相关参数
            (frame)->nb_samples     = frame_size;
            (frame)->channel_layout = m_outPCodecCtx->channel_layout;
            (frame)->format         = m_outPCodecCtx->sample_fmt;
            (frame)->sample_rate    = m_outPCodecCtx->sample_rate;

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
            pkt.data = nullptr;
            pkt.size = 0;

            AVPacket *dpkt = av_packet_alloc();
            av_init_packet(dpkt);

            int data_present = 0;

            frame->pts = av_frame_get_best_effort_timestamp(frame);
            frame->pict_type=AV_PICTURE_TYPE_NONE;

            // 将pcm数据进行编码
            if ((error = avcodec_encode_audio2(m_outPCodecCtx, &pkt,frame, &data_present)) < 0)
            {
                av_free_packet(&pkt);
            }
            av_frame_free(&frame);

            WriteADTSHeader(pkt.size, 48000, 2);
            // 如果编码成功，写入文件
            if (data_present)
            {

                int i =  ADTS(&pkt, &dpkt);

                //jrtplib发送包含ADTS头部的数据
                Asender.SendAACPacket((unsigned char*)dpkt->data, dpkt->size);
                fwrite(dpkt->data, 1, dpkt->size, outAudioFile);
            }

            av_free_packet(&pkt);
            av_free_packet(dpkt);
        }

    }

    swr_free(&au_convert_ctx);
    av_free(mid_pcm_buffer);
    fclose(outAudioFile);
    fclose(pcmFile);
    closeAudioRecord();
}
