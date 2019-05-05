#ifndef CAUDIODATA_H
#define CAUDIODATA_H

#include <iostream>

#define BUFFER_SIZE1 1360
class CAudioData{
public:
    unsigned char * m_pBuffer;
    long m_lLength;
    long m_lMaxLength;
    uint64_t m_pts;


    CAudioData(){m_pBuffer = new unsigned char[BUFFER_SIZE1];m_lLength = 0; m_pts = 0;m_lMaxLength = BUFFER_SIZE1;}
    CAudioData(long lLength){m_lLength = lLength;m_pts = 0;m_pBuffer = new unsigned char[BUFFER_SIZE1];m_lMaxLength = BUFFER_SIZE1;}
    ~CAudioData(){
        if(m_pBuffer != NULL)
        {
            delete []m_pBuffer;
            m_pBuffer = NULL;
        }
        m_lLength = 0;
    }


};


#endif // CAUDIODATA_H
