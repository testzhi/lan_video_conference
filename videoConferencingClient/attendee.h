#ifndef ATTENDEE_H
#define ATTENDEE_H

#include <string>
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

int sfp_refresh_thread(void *opaque);
int sdl_play_refresh_thread(void *opaque);
void fill_audio(void *udata, Uint8 *stream, int len);

class Attendee
{
public:
    enum ATTENDEE_KIND{HOST=1, COMMON_ATTENDEE, ASSISTANT};
    enum VIDEO_KIND{CAMERA_VIDEO=1, SCREEN_CAPTURE_VIDEO, FILE_VIDEO};
    enum AUDIO_KIND{RECORD_AUDIO=1, FILE_AUDIO};

    Attendee();


    void camera(std::string filePath)
    {
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

    ~Attendee();



//    void audioRecordThread(){}
//    void ScreenCaptureRecordThread(){}


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
    int screen_w = 0, screen_h = 0;


    //本地录像及录音存储
    FILE *m_fp_yuv_video = nullptr;
    FILE *m_fp_yuv_audio_in = nullptr;
};



#endif // ATTENDEE_H
