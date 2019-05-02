#include "xaudiorecord.h"
#include <QDebug>

#define MAX_AUDIO_FRAME_SIZE 192000

XAudioRecord::XAudioRecord(QString devSource, QString imtSource)
    :m_audioInputSource(devSource),m_audioInputFormat(imtSource)
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
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        qDebug() << "无法初始化SDL - " << SDL_GetError();
        exit(0);
    }
    m_inFormatContext = avformat_alloc_context();
    AVInputFormat *inputAudioFmt = av_find_input_format(m_audioInputFormat.toStdString().c_str());
    if(avformat_open_input(&m_inFormatContext, m_audioInputSource.toStdString().c_str(), inputAudioFmt, &m_inOptions)!=0)
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

}

void XAudioRecord::closeAACOutputFile()
{

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

void XAudioRecord::run()
{
    initAudioRecord();

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
    AVPacket *aacRawDataPacket=(AVPacket *)av_malloc(sizeof(AVPacket));
    AVFrame	*pcmFrame=av_frame_alloc();
    av_init_packet(aacRawDataPacket);
    int decodeRet, decode_got_picture;

    int index = 0;
    while(av_read_frame(m_inFormatContext, aacRawDataPacket) >= 0)
    {
        if(aacRawDataPacket->stream_index == m_audioStream)
        {
            decodeRet = avcodec_decode_audio4(m_inPCodeCtx, pcmFrame, &decode_got_picture, aacRawDataPacket);
            if(decodeRet < 0)
            {
                printf("解码音频出错\n");
                exit(0);
            }

            if(decode_got_picture>0)
            {
                swr_convert(au_convert_ctx, &mid_pcm_buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pcmFrame->data, pcmFrame->nb_samples);
                qDebug()<<"index:"<<index++<<"    pts:"<<aacRawDataPacket->pts<<"  packet size"<<aacRawDataPacket->size;
                int audioDecodeBufferSize = av_samples_get_buffer_size(nullptr, mid_pcm_channels, pcmFrame->nb_samples, mid_pcm_sample_fmt, 1);
            }

        }
        av_free_packet(aacRawDataPacket);
    }
    swr_free(&au_convert_ctx);
    av_free(pcmFrame);
    av_free(mid_pcm_buffer);

    closeAudioRecord();
}
