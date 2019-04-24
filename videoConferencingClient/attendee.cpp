#include "attendee.h"
#include <iostream>

#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)
// 1 second of 48khz 32bit audio
#define MAX_AUDIO_FRAME_SIZE 192000
//Refresh Event
#define REFRESH_EVENT  (SDL_USEREVENT + 1)
#define BREAK_EVENT  (SDL_USEREVENT + 2)
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)
#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)
int thread_exit = 0;
int play_video_thread_exit = 0;
int thread_pause = 0;
//Buffer:
static  Uint8  *audio_chunk;
static  Uint32  audio_len;
static  Uint8  *audio_pos;

using namespace std;
int sdl_play_refresh_thread(void *opaque)
{
    play_video_thread_exit=0;
    thread_pause=0;

    while (!play_video_thread_exit) {
        if(!thread_pause){
            SDL_Event event;
            event.type = SFM_REFRESH_EVENT;
            SDL_PushEvent(&event);
        }
        SDL_Delay(40);
    }
    play_video_thread_exit=0;
    thread_pause=0;
    //Break
    SDL_Event event;
    event.type = SFM_BREAK_EVENT;
    SDL_PushEvent(&event);

    return 0;
}

int sfp_refresh_thread(void *opaque)
{
    while (thread_exit == 0) {
        SDL_Event event;
        event.type = SFM_REFRESH_EVENT;
        SDL_PushEvent(&event);
        SDL_Delay(40);
    }
    return 0;
}

void fill_audio(void *udata, Uint8 *stream, int len)
{
    //SDL 2.0
    SDL_memset(stream, 0, len);
    if(audio_len == 0)		/*  Only  play  if  we  have  data  left  */
        return;
    len=(len > audio_len ? audio_len : len);	/*  Mix  as  much  data  as  possible  */

    SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
    audio_pos += len;
    audio_len -= len;
}

Attendee::Attendee()
{
    av_register_all();
    avdevice_register_all();
    avformat_network_init();




    m_pCameraFrameYUV = av_frame_alloc();
    m_pScreenCaptureFrameYUV = av_frame_alloc();

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        cout << "无法初始化SDL - " << SDL_GetError() << endl;
        exit(0);
    }
}
//获取录像 录屏 录音环境
void Attendee::initScreenCaptureInputSource()
{
    //Set some options
    //grabbing frame rate
    //av_dict_set(&m_screenCaptureOptions,"framerate","5",0);
    //Make the grabbed area follow the mouse
    //av_dict_set(&m_screenCaptureOptions,"follow_mouse","centered",0);
    //Video frame size. The default is to capture the full screen
    //av_dict_set(&m_screenCaptureOptions,"video_size","640x480",0);

    m_pScreenCaptureFormatCtx = avformat_alloc_context();

    AVInputFormat *ifmt = av_find_input_format("x11grab");
    //Grab at position 10,20
    char screenCaptureUrl[] = ":0.0+10,20";
    if(avformat_open_input(&m_pScreenCaptureFormatCtx, screenCaptureUrl, ifmt, &m_screenCaptureOptions)!=0)
    {
        cout << "不能打开屏幕录制器." << endl;
        exit(0);
    }
}
void Attendee::initCameraInputSource()
{
    m_pCameraFormatCtx = avformat_alloc_context();

    char cameraUrl[] = "/dev/video0";
    AVInputFormat *inputVideoFmt = av_find_input_format("video4linux2");
    if(avformat_open_input(&m_pCameraFormatCtx, cameraUrl, inputVideoFmt, &m_cameraOptions)!=0)
    {
        cout << "不能打开相机.\n" << endl;
        exit(0);
    }

}
void Attendee::initAudioInputSource()
{
    m_pAudioFormatCtx = avformat_alloc_context();

    char audioUrl[] = "hw:1";
    AVInputFormat *inputAudioFmt = av_find_input_format("alsa");
    if(avformat_open_input(&m_pAudioFormatCtx, audioUrl, inputAudioFmt, &m_audioOptions)!=0)
    {
        cout << "不能打开音频设备.\n" << endl;
        exit(0);
    }
}

void Attendee::initReadVideoInputSource(string filePath)
{
    m_fsVideoFormatCtx = avformat_alloc_context();
    if(avformat_open_input(&m_fsVideoFormatCtx, filePath.data(), nullptr, &m_fsVideoOptions)!=0){
        printf("Couldn't open input stream.\n");
        exit(0);
    }
}

void Attendee::initReadAudioInputSource(string filePath)
{
    m_fsAudioFormatCtx = avformat_alloc_context();
}

void Attendee::getVideoStream(int videoKind)
{
    if(videoKind == CAMERA_VIDEO)
    {
        if(avformat_find_stream_info(m_pCameraFormatCtx, &m_cameraOptions) < 0)
        {
            printf("不能找到视频流信息.\n");
            exit(0);
        }
        for(int i = 0; i < m_pCameraFormatCtx->nb_streams; i++)
            if(m_pCameraFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                m_cameraIndex = i;
                break;
            }
        if(m_cameraIndex == -1)
        {
            printf("不能找到任何视频流.\n");
            exit(0);
        }
        m_pCameraCodecCtx = m_pCameraFormatCtx->streams[m_cameraIndex]->codec;
    }else if(videoKind == SCREEN_CAPTURE_VIDEO) {
        if(avformat_find_stream_info(m_pScreenCaptureFormatCtx, &m_screenCaptureOptions) < 0)
        {
            printf("不能找到视频流信息.\n");
            exit(0);
        }
        for(int i = 0; i < m_pScreenCaptureFormatCtx->nb_streams; i++)
            if(m_pScreenCaptureFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                m_screenCaptureIndex = i;
                break;
            }
        if(m_screenCaptureIndex == -1)
        {
            printf("不能找到任何视频流.\n");
            exit(0);
        }
        m_pScreenCaptureCodecCtx = m_pScreenCaptureFormatCtx->streams[m_screenCaptureIndex]->codec;
    } else {
        if(avformat_find_stream_info(m_fsVideoFormatCtx, NULL) < 0)
        {
            printf("不能找到视频流信息.\n");
            exit(0);
        }
        for(int i = 0; i < m_fsVideoFormatCtx->nb_streams; i++)
            if(m_fsVideoFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                m_fsVideoIndex = i;
                break;
            }
        if(m_fsVideoIndex == -1)
        {
            printf("不能找到任何视频流.\n");
            exit(0);
        }
        m_fsVideoCodecCtx = m_fsVideoFormatCtx->streams[m_cameraIndex]->codec;
    }
}
void Attendee::getAudioStream(int audioKind)
{
    if(audioKind == RECORD_AUDIO)
    {
        if(avformat_find_stream_info(m_pAudioFormatCtx, &m_audioOptions) <0 )
        {
            printf("不能找到音频流信息.\n");
            exit(0);
        }
        for(int i = 0; i < m_pAudioFormatCtx->nb_streams; i++)
            if(m_pAudioFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                m_audioIndex = i;
                break;
            }
        if(m_audioIndex == -1)
        {
            printf("不能找到任何音频流.\n");
            exit(0);
        }
        m_pAudioCodecCtx = m_pAudioFormatCtx->streams[m_audioIndex]->codec;
        m_pAudioCodecCtx->channel_layout = av_get_default_channel_layout(m_pAudioCodecCtx->channels);
    } else {
        if(avformat_find_stream_info(m_fsAudioFormatCtx, &m_fsAudioOptions)<0)
        {
            printf("不能找到音频流信息.\n");
            exit(0);
        }
        for(int i = 0; i < m_fsAudioFormatCtx->nb_streams; i++)
            if(m_fsAudioFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                m_fsAudioIndex = i;
                break;
            }
        if(m_fsAudioIndex == -1)
        {
            printf("不能找到任何音频流.\n");
            exit(0);
        }
        m_fsAudioCodecCtx = m_fsAudioFormatCtx->streams[m_fsAudioIndex]->codec;
        m_fsAudioCodecCtx->channel_layout = av_get_default_channel_layout(m_fsAudioCodecCtx->channels);

    }

}

void Attendee::openVideoCodec(int videoKind)
{
    if(videoKind == CAMERA_VIDEO)
    {
        AVCodec	*pCameraCodec = avcodec_find_decoder(m_pCameraCodecCtx->codec_id);
        if(pCameraCodec == nullptr)
        {
            printf("不能发现视频编码器.\n");
            exit(0);
        }
        if(avcodec_open2(m_pCameraCodecCtx, pCameraCodec, &m_cameraOptions)<0)
        {
            printf("不能打开视频编码器.\n");
            exit(0);
        }
    }else if(videoKind == SCREEN_CAPTURE_VIDEO){
        AVCodec	*pScreenCaptureCodec = avcodec_find_decoder(m_pScreenCaptureCodecCtx->codec_id);
        if(pScreenCaptureCodec == nullptr)
        {
            printf("不能发现视频编码器.\n");
            exit(0);
        }
        if(avcodec_open2(m_pScreenCaptureCodecCtx, pScreenCaptureCodec, &m_screenCaptureOptions)<0)
        {
            printf("不能打开视频编码器.\n");
            exit(0);
        }
    }else {
        AVCodec	*fsVideoCodec = avcodec_find_decoder(m_fsVideoCodecCtx->codec_id);
        if(fsVideoCodec == nullptr)
        {
            printf("不能发现视频编码器.\n");
            exit(0);
        }
        if(avcodec_open2(m_fsVideoCodecCtx, fsVideoCodec, &m_fsVideoOptions)<0)
        {
            printf("不能打开视频编码器.\n");
            exit(0);
        }
    }
}
void Attendee::openAudioCodec(int audioKind)
{
    if(audioKind == RECORD_AUDIO)
    {
        AVCodec	*pAudioCodec = avcodec_find_decoder(m_pAudioCodecCtx->codec_id);
        if(pAudioCodec == nullptr)
        {
            printf("不能发现音频编码器.\n");
            exit(0);
        }
        if(avcodec_open2(m_pAudioCodecCtx, pAudioCodec, &m_audioOptions)<0)
        {
            printf("不能打开音频编码器.\n");
            exit(0);
        }
    }else {
        AVCodec	*pAudioCodec = avcodec_find_decoder(m_fsAudioCodecCtx->codec_id);
        if(pAudioCodec == nullptr)
        {
            printf("不能发现音频编码器.\n");
            exit(0);
        }
        if(avcodec_open2(m_fsAudioCodecCtx, pAudioCodec, &m_fsAudioOptions)<0)
        {
            printf("不能打开音频编码器.\n");
            exit(0);
        }
    }
}

void Attendee::recordVideo(AVFormatContext *videoFormatCtx, int videoIndex, AVCodecContext *videoCodecCtx, AVFrame *videoFrameYUV, string filePath)
{
    m_fp_yuv_video = fopen(filePath.data(), "wb+");

    uint8_t *videoOutBuffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, videoCodecCtx->width, videoCodecCtx->height));
    avpicture_fill((AVPicture *)videoFrameYUV, videoOutBuffer, AV_PIX_FMT_YUV420P, videoCodecCtx->width, videoCodecCtx->height);

    struct SwsContext *img_convert_ctx;
    img_convert_ctx = sws_getContext(videoCodecCtx->width, videoCodecCtx->height, videoCodecCtx->pix_fmt, videoCodecCtx->width, videoCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, nullptr, nullptr, nullptr);


    AVPacket *videoPacket=(AVPacket *)av_malloc(sizeof(AVPacket));
    AVFrame	*pVideoFrame=av_frame_alloc();
    av_init_packet(videoPacket);
    int videoRet, video_got_picture;

    screen_w = videoCodecCtx->width;
    screen_h = videoCodecCtx->height;
    screen = SDL_CreateWindow("Meeting Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_w, screen_h, SDL_WINDOW_OPENGL);
    SDL_SetWindowFullscreen(screen, 0);
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
    //IYUV: Y + U + V  (3 planes)
    //YV12: Y + V + U  (3 planes)
    SDL_Texture *sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, videoCodecCtx->width, videoCodecCtx->height);

    SDL_Rect sdlRect;
    sdlRect.x = 0;
    sdlRect.y = 0;
    sdlRect.w = screen_w;
    sdlRect.h = screen_h;
    //SDL_Video End

    if(!screen)
    {
        cout << "SDL:不能设置屏幕模式 - exiting: " << SDL_GetError() << endl;
        exit(0);
    }

    //Event Loop
    SDL_Event event;
    SDL_Thread *video_and_audio_tid = SDL_CreateThread(sfp_refresh_thread, nullptr, nullptr);

    for (;;) {
        //Wait
        SDL_WaitEvent(&event);
        if(event.type==SFM_REFRESH_EVENT){
            //------------------------------
            if(av_read_frame(videoFormatCtx, videoPacket)>=0)
            {
                if(videoPacket->stream_index == videoIndex)
                {
                    videoRet = avcodec_decode_video2(videoCodecCtx, pVideoFrame, &video_got_picture, videoPacket);
                    if(videoRet < 0)
                    {
                        cout << "解码错误" << endl;
                        exit(0);
                    }
                    if(video_got_picture)
                    {
                        sws_scale(img_convert_ctx, (const uint8_t* const*)pVideoFrame->data, pVideoFrame->linesize, 0, videoCodecCtx->height, videoFrameYUV->data, videoFrameYUV->linesize);
                        //SDL---------------------------
                        SDL_UpdateTexture(sdlTexture, nullptr, videoFrameYUV->data[0], videoFrameYUV->linesize[0] );
                        SDL_RenderClear(sdlRenderer );
                        //SDL_RenderCopy( sdlRenderer, sdlTexture, &sdlRect, &sdlRect );
                        SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, nullptr);
                        SDL_RenderPresent(sdlRenderer);
                        //SDL End-----------------------
                        int y_size = videoCodecCtx->width * videoCodecCtx->height;
                        fwrite(videoFrameYUV->data[0], 1, y_size, m_fp_yuv_video);    //Y
                        fwrite(videoFrameYUV->data[1], 1, y_size/4,m_fp_yuv_video);  //U
                        fwrite(videoFrameYUV->data[2], 1, y_size/4,m_fp_yuv_video);  //V

                    }
                }
                av_free_packet(videoPacket);
            }else{
                //Exit Thread
                thread_exit=1;
                break;
            }
        }else if(event.type==SDL_QUIT){
            thread_exit=1;
            break;
        }
        av_free_packet(videoPacket);
    }
    sws_freeContext(img_convert_ctx);
    av_free(pVideoFrame);
    av_free(videoOutBuffer);
    fclose(m_fp_yuv_video);
}
void Attendee::recordCamera(string cameraPath)
{
    recordVideo(m_pCameraFormatCtx, m_cameraIndex, m_pCameraCodecCtx, m_pCameraFrameYUV, cameraPath);
}
void Attendee::recordScreenCapture(string screenCapturePath)
{
    recordVideo(m_pScreenCaptureFormatCtx, m_screenCaptureIndex, m_pScreenCaptureCodecCtx, m_pScreenCaptureFrameYUV, screenCapturePath);
}
void Attendee::recordAudio(string audioPath)
{
    //AUDIO OUTPUT
    uint64_t out_channel_layout = AV_CH_LAYOUT_STEREO;//Out Audio Param
    int out_nb_samples = m_pAudioCodecCtx->frame_size;//nb_samples: AAC-1024 MP3-1152
    AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
    int out_sample_rate = 44100;
    int out_channels = av_get_channel_layout_nb_channels(out_channel_layout);

    //    AUDIO INPUT
    //    int64_t in_channel_layout = av_get_default_channel_layout(m_pAudioCodecCtx->channels);
    int64_t in_channel_layout = m_pAudioCodecCtx->channel_layout;

    //Swr
    struct SwrContext *au_convert_ctx = swr_alloc();
    au_convert_ctx=swr_alloc_set_opts(au_convert_ctx, out_channel_layout, out_sample_fmt, out_sample_rate, in_channel_layout, m_pAudioCodecCtx->sample_fmt , m_pAudioCodecCtx->sample_rate, 0, nullptr);
    swr_init(au_convert_ctx);

    uint8_t *audioOutBuffer = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);


    m_fp_yuv_audio_in = fopen(audioPath.data(), "wb");
    AVPacket *audioPacket=(AVPacket *)av_malloc(sizeof(AVPacket));
    AVFrame	*pAudioFrame=av_frame_alloc();
    av_init_packet(audioPacket);
    int audioRet, audio_got_picture;

    int index = 0;
    while(av_read_frame(m_pAudioFormatCtx, audioPacket) >= 0)
    {
        if(audioPacket->stream_index == m_audioIndex)
        {
            audioRet = avcodec_decode_audio4(m_pAudioCodecCtx, pAudioFrame, &audio_got_picture, audioPacket);
            if(audioRet < 0)
            {
                printf("解码音频出错\n");
                exit(0);
            }

            if(audio_got_picture>0)
            {
                swr_convert(au_convert_ctx, &audioOutBuffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)pAudioFrame->data, pAudioFrame->nb_samples);
                printf("index:%5d\t pts:%lld\t packet size:%d\n", index++, audioPacket->pts, audioPacket->size);
                int audioOutBufferSize = av_samples_get_buffer_size(NULL, out_channels, pAudioFrame->nb_samples, out_sample_fmt, 1);

                fwrite(audioOutBuffer, 1, audioOutBufferSize, m_fp_yuv_audio_in);
            }

        }
        av_free_packet(audioPacket);
    }
    swr_free(&au_convert_ctx);
    av_free(pAudioFrame);
    av_free(audioOutBuffer);
    fclose(m_fp_yuv_audio_in);
}



void Attendee::sdlPlayVideo(string videoPath)
{
    initReadVideoInputSource(videoPath);
    getVideoStream(FILE_VIDEO);
    openVideoCodec(FILE_VIDEO);

    AVFrame	*pFrame,*pFrameYUV;
    pFrame=av_frame_alloc();
    pFrameYUV=av_frame_alloc();


    uint8_t *buffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, m_fsVideoCodecCtx->width, m_fsVideoCodecCtx->height));
    avpicture_fill((AVPicture *)pFrameYUV, buffer, AV_PIX_FMT_YUV420P, m_fsVideoCodecCtx->width, m_fsVideoCodecCtx->height);

    struct SwsContext *img_convert_ctx;
    img_convert_ctx = sws_getContext(m_fsVideoCodecCtx->width, m_fsVideoCodecCtx->height, m_fsVideoCodecCtx->pix_fmt, m_fsVideoCodecCtx->width, m_fsVideoCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

    screen = SDL_CreateWindow("Play Conferences", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              m_fsVideoCodecCtx->width, m_fsVideoCodecCtx->height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    SDL_SetWindowFullscreen(screen, 0);
    if(!screen)
    {
        printf("SDL: could not create window - exiting:%s\n",SDL_GetError());
        exit(0);
    }
    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
    Uint32 pixformat=0;
    //IYUV: Y + U + V  (3 planes)
    //YV12: Y + V + U  (3 planes)
    pixformat= SDL_PIXELFORMAT_IYUV;
    SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer,pixformat, SDL_TEXTUREACCESS_STREAMING,m_fsVideoCodecCtx->width,m_fsVideoCodecCtx->height);

    SDL_Rect sdlRect;
    sdlRect.x=0;
    sdlRect.y=0;
    sdlRect.w=screen_w;
    sdlRect.h=screen_h;

    //------------------------------
    SDL_Thread *refresh_thread = SDL_CreateThread(sdl_play_refresh_thread,NULL,NULL);
    SDL_Event event;
    //Event Loop
    AVPacket *packet=(AVPacket *)av_malloc(sizeof(AVPacket));
    int ret, got_picture;
    for (;;) {
        //Wait
        SDL_WaitEvent(&event);
        if(event.type==SFM_REFRESH_EVENT){
            //------------------------------
            if(av_read_frame(m_fsVideoFormatCtx, packet)>=0){
                if(packet->stream_index==m_fsVideoIndex){
                    ret = avcodec_decode_video2(m_fsVideoCodecCtx, pFrame, &got_picture, packet);
                    if(ret < 0){
                        printf("Decode Error.\n");
                        exit(0);
                    }
                    if(got_picture){
                        sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, m_fsVideoCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
                        //SDL---------------------------
                        SDL_UpdateTexture( sdlTexture, NULL, pFrameYUV->data[0], pFrameYUV->linesize[0] );
                        SDL_RenderClear( sdlRenderer );
                        //SDL_RenderCopy( sdlRenderer, sdlTexture, &sdlRect, &sdlRect );
                        SDL_RenderCopy( sdlRenderer, sdlTexture, NULL, NULL);
                        SDL_RenderPresent( sdlRenderer );
                        //SDL End-----------------------
                    }
                }
                av_free_packet(packet);
            }else{
                //Exit Thread
                play_video_thread_exit=1;
            }
        }else if(event.type==SDL_KEYDOWN){
            //Pause
            if(event.key.keysym.sym==SDLK_SPACE)
                thread_pause=!thread_pause;
        }else if(event.type==SDL_QUIT){
            play_video_thread_exit=1;
        }else if(event.type==SFM_BREAK_EVENT){
            break;
        }

    }
    sws_freeContext(img_convert_ctx);
    av_frame_free(&pFrameYUV);
    av_frame_free(&pFrame);

}
void Attendee::sdlPlayAudio(string audioPath)
{
    SDL_AudioSpec wanted_spec;
    wanted_spec.freq = 44100;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.channels = 2;
    wanted_spec.silence = 0;
    wanted_spec.samples = 1024;
    wanted_spec.callback = fill_audio;

    if (SDL_OpenAudio(&wanted_spec, NULL)<0)
    {
        printf("can't open audio.\n");
        exit(0);
    }
    FILE *fp = fopen(audioPath.data(), "rb+");
    if(fp==NULL)
    {
        printf("cannot open this file\n");
        exit(0);
    }

    //For YUV420P
    int pcm_buffer_size=4096;
    char *pcm_buffer=(char *)malloc(pcm_buffer_size);
    int data_count=0;

    while(1){
        if (fread(pcm_buffer, 1, pcm_buffer_size, fp) != pcm_buffer_size){
            // Loop
            fseek(fp, 0, SEEK_SET);
            fread(pcm_buffer, 1, pcm_buffer_size, fp);
            data_count=0;
        }
        printf("Now Playing %10d Bytes data.\n",data_count);
        data_count += pcm_buffer_size;
        //Set audio buffer (PCM data)
        audio_chunk = (Uint8 *) pcm_buffer;
        //Audio buffer length
        audio_len = pcm_buffer_size;
        audio_pos = audio_chunk;
        //Play
        SDL_PauseAudio(0);
        while(audio_len>0)//Wait until finish
            SDL_Delay(1);
    }
    free(pcm_buffer);
}

Attendee::~Attendee()
{
    SDL_Quit();

    avcodec_close(m_pScreenCaptureCodecCtx);
    avcodec_close(m_pCameraCodecCtx);
    avcodec_close(m_pAudioCodecCtx);
    avcodec_close(m_fsAudioCodecCtx);
    avcodec_close(m_fsVideoCodecCtx);

    avformat_close_input(&m_pScreenCaptureFormatCtx);
    avformat_close_input(&m_pCameraFormatCtx);
    avformat_close_input(&m_pAudioFormatCtx);
    avformat_close_input(&m_fsAudioFormatCtx);
    avformat_close_input(&m_fsVideoFormatCtx);

}





