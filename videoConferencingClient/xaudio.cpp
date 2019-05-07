#include "xaudio.h"
#include <QPainter>
#include <QDebug>
#include "xaudiorecord.h"

void XAudio::SetSize(int width, int height)
{
    nWidth = width;
    nHeight = height;
}


XAudio::XAudio(QObject *parent):QObject(parent)
{
    qDebug()<<"create";
    m_audioRecord = new XAudioRecord();
    connect(m_audioRecord, SIGNAL(sig_totalTimeChanged(QString,qint64)), this, SLOT(slot_totalTimeChanged(QString,qint64)));
    connect(m_audioRecord, SIGNAL(sig_currentTimeChanged(QString,qint64)), this, SLOT(slot_currentTimeChanged(QString,qint64)));
}

XAudio::~XAudio()
{
    qDebug()<<"distory";
    m_audioRecord->deleteLater();
//    m_pScreenRecord->deleteLater();

}

void XAudio::startPlay()
{
//    int i = type.toInt();
//    if(i == 0)
        m_audioRecord->startPlay();
//    else m_pScreenRecord->startPlay();
}

void XAudio::pausePlay()
{
//    int i = type.toInt();
//    if(i == 0)
        m_audioRecord->pausePlay();
//    else m_pScreenRecord->pausePlay();
}

void XAudio::slot_totalTimeChanged(QString str, qint64 sec)
{
    setDuration(sec);
    emit sig_totalTimeChanged(str);
}

void XAudio::slot_currentTimeChanged(QString str, qint64 sec)
{
    setPosition(sec);
    emit sig_currentTimeChanged(str);
}

QString XAudio::getStrVideoPath() const
{
    return strVideoPath;
}

void XAudio::setStrVideoPath(QString &value)
{
    emit strVideoPathChanged(value);
    strVideoPath = value;
    if (m_audioRecord)
    {
//        m_audioRecord->setVideoSource(value);
        qDebug() << "XVideo::setStrVideoPath:" << value;
    }
}

int XAudio::getWidth() const
{
    return nWidth;
}

void XAudio::setWidth(int value)
{
    nWidth = value;
    emit widthChanged(value);
}

int XAudio::getHeight() const
{
    return nHeight;
}

void XAudio::setHeight(int value)
{
    nHeight = value;
    emit heightChanged(value);
}

int XAudio::getDuration() const
{
    return nDuration;
}

void XAudio::setDuration(int value)
{
    nDuration = value;
    emit durationChanged(value);
}

int XAudio::getPosition() const
{
    return nPosition;
}

void XAudio::setPosition(int value)
{
    nPosition = value;
    emit positionChanged(value);
}

