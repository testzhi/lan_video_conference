#ifndef VIDEODATA_H
#define VIDEODATA_H

#include <iostream>

#define BUFFER_SIZE 90000 //根据一帧视频编码后的大小设置

class CVideoData{
public:
    unsigned char * m_pBuffer;
    long m_lLength;
    long m_lMaxLength;
    uint64_t m_pts;


    CVideoData(){m_pBuffer = new unsigned char[BUFFER_SIZE];m_lLength = 0; m_pts = 0;
                 m_lMaxLength = BUFFER_SIZE;}

    CVideoData(long lLength){m_lLength = lLength;m_pts = 0;
                             m_pBuffer = new unsigned char[BUFFER_SIZE];m_lMaxLength = BUFFER_SIZE;}

    ~CVideoData(){
        if(m_pBuffer != NULL)
        {
            delete []m_pBuffer;
            m_pBuffer = NULL;
        }
        m_lLength = 0;
    }


};

#endif // VIDEODATA_H
