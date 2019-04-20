#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>

class Notification:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notificationCategory READ notificationCategory WRITE setNotificationCategory NOTIFY notificationCategoryChanged)
    Q_PROPERTY(QString notificationMessage READ notificationMessage WRITE setNotificationMessage NOTIFY notificationMessageChanged)
signals:
    void notificationCategoryChanged();
    void notificationMessageChanged();
public:
    Notification(QObject *parent = 0):QObject(parent){}
    QString notificationCategory() const;
    void setNotificationCategory(const QString &notificationCategory);
    QString notificationMessage() const;
    void setNotificationMessage(const QString &notificationMessage);

private:
    QString m_notificationCategory;
    QString m_notificationMessage;
    //    QString m_notificationState;
};

#endif // NOTIFICATION_H
