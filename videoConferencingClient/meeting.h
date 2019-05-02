#ifndef MEETING_H
#define MEETING_H

#include <QObject>
#include <QQmlListProperty>

#include "attendee.h"

class Meeting:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString initiator READ initiator WRITE setInitiator NOTIFY initiatorChanged)
    Q_PROPERTY(QString speaker READ speaker WRITE setSpeaker NOTIFY speakerChanged)
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QString time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QString scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QString duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString meetingID READ meetingID WRITE setMeetingID NOTIFY meetingIDChanged)
    Q_PROPERTY(QString remark READ remark WRITE setRemark NOTIFY remarkChanged)

signals:
    void initiatorChanged();
    void speakerChanged();
    void dateChanged();
    void timeChanged();
    void themeChanged();
    void scaleChanged();
    void durationChanged();
    void categoryChanged();
    void stateChanged();
    void meetingIDChanged();
    void remarkChanged();
public:
    Meeting(QObject *parent = 0):QObject(parent){}
    Meeting(std::string initiator,std::string speaker,std::string date,std::string time,std::string theme,std::string scale,std::string duration,std::string category,std::string state);
    Q_INVOKABLE QString initiator() const;
    Q_INVOKABLE void setInitiator(const QString &initiator);
    Q_INVOKABLE QString speaker() const;
    Q_INVOKABLE void setSpeaker(const QString &speaker);
    Q_INVOKABLE QString date() const;
    Q_INVOKABLE void setDate(const QString &date);
    Q_INVOKABLE QString time() const;
    Q_INVOKABLE void setTime(const QString &time);
    Q_INVOKABLE QString theme() const;
    Q_INVOKABLE void setTheme(const QString &theme);
    Q_INVOKABLE QString scale() const;
    Q_INVOKABLE void setScale(const QString &scale);
    Q_INVOKABLE QString duration() const;
    Q_INVOKABLE void setDuration(const QString &duration);
    Q_INVOKABLE QString category() const;
    Q_INVOKABLE void setCategory(const QString &category);
    Q_INVOKABLE QString state() const;
    Q_INVOKABLE QString getState();
    Q_INVOKABLE void setState(const QString &state);
    Q_INVOKABLE QString meetingID() const;
    Q_INVOKABLE void setMeetingID(const QString &meetingID);
    Q_INVOKABLE QString remark() const;
    Q_INVOKABLE void setRemark(const QString &remark);

private:
    QString m_meetingID;
    QString m_initiator;//会议发起人（秘书）
    QString m_speaker;//会议主讲人
    QString m_date;//会议日期
    QString m_time;//会议开始时间
    QString m_theme;//会议主题
    QString m_remark;
    QString m_scale;//会议规模（人数）
    QString m_duration;//会议预期时长
    QString m_category;//会议类别
    QString m_state;//会议状态

};

#endif // MEETING_H
