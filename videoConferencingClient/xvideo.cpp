#include "xvideo.h"
#include <QPainter>
#include <QDebug>
#include "xvideorecord.h"

void XVideo::SetSize(int width, int height)
{
    nWidth = width;
    nHeight = height;
}


XVideo::XVideo()
{
    qDebug()<<"create";
//    m_pCameraRecord = new XVideoRecordThread(":0.0+10,20", "x11grab");
    m_pCameraRecord = new XVideoRecordThread("/dev/video0", "video4linux2");
//    m_pScreenRecord = new XVideoRecordThread(":0.0+10,20", "x11grab");
    connect(m_pCameraRecord, &XVideoRecordThread::sig_GetOneFrame, this, &XVideo::slot_GetOneFrame);
    connect(m_pCameraRecord, SIGNAL(sig_totalTimeChanged(QString,qint64)), this, SLOT(slot_totalTimeChanged(QString,qint64)));
    connect(m_pCameraRecord, SIGNAL(sig_currentTimeChanged(QString,qint64)), this, SLOT(slot_currentTimeChanged(QString,qint64)));
}

XVideo::~XVideo()
{
    qDebug()<<"distory";
    m_pCameraRecord->deleteLater();
    m_pScreenRecord->deleteLater();

}

void XVideo::startPlay()
{
    m_pCameraRecord->startPlay();
}

void XVideo::pausePlay()
{
//    m_pCameraRecord->pausePlay();
    m_pCameraRecord->terminate();
}

void XVideo::setScale(QString s)
{
    m_pCameraRecord->setImageScale(s.toDouble());
}

void XVideo::slot_GetOneFrame(QImage image)
{
    m_Frame = image.copy();
    update();
}

void XVideo::slot_totalTimeChanged(QString str, qint64 sec)
{
    setDuration(sec);
    emit sig_totalTimeChanged(str);
}

void XVideo::slot_currentTimeChanged(QString str, qint64 sec)
{
    setPosition(sec);
    emit sig_currentTimeChanged(str);
}

void XVideo::paint(QPainter *pPainter)
{

    if (!m_Frame.isNull())
    {
        QPoint p(0,0);
        pPainter->drawImage(p,m_Frame);
    }
}

QString XVideo::getStrVideoPath() const
{
    return strVideoPath;
}

void XVideo::setStrVideoPath(QString &value)
{
    emit strVideoPathChanged(value);
    strVideoPath = value;
    if (m_pCameraRecord)
    {
        m_pCameraRecord->setVideoSource(value);
        qDebug() << "XVideo::setStrVideoPath:" << value;
    }
}

int XVideo::getWidth() const
{
    return nWidth;
}

void XVideo::setWidth(int value)
{
    nWidth = value;
    emit widthChanged(value);
}

int XVideo::getHeight() const
{
    return nHeight;
}

void XVideo::setHeight(int value)
{
    nHeight = value;
    emit heightChanged(value);
}

int XVideo::getDuration() const
{
    return nDuration;
}

void XVideo::setDuration(int value)
{
    nDuration = value;
    emit durationChanged(value);
}

int XVideo::getPosition() const
{
    return nPosition;
}

void XVideo::setPosition(int value)
{
    nPosition = value;
    emit positionChanged(value);
}
