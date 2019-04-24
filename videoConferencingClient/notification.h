#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>

class Notification:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notificationCategory READ notificationCategory WRITE setNotificationCategory NOTIFY notificationCategoryChanged)
    Q_PROPERTY(QString notificationMessage READ notificationMessage WRITE setNotificationMessage NOTIFY notificationMessageChanged)
    Q_PROPERTY(QString meetingID READ meetingID WRITE setMeetingID NOTIFY meetingIDChanged)
signals:
    void notificationCategoryChanged();
    void notificationMessageChanged();
    void meetingIDChanged();
public:
    Notification(QObject *parent = 0):QObject(parent){}
    QString notificationCategory() const;
    void setNotificationCategory(const QString &notificationCategory);
    QString notificationMessage() const;
    void setNotificationMessage(const QString &notificationMessage);

    QString meetingID() const;
    void setMeetingID(const QString &meetingID);

private:
    QString m_notificationCategory;
    QString m_notificationMessage;
    QString m_meetingID;
    //    QString m_notificationState;
};

#endif // NOTIFICATION_H
