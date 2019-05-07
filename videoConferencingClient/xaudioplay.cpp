#include "xaudioplay.h"
#include <QDebug>

#define MAX_AUDIO_FRAME_SIZE 192000 // 1 second of 48khz 32bit audio
static  Uint8  *audioChunk;


XAudioPlay::XAudioPlay()
{

}

void XAudioPlay::initAudioPlay()
{
    av_register_all();
    avformat_network_init();
    m_pFormatCtx = nullptr;
    m_options = nullptr;
    m_pCodecCtx = nullptr;
    m_pFormatCtx = avformat_alloc_context();

    if(avformat_open_input(&m_pFormatCtx, m_fileName.toStdString().c_str(), nullptr, nullptr)!= 0){
        qDebug() << "不能打开音频文件." ;
        exit(0);
    }
    if(avformat_find_stream_info(m_pFormatCtx,nullptr)<0){
        printf("不能找到音频流信息.\n");
        exit(0);
    }
    av_dump_format(m_pFormatCtx, 0, m_fileName.toStdString().c_str(), false);


    for(int i=0; i < m_pFormatCtx->nb_streams; i++)
        if(m_pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
        {
            m_audioStream=i;
            break;
        }

    if(m_audioStream==-1)
    {
        printf("不能找到任何音频流.\n");
        exit(0);
    }

    AVCodecContext	*pCodecCtx=m_pFormatCtx->streams[m_audioStream]->codec;

    // Find the decoder for the audio stream
    AVCodec	*pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==nullptr)
    {
        printf("不能发现音频解码器.\n");
        exit(0);
    }

    // Open codec
    if(avcodec_open2(pCodecCtx, pCodec,nullptr)<0){
        printf("不能打开音频解码器.\n");
        exit(0);
    }
}

void XAudioPlay::closeAudioPlay()
{
    avcodec_close(m_pCodecCtx);;
    avformat_close_input(&m_pFormatCtx);
}

void XAudioPlay::run()
{

    initAudioPlay();

    AVPacket *packet=(AVPacket *)av_malloc(sizeof(AVPacket));
    av_init_packet(packet);

    uint64_t out_channel_layout=AV_CH_LAYOUT_STEREO;
    int out_nb_samples=m_pCodecCtx->frame_size;
    AVSampleFormat out_sample_fmt=AV_SAMPLE_FMT_S16;
    int out_sample_rate=44100;
    int out_channels=av_get_channel_layout_nb_channels(out_channel_layout);
    //Out Buffer Size
    int out_buffer_size=av_samples_get_buffer_size(nullptr,out_channels ,out_nb_samples,out_sample_fmt, 1);

    uint8_t *out_buffer=(uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE*2);
    AVFrame *pFrame=av_frame_alloc();
    //SDL------------------
    //Init
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf( "Could not initialize SDL - %s\n", SDL_GetError());
        exit(0);
    }
    //SDL_AudioSpec
    SDL_AudioSpec wanted_spec;
    wanted_spec.freq = out_sample_rate;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = out_channels;
    wanted_spec.silence = 0;
    wanted_spec.samples = out_nb_samples;
    wanted_spec.callback = fill_Audio;
    wanted_spec.userdata = m_pCodecCtx;

    if (SDL_OpenAudio(&wanted_spec, nullptr)<0){
        printf("can't open audio.\n");
        exit(0);
    }

    //FIX:Some Codec's Context Information is missing
    int64_t in_channel_layout=av_get_default_channel_layout(m_pCodecCtx->channels);



    int ret;
    uint32_t len = 0;
    int got_picture;
    int index = 0;
    //Swr
    struct SwrContext *au_convert_ctx = swr_alloc();
    au_convert_ctx=swr_alloc_set_opts(au_convert_ctx,out_channel_layout, out_sample_fmt, out_sample_rate, in_channel_layout,m_pCodecCtx->sample_fmt , m_pCodecCtx->sample_rate,0, nullptr);
    swr_init(au_convert_ctx);

    while(av_read_frame(m_pFormatCtx, packet)>=0){
        if(packet->stream_index==m_audioStream){
            ret = avcodec_decode_audio4(m_pCodecCtx, pFrame,&got_picture, packet);
            if ( ret < 0 ) {
                printf("Error in decoding audio frame.\n");
                exit(0);
            }
            if ( got_picture > 0 ){
                swr_convert(au_convert_ctx,&out_buffer, MAX_AUDIO_FRAME_SIZE,(const uint8_t **)pFrame->data , pFrame->nb_samples);
                printf("index:%5d\t pts:%ld\t packet size:%d\n",index,packet->pts,packet->size);



                index++;
            }

            while(audioLength>0)//Wait until finish
                SDL_Delay(1);

            //Set audio buffer (PCM data)
            audioChunk = (Uint8 *) out_buffer;
            //Audio buffer length
            audioLength =out_buffer_size;
            audioPostion = audioChunk;

            //Play
            SDL_PauseAudio(0);
        }
        av_free_packet(packet);
    }

    swr_free(&au_convert_ctx);

    SDL_CloseAudio();//Close SDL
    SDL_Quit();

    av_free(out_buffer);

    closeAudioPlay();

}

QString XAudioPlay::fileName() const
{
    return m_fileName;
}

void XAudioPlay::setFileName(const QString &fileName)
{
    m_fileName = fileName;
}

void XAudioPlay::startPlay()
{
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

void XAudioPlay::stopPlay()
{

}

void XAudioPlay::pausePlay()
{
    m_playerState = Pause;
    qDebug() << "Pause...";
}




