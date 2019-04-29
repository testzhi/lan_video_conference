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
void XVideoRecordThread::setVideoOutputPath(const QString &videoOutputPath)
{
    m_videoOutputPath = videoOutputPath;
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

void XVideoRecordThread::run()
{
    m_videoOutputPath = "test.yuv";
    m_videoOutputYUV420 = nullptr;
    m_videoOptions = nullptr;
    m_formatCtx = nullptr;
    m_pCodecCtx = nullptr;
    av_register_all();
    avdevice_register_all();
    avformat_network_init();

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

    int videoStream = -1;
    //查找视频中包含的流信息，
    for (int i = 0; i < m_formatCtx->nb_streams; i++)
    {
        if (m_formatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
            break;
        }
    }

    if (videoStream == -1)
    {
        qDebug() << "不能找到任何视频流";
        return;
    }

    m_pCodecCtx = m_formatCtx->streams[videoStream]->codec;
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

    if(!m_videoOutputPath.isEmpty())
        m_videoOutputYUV420 = fopen(m_videoOutputPath.toStdString().c_str(), "wb+");


    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameYUV = av_frame_alloc();


    m_pixWidth = m_pCodecCtx->width;
    m_pixHeight = m_pCodecCtx->height;
    qDebug() << m_pixWidth << "          " << m_pixHeight ;

    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB32, m_pCodecCtx->width,m_pCodecCtx->height);
    uint8_t *out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameYUV, out_buffer, AV_PIX_FMT_YUV420P, m_pCodecCtx->width, m_pCodecCtx->height);
    struct SwsContext *img_convert_ctx = sws_getContext(m_pCodecCtx->width, m_pCodecCtx->height, m_pCodecCtx->pix_fmt, m_pCodecCtx->width/2, m_pCodecCtx->height, AV_PIX_FMT_RGB555, SWS_BICUBIC, nullptr, nullptr, nullptr);


    AVPacket *packet = (AVPacket *) malloc(sizeof(AVPacket));
    int y_size = m_pCodecCtx->width * m_pCodecCtx->height;
    av_new_packet(packet, y_size);

    av_dump_format(m_formatCtx, 0, m_videoSource.toStdString().c_str(), 0); //输出视频信息

    int ret, got_picture;

    while (1)
    {
        if(m_playerState == Pause) {
            break;
        }
        if(av_read_frame(m_formatCtx, packet)>=0)
        {
            if(packet->stream_index == videoStream)
            {
                ret = avcodec_decode_video2(m_pCodecCtx, pFrame, &got_picture, packet);
                if(ret < 0)
                {
                    qDebug() << "解码错误";
                    return;
                }
                if(got_picture)
                {

                    sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, m_pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
                    int yy_size = m_pCodecCtx->width * m_pCodecCtx->height;
                    QSize qsize(m_pixWidth, m_pixHeight);
                    QImage *tmpImg = new QImage((uchar *)out_buffer, m_pCodecCtx->width, m_pCodecCtx->height, QImage::Format_RGB555);

                    QImage image = tmpImg->scaled(m_pCodecCtx->width*m_imageScale, m_pCodecCtx->height*m_imageScale); //把图像复制一份 传递给界面显示
                    emit sig_GetOneFrame(image);  //发送信号
                    if(!m_videoOutputPath.isEmpty())
                    {
                        fwrite(pFrameYUV->data[0], 1, yy_size, m_videoOutputYUV420);    //Y
                        fwrite(pFrameYUV->data[1], 1, yy_size/4, m_videoOutputYUV420);  //U
                        fwrite(pFrameYUV->data[2], 1, yy_size/4, m_videoOutputYUV420);  //V
                    }
                }
            }
        }
        av_free_packet(packet);
    }


    sws_freeContext(img_convert_ctx);
    av_free(pFrame);
    av_free(out_buffer);
    fclose(m_videoOutputYUV420);

    emit sig_GetOneFrame(QImage());
    pausePlay();

//    av_free(out_buffer);
    av_free(pFrameYUV);
    avcodec_close(m_pCodecCtx);
    avformat_close_input(&m_formatCtx);
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


