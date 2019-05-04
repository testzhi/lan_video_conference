#ifndef XRECV_H
#define XRECV_H
#include <QQuickPaintedItem>
#include <QImage>

#include "xvideoplay.h"

class XRecv:public QQuickPaintedItem
{
    Q_OBJECT
public:

    Q_PROPERTY(int          nWidth           READ getWidth         WRITE setWidth        NOTIFY widthChanged)
    Q_PROPERTY(int          nHeight          READ getHeight        WRITE setHeight       NOTIFY heightChanged)
    Q_PROPERTY(int          nDuration        READ getDuration      WRITE setDuration     NOTIFY durationChanged)
    Q_PROPERTY(int          nPosition        READ getPosition      WRITE setPosition     NOTIFY positionChanged)
Q_INVOKABLE void SetSize(int width, int height);
    explicit XRecv();
    ~XRecv();
    int getHeight() const;
    void setHeight(int value);

    int getWidth() const;
    void setWidth(int value);

    QString getStrVideoPath() const;

    int getDuration() const;
    void setDuration(int value);

    int getPosition() const;
    void setPosition(int value);

public:
    Q_INVOKABLE void startPlay();
    Q_INVOKABLE void pausePlay();
    Q_INVOKABLE void setScale(QString s);
protected:
    virtual void paint(QPainter *pPainter);
private:

    QImage m_Frame;
    XVideoPlay *m_pVideoPlay;
    int nHeight;
    int nWidth;
    QString strVideoPath;
    int nDuration;
    int nPosition;
public slots:
    void slot_GetOneFrame(QImage image);
    void slot_totalTimeChanged(QString str, qint64 sec);
    void slot_currentTimeChanged(QString str, qint64 sec);

signals:
    void widthChanged(int nWidth);
    void heightChanged(int nHeight);
    void strVideoPathChanged(QString strPath);
    void durationChanged(int nDuration);
    void positionChanged(int nPosition);

    void sig_totalTimeChanged(QString str);
    void sig_currentTimeChanged(QString str);

};

#endif // XRECV_H
