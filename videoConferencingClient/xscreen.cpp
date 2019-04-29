#include "xscreen.h"
#include <QPainter>
#include <QDebug>
#include "xvideorecord.h"

void XScreen::SetSize(int width, int height)
{
    nWidth = width;
    nHeight = height;
}


XScreen::XScreen()
{
    qDebug()<<"create";
//    m_pCameraRecord = new XScreenRecordThread(":0.0+10,20", "x11grab");
    m_pCameraRecord = new XVideoRecordThread(":0.0+10,20", "x11grab");
//    m_pScreenRecord = new XVideoRecordThread(":0.0+10,20", "x11grab");
    connect(m_pCameraRecord, &XVideoRecordThread::sig_GetOneFrame, this, &XScreen::slot_GetOneFrame);
    connect(m_pCameraRecord, SIGNAL(sig_totalTimeChanged(QString,qint64)), this, SLOT(slot_totalTimeChanged(QString,qint64)));
    connect(m_pCameraRecord, SIGNAL(sig_currentTimeChanged(QString,qint64)), this, SLOT(slot_currentTimeChanged(QString,qint64)));
}

XScreen::~XScreen()
{
    qDebug()<<"distory";
    m_pCameraRecord->deleteLater();
//    m_pScreenRecord->deleteLater();

}

void XScreen::startPlay()
{
//    int i = type.toInt();
//    if(i == 0)
        m_pCameraRecord->startPlay();
//    else m_pScreenRecord->startPlay();
}

void XScreen::pausePlay()
{
//    int i = type.toInt();
//    if(i == 0)
        m_pCameraRecord->pausePlay();
//    else m_pScreenRecord->pausePlay();
}

void XScreen::setScale(QString s)
{
    m_pCameraRecord->setImageScale(s.toDouble());
}

void XScreen::slot_GetOneFrame(QImage image)
{
    m_Frame = image.copy();
    update();
}

void XScreen::slot_totalTimeChanged(QString str, qint64 sec)
{
    setDuration(sec);
    emit sig_totalTimeChanged(str);
}

void XScreen::slot_currentTimeChanged(QString str, qint64 sec)
{
    setPosition(sec);
    emit sig_currentTimeChanged(str);
}

void XScreen::paint(QPainter *pPainter)
{

    if (!m_Frame.isNull())
    {
        QPoint p(0,0);
        pPainter->drawImage(p,m_Frame);
    }
}

QString XScreen::getStrVideoPath() const
{
    return strVideoPath;
}

void XScreen::setStrVideoPath(QString &value)
{
    emit strVideoPathChanged(value);
    strVideoPath = value;
    if (m_pCameraRecord)
    {
        m_pCameraRecord->setVideoSource(value);
        qDebug() << "XScreen::setStrVideoPath:" << value;
    }
}

int XScreen::getWidth() const
{
    return nWidth;
}

void XScreen::setWidth(int value)
{
    nWidth = value;
    emit widthChanged(value);
}

int XScreen::getHeight() const
{
    return nHeight;
}

void XScreen::setHeight(int value)
{
    nHeight = value;
    emit heightChanged(value);
}

int XScreen::getDuration() const
{
    return nDuration;
}

void XScreen::setDuration(int value)
{
    nDuration = value;
    emit durationChanged(value);
}

int XScreen::getPosition() const
{
    return nPosition;
}

void XScreen::setPosition(int value)
{
    nPosition = value;
    emit positionChanged(value);
}
