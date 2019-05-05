#ifndef XAUDIOPLAY_H
#define XAUDIOPLAY_H

#include <QString>
#include <QThread>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
#include "SDL2/SDL.h"
};
static  Uint8  *audioChunk;
static  Uint32  audioLength;
static  Uint8  *audioPostion;


void fillAudio(void *udata,Uint8 *stream,int len)
{
    //SDL 2.0
    SDL_memset(stream, 0, len);
    if(audioLength==0)		/*  Only  play  if  we  have  data  left  */
        return;
    len=(len>audioLength?audioLength:len);	/*  Mix  as  much  data  as  possible  */

    SDL_MixAudio(stream,audioPostion,len,SDL_MIX_MAXVOLUME);
    audioPostion += len;
    audioLength -= len;
}

class XAudioPlay :public QThread
{
public:
    XAudioPlay();

    void initAudioPlay();
    void closeAudioPlay();

    QString fileName() const;
    void setFileName(const QString &fileName);

protected:
    void run();

private:

    AVFormatContext *m_pFormatCtx;
    AVCodecContext *m_pCodecCtx;
    AVDictionary *m_options;
    int m_audioStream{-1};

    QString m_fileName{"rec.aac"};
};

#endif // XAUDIOPLAY_H
