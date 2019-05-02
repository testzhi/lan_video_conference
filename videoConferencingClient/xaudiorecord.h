#ifndef XAUDIORECORD_H
#define XAUDIORECORD_H

#include <QThread>

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

enum PlayerState
{
    Stop,
    Pause,
    Playing
};

class XAudioRecord : public QThread
{
public:
    //                              hw:1      alsa
    explicit XAudioRecord(QString devSource, QString imtSource);
    ~XAudioRecord();

    void initAudioRecord();
    void closeAudioRecord();

    void initAACOutputFile();
    void closeAACOutputFile();

    void startPlay();
    void stopPlay();
    void pausePlay();
protected:
    void run();

private:
    AVFormatContext *m_inFormatContext;
    AVCodecContext *m_inPCodeCtx;
    AVDictionary *m_inOptions;
    int m_audioStream;

    QString m_audioInputFormat;
    QString m_audioInputSource;

    PlayerState m_playerState;

    AVFormatContext *m_outFormatContext;
    AVCodecContext *m_outPCodeCtx;
    AVDictionary *m_outOptions;

    QString m_AACOutputFilePath;
    AVStream *m_audio_st;
};

#endif // XAUDIORECORD_H
