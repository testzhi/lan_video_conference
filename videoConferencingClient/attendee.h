#ifndef ATTENDEE_H
#define ATTENDEE_H

#include <string>
#include <QObject>
#include <iostream>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavdevice/avdevice.h>
#include <libavutil/audio_fifo.h>
#include <SDL2/SDL.h>
};

using std::cout;
using std::endl;

int sfp_refresh_thread(void *opaque);
int sdl_play_refresh_thread(void *opaque);
void fill_audio(void *udata, Uint8 *stream, int len);

class Attendee:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userID READ userID WRITE setUserID NOTIFY userIDChanged)
    Q_PROPERTY(QString realName READ realName WRITE setRealName NOTIFY realNameChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString jurisdiction READ jurisdiction WRITE setJurisdiction NOTIFY jurisdictionChanged)
public:
    enum ATTENDEE_KIND{HOST=1, COMMON_ATTENDEE, ASSISTANT};
    enum VIDEO_KIND{CAMERA_VIDEO=1, SCREEN_CAPTURE_VIDEO, FILE_VIDEO};
    enum AUDIO_KIND{RECORD_AUDIO=1, FILE_AUDIO};

    Attendee(QObject *parent = 0):QObject(parent){
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


    Q_INVOKABLE void camera(std::string filePath)
    {
//        widge = screen;
        initCameraInputSource();
        getVideoStream(CAMERA_VIDEO);
        openVideoCodec(CAMERA_VIDEO);
        recordCamera(filePath);
    }
    void screenCapture(std::string filePath)
    {
        initScreenCaptureInputSource();
        getVideoStream(SCREEN_CAPTURE_VIDEO);
        openVideoCodec(SCREEN_CAPTURE_VIDEO);
        recordScreenCapture(filePath);
    }
    void audio(std::string filePath)
    {
        initAudioInputSource();
        getAudioStream(RECORD_AUDIO);
        openAudioCodec(RECORD_AUDIO);
        recordAudio(filePath);
    }
    void sdlPlayVideo(std::string videoPath);
    void sdlPlayAudio(std::string audioPath);

    void freeAttendee();



//    void audioRecordThread(){}
//    void ScreenCaptureRecordThread(){}
    QString userID() const;
    void setUserID(const QString &userID);

    QString realName() const;
    void setRealName(const QString &realName);

    QString email() const;
    void setEmail(const QString &email);

    QString avatar() const;
    void setAvatar(const QString &avatar);

    QString jurisdiction() const;
    void setJurisdiction(const QString &jurisdiction);

signals:
    void userIDChanged();
    void realNameChanged();
    void avatarChanged();
    void emailChanged();
    void jurisdictionChanged();
protected:
    //获取录像 录屏 录音环境
    void initScreenCaptureInputSource();
    void initCameraInputSource();
    void initAudioInputSource();
//    //获取待读音视频环境
    void initReadVideoInputSource(std::string filePath);
    void initReadAudioInputSource(std::string filePath);

    //获取视频流
    void getVideoStream(int videoKind);
    void getAudioStream(int audioKind);

    void openVideoCodec(int videoKind);
    void openAudioCodec(int audioKind);

    void recordCamera(std::string cameraPath);
    void recordScreenCapture(std::string screenCapturePath);
    void recordAudio(std::string audioPath);

private:
    void recordVideo(AVFormatContext *videoFormatCtx, int videoIndex, AVCodecContext *videoCodecCtx, AVFrame *videoFrameYUV, std::string filePath);

    //录音录屏录像
    AVFormatContext	*m_pScreenCaptureFormatCtx = nullptr;
    AVFormatContext *m_pCameraFormatCtx = nullptr;
    AVFormatContext *m_pAudioFormatCtx = nullptr;
    int m_screenCaptureIndex = -1, m_audioIndex = -1, m_cameraIndex = -1;
    //文件or流读取
    AVFormatContext *m_fsVideoFormatCtx = nullptr;
    AVFormatContext *m_fsAudioFormatCtx = nullptr;
    int m_fsVideoIndex = -1, m_fsAudioIndex = -1;

    //录音录屏录像
    AVDictionary *m_screenCaptureOptions = nullptr;
    AVDictionary *m_cameraOptions = nullptr;
    AVDictionary *m_audioOptions = nullptr;
    //文件or流读取
    AVDictionary *m_fsVideoOptions = nullptr;
    AVDictionary *m_fsAudioOptions = nullptr;

    //录音录屏录像
    AVCodecContext *m_pScreenCaptureCodecCtx = nullptr;
    AVCodecContext *m_pCameraCodecCtx = nullptr;
    AVCodecContext *m_pAudioCodecCtx = nullptr;
    //文件or流读取
    AVCodecContext *m_fsVideoCodecCtx = nullptr;
    AVCodecContext *m_fsAudioCodecCtx = nullptr;




    AVFrame	*m_pCameraFrameYUV = nullptr;
    AVFrame *m_pScreenCaptureFrameYUV = nullptr;


    SDL_Window *screen;
    QWidget *widge;
    int screen_w = 0, screen_h = 0;


    //本地录像及录音存储
    FILE *m_fp_yuv_video = nullptr;
    FILE *m_fp_yuv_audio_in = nullptr;

    QString m_userID;
    QString m_realName;
    QString m_email;
    QString m_avatar;
    QString m_jurisdiction;
};



#endif // ATTENDEE_H
