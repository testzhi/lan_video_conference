#include "xvideoplay.h"
#include <QDebug>
#include <QImage>

XVideoPlay::XVideoPlay(QString filename):m_filename(filename)
{

}

XVideoPlay::~XVideoPlay()
{
    m_playerState = Pause;
    avcodec_close(m_pCodecCtx);
    avformat_close_input(&m_formatCtx);
}

void XVideoPlay::initVideoPlay()
{
    m_videoOptions = nullptr;
    m_formatCtx = nullptr;
    m_pCodecCtx = nullptr;
    m_formatCtx = avformat_alloc_context();
    if(avformat_open_input(&m_formatCtx, m_filename.toStdString().c_str(), nullptr,nullptr)!=0){
        printf("Couldn't open input stream.\n");
        return;
    }
    if(avformat_find_stream_info(m_formatCtx,nullptr)<0){
        printf("Couldn't find stream information.\n");
        return;
    }
    m_videoStream=-1;
    for(int i=0; i<m_formatCtx->nb_streams; i++)
        if(m_formatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            m_videoStream=i;
            break;
        }
    if(m_videoStream==-1){
        printf("Didn't find a video stream.\n");
        return;
    }
    m_pCodecCtx = m_formatCtx->streams[m_videoStream]->codec;
    AVCodec *pCodec=avcodec_find_decoder(m_pCodecCtx->codec_id);
    if(pCodec==nullptr){
        printf("Codec not found.\n");
        return;
    }
    if(avcodec_open2(m_pCodecCtx, pCodec,nullptr)<0){
        printf("Could not open codec.\n");
        return;
    }
}

void XVideoPlay::initAudioPlay()
{

}

void XVideoPlay::startPlay()
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

void XVideoPlay::stopPlay()
{
    m_playerState = Stop;
    if(!this->isFinished() ) {
        this->stopPlay();
    }
    qDebug() << "STOP...";
}

void XVideoPlay::pausePlay()
{
    m_playerState = Pause;
    //    if( this->isRunning() ) {
    //        this->wait();
    //    }
    qDebug() << "Pause...";
}

void XVideoPlay::run()
{
    AVFrame *pFrame=av_frame_alloc();
    AVFrame *pFrameYUV=av_frame_alloc();

    uint8_t *out_buffer=(uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, m_pCodecCtx->width, m_pCodecCtx->height));
    avpicture_fill((AVPicture *)pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, m_pCodecCtx->width, m_pCodecCtx->height);
    struct SwsContext *img_convert_ctx = sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt, m_pCodecCtx->width, m_pCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, nullptr, nullptr, nullptr);
    AVPacket *packet=(AVPacket *)av_malloc(sizeof(AVPacket));



    AVFrame *pFrameRGB = av_frame_alloc();
    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB555, m_pCodecCtx->width,m_pCodecCtx->height);
    uint8_t *rgb_out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, rgb_out_buffer, AV_PIX_FMT_YUV420P, m_pCodecCtx->width, m_pCodecCtx->height);

    struct SwsContext *img_convert_ctx2 = sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt, m_pCodecCtx->width/2, m_pCodecCtx->height, AV_PIX_FMT_RGB555, SWS_BICUBIC, nullptr, nullptr, nullptr);
    //Output Info-----------------------------
    printf("---------------- File Information ---------------\n");
    av_dump_format(m_formatCtx,0,m_filename.toStdString().c_str(),0);
    printf("-------------------------------------------------\n");




    int ret, got_picture;
    while (1)
    {
        if(m_playerState == Pause)
            break;
        if(av_read_frame(m_formatCtx, packet)>=0)
        {
            if(packet->stream_index==m_videoStream){
                ret = avcodec_decode_video2(m_pCodecCtx, pFrame, &got_picture, packet);
                if(ret < 0){
                    qDebug() << "解码错误";
                    return;
                }
                if(got_picture){
                    sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, m_pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
                    //                    sws_scale(img_convert_ctx2, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, m_pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
                    sws_scale(img_convert_ctx2, (const uint8_t* const*)pFrameYUV->data, pFrameYUV->linesize, 0, m_pCodecCtx->height, pFrameRGB->data, pFrameRGB->linesize);
                    QImage *tmpImg = new QImage((uchar *)rgb_out_buffer, m_pCodecCtx->width, m_pCodecCtx->height, QImage::Format_RGB555);

                    QImage image = tmpImg->scaled(m_pCodecCtx->width*m_imageScale, m_pCodecCtx->height*m_imageScale); //把图像复制一份 传递给界面显示
                    emit sig_getAFrame(image);  //发送信号
                }
            }
            av_free_packet(packet);
        }
    }

    sws_freeContext(img_convert_ctx2);
    sws_freeContext(img_convert_ctx);
    av_free(out_buffer);
    av_free(rgb_out_buffer);
    av_frame_free(&pFrameRGB);
    av_frame_free(&pFrameYUV);
    av_frame_free(&pFrame);
    avcodec_close(m_pCodecCtx);
    avformat_close_input(&m_formatCtx);

}

double XVideoPlay::imageScale() const
{
    return m_imageScale;
}

void XVideoPlay::setImageScale(double imageScale)
{
    m_imageScale = imageScale;
}
