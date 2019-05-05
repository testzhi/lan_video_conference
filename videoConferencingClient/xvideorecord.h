#ifndef XVIDEOTHREAD_H
#define XVIDEOTHREAD_H

#include <QThread>
#include <QImage>
#include "videosender.h"
#include "aacsender.h"
#include "aacrecv.h"

extern "C"
{
#include "libavformat/avformat.h"
#include "libavutil/time.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavdevice/avdevice.h"
#include "libavutil/audio_fifo.h"
#include "libavcodec/avcodec.h"
#include "libavdevice/avdevice.h"
#include "libavutil/imgutils.h"
#include "libavfilter/avfilter.h"
#include "libavutil/audio_fifo.h"
#include "libavutil/avutil.h"
#include "libavutil/frame.h"
#include "libavutil/samplefmt.h"
#include "libavformat/avio.h"
#include "libavutil/avassert.h"
#include "libavutil/avstring.h"
#include "libavutil/opt.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include <SDL2/SDL.h>
}

#define SSRC           100
#define SERVER_PORT     5000
#define BASE_PORT     3000

#define ASSRC           102
#define A_DEST_PORT     8000
#define A_BASE_PORT     8050

//音频参数START-------------------------------
#define OUTPUT_BIT_RATE 96000
#define OUTPUT_CHANNELS 2
#define MAX_AUDIO_FRAME_SIZE 192000
#define ADTS_HEADER_SIZE 7

const int avpriv_mpeg4audio_sample_rates[16] = {
    96000, 88200, 64000, 48000, 44100, 32000,
    24000, 22050, 16000, 12000, 11025, 8000, 7350
};

const uint8_t ff_mpeg4audio_channels[8] = {
    0, 1, 2, 3, 4, 5, 6, 8
};
//音频参数END---------------------------------

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

    void checkerror(int rtperr);
    void SetH264RTPParams(SVideoSender& sess,uint32_t destip,uint16_t destport,uint16_t baseport);
    void SetAACRTPParams(CAACSender& sess,uint32_t destip,uint16_t destport,uint16_t baseport);

    //音频函数相关START----------------------------------------
    static int GetSampleIndex(int sample_rate);
    static int init_resampler(AVCodecContext *input_codec_context,
                              AVCodecContext *output_codec_context,
                              SwrContext **resample_context);

    static int init_converted_samples(uint8_t ***converted_input_samples,
                                      AVCodecContext *output_codec_context,
                                      int frame_size);

    static int convert_samples(const uint8_t **input_data,
                               uint8_t **converted_data, const int frame_size,
                               SwrContext *resample_context);

    static int add_samples_to_fifo(AVAudioFifo *fifo,
                                   uint8_t **converted_input_samples,
                                   const int frame_size);

    void WriteADTSHeader(int Size, int sample_rate,int channels);
    int ADTS(AVPacket *src, AVPacket **des);

    void aacCodeAndSent();//音频编码发送主函数
    //音频函数相关END----------------------------------------------

    char *ADTSHeader = nullptr;


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
