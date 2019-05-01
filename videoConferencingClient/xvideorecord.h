#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H

#include <QThread>
#include <QImage>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include <libavutil/time.h>
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include <libavdevice/avdevice.h>
#include <libavutil/audio_fifo.h>
#include <SDL2/SDL.h>
}

typedef struct PacketQueue {
    AVPacketList *first_pkt, *last_pkt;
    int nb_packets;
    int size;
} PacketQueue;


typedef struct VideoState {
    AVCodecContext *aCodecCtx; //音频解码器
    AVFrame *audioFrame;// 解码音频过程中的使用缓存
    PacketQueue *audioq;

    double video_clock; ///<pts of last decoded frame / predicted pts of next decoded frame

    AVStream *video_st;

} VideoState;

enum PlayerState
{
    Stop,
    Pause,
    Playing
};

class XVideoRecordThread  : public QThread
{
    Q_OBJECT
public:
    explicit XVideoRecordThread(QString devSource, QString imtSource);
    ~XVideoRecordThread();

    void initVideoRecord();
    void closeVideoRecord();

    void initH264OutputFile();
    void closeH264OutputFile();

    void setFileName(QString &path);
    void setVideoSource(const QString &videoSource);
    void setVideoInputFormat(const QString &videoInputFormat);
    void startPlay();
    void stopPlay();
    void pausePlay();

    int pixWidth() const;
    int pixHeight() const;


    double imageScale() const;
    void setImageScale(double imageScale);

signals:
    void sig_GetOneFrame(QImage); //每获取到一帧图像 就发送此信号
    void sig_totalTimeChanged(QString, qint64);
    void sig_currentTimeChanged(QString, qint64);

protected:
    void run();


private:
    QString m_fileName;
    VideoState m_videoState{};//用来 传递给 SDL音频回调函数的数据
    double m_imageScale;

    AVFormatContext	*m_formatCtx;
    AVCodecContext *m_pCodecCtx;
    AVDictionary *m_videoOptions;
    int m_videoStream;
    QString m_videoInputFormat{"video4linux2"};///音频"alsa"
    QString m_videoSource;
    PlayerState m_playerState;

    AVFormatContext *m_outFormatCtx;
    AVCodecContext *m_pOutCodecCtx;
    AVDictionary *m_videoOutputOptions;
    QString m_H264OutputFilePath;
    AVStream *m_video_st;

    int m_pixWidth;
    int m_pixHeight;
};

#endif // XVIDEOTHREAD_H
