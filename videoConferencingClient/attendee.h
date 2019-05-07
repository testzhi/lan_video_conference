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

class Attendee:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userID READ userID WRITE setUserID NOTIFY userIDChanged)
    Q_PROPERTY(QString realName READ realName WRITE setRealName NOTIFY realNameChanged)
    Q_PROPERTY(QString avatar READ avatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString jurisdiction READ jurisdiction WRITE setJurisdiction NOTIFY jurisdictionChanged)
public:

    Attendee(QObject *parent = 0):QObject(parent){
    }



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

private:

    QString m_userID;
    QString m_realName;
    QString m_email;
    QString m_avatar;
    QString m_jurisdiction;
};



#endif // ATTENDEE_H
