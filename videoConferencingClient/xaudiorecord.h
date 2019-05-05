#ifndef XAUDIORECORD_H
#define XAUDIORECORD_H

#include <QThread>
#include "aacsender.h"

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
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
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
    explicit XAudioRecord();
    ~XAudioRecord();

    void initAudioRecord();
    void closeAudioRecord();

    void initAACOutputFile();
    void closeAACOutputFile();

    void startPlay();
    void stopPlay();
    void pausePlay();


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

    //音频函数相关END----------------------------------------------
    void checkerror(int rtperr);
    void SetAACRTPParams(CAACSender& sess,uint32_t destip,uint16_t destport,uint16_t baseport);


protected:
    void run();

private:
    AVFormatContext *m_inFormatContext;
    AVCodecContext *m_inPCodeCtx;
    AVDictionary *m_inOptions;
    int m_audioStream;

    PlayerState m_playerState;

    AVFormatContext *m_outFormatContext;
    AVCodecContext *m_outPCodecCtx;
    AVDictionary *m_outOptions;

    QString m_AACOutputFilePath;
    AVStream *m_audio_st;
};

#endif // XAUDIORECORD_H
