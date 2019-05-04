#include "xrecv.h"
#include <QPainter>
#include <QDebug>

void XRecv::SetSize(int width, int height)
{
    nWidth = width;
    nHeight = height;
}


XRecv::XRecv()
{
    m_pVideoPlay = new XVideoPlay("rec.h264");
    connect(m_pVideoPlay, &XVideoPlay::sig_getAFrame, this, &XRecv::slot_GetOneFrame);
}

XRecv::~XRecv()
{
    qDebug()<<"distory";
    m_pVideoPlay->deleteLater();
//    m_pScreenRecord->deleteLater();

}

void XRecv::startPlay()
{
//    int i = type.toInt();
//    if(i == 0)
        m_pVideoPlay->startPlay();
//    else m_pScreenRecord->startPlay();
}

void XRecv::pausePlay()
{
//    int i = type.toInt();
//    if(i == 0)
        m_pVideoPlay->pausePlay();
//    else m_pScreenRecord->pausePlay();
}

void XRecv::setScale(QString s)
{
    m_pVideoPlay->setImageScale(s.toDouble());
}

void XRecv::slot_GetOneFrame(QImage image)
{
    m_Frame = image.copy();
    update();
}

void XRecv::slot_totalTimeChanged(QString str, qint64 sec)
{
    setDuration(sec);
    emit sig_totalTimeChanged(str);
}

void XRecv::slot_currentTimeChanged(QString str, qint64 sec)
{
    setPosition(sec);
    emit sig_currentTimeChanged(str);
}

void XRecv::paint(QPainter *pPainter)
{

    if (!m_Frame.isNull())
    {
        QPoint p(0,0);
        pPainter->drawImage(p,m_Frame);
    }
}

QString XRecv::getStrVideoPath() const
{
    return strVideoPath;
}

//void XRecv::setStrVideoPath(QString &value)
//{
//    emit strVideoPathChanged(value);
//    strVideoPath = value;
//    if (m_pVideoPlay)
//    {
//        m_pVideoPlay->setVideoSource(value);
//        qDebug() << "XRecv::setStrVideoPath:" << value;
//    }
//}

int XRecv::getWidth() const
{
    return nWidth;
}

void XRecv::setWidth(int value)
{
    nWidth = value;
    emit widthChanged(value);
}

int XRecv::getHeight() const
{
    return nHeight;
}

void XRecv::setHeight(int value)
{
    nHeight = value;
    emit heightChanged(value);
}

int XRecv::getDuration() const
{
    return nDuration;
}

void XRecv::setDuration(int value)
{
    nDuration = value;
    emit durationChanged(value);
}

int XRecv::getPosition() const
{
    return nPosition;
}

void XRecv::setPosition(int value)
{
    nPosition = value;
    emit positionChanged(value);
}
